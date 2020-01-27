////////////////////////////////////////////////////////////////////////
// OpenTibia - an opensource roleplaying game
////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////
#include "otpch.h"
#include "enums.h"
#include <iostream>

#include "databasemanager.h"
#include "tools.h"

#include "configmanager.h"
extern ConfigManager g_config;

bool DatabaseManager::optimizeTables()
{
	Database* db = Database::getInstance();
	DBQuery query;
	switch(db->getDatabaseEngine())
	{
		case DATABASE_ENGINE_MYSQL:
		{
			query << "SELECT `TABLE_NAME` FROM `information_schema`.`tables` WHERE `TABLE_SCHEMA` = " << db->escapeString(g_config.getString(ConfigManager::SQL_DB)) << " AND `DATA_FREE` > 0;";
			DBResult* result;
			if(!(result = db->storeQuery(query.str())))
				break;

			query.str("");
			do
			{
				std::clog << "> Optimizing table: " << result->getDataString("TABLE_NAME") << "... ";
				query << "OPTIMIZE TABLE `" << result->getDataString("TABLE_NAME") << "`;";
				if(db->query(query.str()))
					std::clog << "[success]" << std::endl;
				else
					std::clog << "[failure]" << std::endl;

				query.str("");
			}
			while(result->next());

			result->free();
			return true;
		}

		case DATABASE_ENGINE_SQLITE:
		{
			if(!db->query("VACUUM;"))
				break;

			std::clog << "> Optimized database." << std::endl;
			return true;
		}

		case DATABASE_ENGINE_POSTGRESQL:
		{
			if(!db->query("VACUUM FULL;"))
				break;

			std::clog << "> Optimized database." << std::endl;
			return true;
		}

		default:
			break;
	}

	return false;
}

bool DatabaseManager::triggerExists(std::string trigger)
{
	Database* db = Database::getInstance();
	DBQuery query;
	query << "SELECT `TRIGGER_NAME` FROM `information_schema`.`triggers` WHERE `TRIGGER_SCHEMA` = " << db->escapeString(g_config.getString(ConfigManager::SQL_DB)) << " AND `TRIGGER_NAME` = " << db->escapeString(trigger) << ";";

	DBResult* result;
	if(!(result = db->storeQuery(query.str())))
		return false;

	result->free();
	return true;
}

bool DatabaseManager::tableExists(std::string table)
{
	Database* db = Database::getInstance();
	DBQuery query;
	query << "SELECT `TABLE_NAME` FROM `information_schema`.`tables` WHERE `TABLE_SCHEMA` = " << db->escapeString(g_config.getString(ConfigManager::SQL_DB)) << " AND `TABLE_NAME` = " << db->escapeString(table) << ";";

	DBResult* result;
	if(!(result = db->storeQuery(query.str())))
		return false;

	result->free();
	return true;
}

bool DatabaseManager::isDatabaseSetup()
{
	Database* db = Database::getInstance();
	DBQuery query;
	query << "SELECT `TABLE_NAME` FROM `information_schema`.`tables` WHERE `TABLE_SCHEMA` = " << db->escapeString(g_config.getString(ConfigManager::SQL_DB)) << ";";

	DBResult* result;
	if(!(result = db->storeQuery(query.str())))
		return false;

	result->free();
	return true;
}

int32_t DatabaseManager::getDatabaseVersion()
{
	if(!tableExists("server_config"))
		return 0;

	int32_t value = 0;
	if(getDatabaseConfig("db_version", value))
		return value;

	return -1;
}

bool DatabaseManager::getDatabaseConfig(std::string config, int32_t &value)
{
	value = 0;

	Database* db = Database::getInstance();
	DBResult* result;

	DBQuery query;
	query << "SELECT `value` FROM `server_config` WHERE `config` = " << db->escapeString(config) << ";";
	if(!(result = db->storeQuery(query.str())))
		return false;

	value = atoi(result->getDataString("value").c_str());
	result->free();
	return true;
}

bool DatabaseManager::getDatabaseConfig(std::string config, std::string &value)
{
	value = "";

	Database* db = Database::getInstance();
	DBResult* result;

	DBQuery query;
	query << "SELECT `value` FROM `server_config` WHERE `config` = " << db->escapeString(config) << ";";
	if(!(result = db->storeQuery(query.str())))
		return false;

	value = result->getDataString("value");
	result->free();
	return true;
}

void DatabaseManager::registerDatabaseConfig(std::string config, int32_t value)
{
	Database* db = Database::getInstance();
	DBQuery query;

	int32_t tmp = 0;
	if(!getDatabaseConfig(config, tmp))
		query << "INSERT INTO `server_config` VALUES (" << db->escapeString(config) << ", '" << value << "');";
	else
		query << "UPDATE `server_config` SET `value` = '" << value << "' WHERE `config` = " << db->escapeString(config) << ";";

	db->query(query.str());
}

void DatabaseManager::registerDatabaseConfig(std::string config, std::string value)
{
	Database* db = Database::getInstance();
	DBQuery query;

	std::string tmp;
	if(!getDatabaseConfig(config, tmp))
		query << "INSERT INTO `server_config` VALUES (" << db->escapeString(config) << ", " << db->escapeString(value) << ");";
	else
		query << "UPDATE `server_config` SET `value` = " << db->escapeString(value) << " WHERE `config` = " << db->escapeString(config) << ";";

	db->query(query.str());
}

void DatabaseManager::checkEncryption()
{
	Encryption_t newValue = (Encryption_t)g_config.getNumber(ConfigManager::ENCRYPTION);
	int32_t value = (int32_t)ENCRYPTION_PLAIN;
	if(getDatabaseConfig("encryption", value))
	{
		if(newValue != (Encryption_t)value)
		{
			switch(newValue)
			{
				case ENCRYPTION_MD5:
				{
					if((Encryption_t)value != ENCRYPTION_PLAIN)
					{
						std::clog << "> WARNING: You cannot change the encryption to MD5, change it back in config.lua." << std::endl;
						return;
					}

					Database* db = Database::getInstance();
					DBQuery query;
					if(db->getDatabaseEngine() != DATABASE_ENGINE_MYSQL && db->getDatabaseEngine() != DATABASE_ENGINE_POSTGRESQL)
					{
						query << "SELECT `id`, `password`, `key` FROM `accounts`;";
						if(DBResult* result = db->storeQuery(query.str()))
						{
							do
							{
								query << "UPDATE `accounts` SET `password` = " << db->escapeString(transformToMD5(result->getDataString("password"), false)) << ", `key` = " << db->escapeString(transformToMD5(result->getDataString("key"), false)) << " WHERE `id` = " << result->getDataInt("id") << ";";
								db->query(query.str());
							}
							while(result->next());
							result->free();
						}
					}
					else
						db->query("UPDATE `accounts` SET `password` = MD5(`password`), `key` = MD5(`key`);");

					registerDatabaseConfig("encryption", (int32_t)newValue);
					std::clog << "> Encryption updated to MD5." << std::endl;
					break;
				}

				case ENCRYPTION_SHA1:
				{
					if((Encryption_t)value != ENCRYPTION_PLAIN)
					{
						std::clog << "> WARNING: You cannot change the encryption to SHA1, change it back in config.lua." << std::endl;
						return;
					}

					Database* db = Database::getInstance();
					DBQuery query;
					if(db->getDatabaseEngine() != DATABASE_ENGINE_MYSQL && db->getDatabaseEngine() != DATABASE_ENGINE_POSTGRESQL)
					{
						query << "SELECT `id`, `password`, `key` FROM `accounts`;";
						if(DBResult* result = db->storeQuery(query.str()))
						{
							do
							{
								query << "UPDATE `accounts` SET `password` = " << db->escapeString(transformToSHA1(result->getDataString("password"), false)) << ", `key` = " << db->escapeString(transformToSHA1(result->getDataString("key"), false)) << " WHERE `id` = " << result->getDataInt("id") << ";";
								db->query(query.str());
							}
							while(result->next());
							result->free();
						}
					}
					else
						db->query("UPDATE `accounts` SET `password` = SHA1(`password`), `key` = SHA1(`key`);");

					registerDatabaseConfig("encryption", (int32_t)newValue);
					std::clog << "> Encryption set to SHA1." << std::endl;
					break;
				}

				case ENCRYPTION_SHA256:
				{
					if((Encryption_t)value != ENCRYPTION_PLAIN)
					{
						std::clog << "> WARNING: You cannot change the encryption to SHA256, change it back in config.lua." << std::endl;
						return;
					}

					Database* db = Database::getInstance();
					DBQuery query;

					query << "SELECT `id`, `password`, `key` FROM `accounts`;";
					if(DBResult* result = db->storeQuery(query.str()))
					{
						do
						{
							query << "UPDATE `accounts` SET `password` = " << db->escapeString(transformToSHA256(result->getDataString("password"), false)) << ", `key` = " << db->escapeString(transformToSHA256(result->getDataString("key"), false)) << " WHERE `id` = " << result->getDataInt("id") << ";";
							db->query(query.str());
						}
						while(result->next());
						result->free();
					}

					registerDatabaseConfig("encryption", (int32_t)newValue);
					std::clog << "> Encryption set to SHA256." << std::endl;
					break;
				}

				case ENCRYPTION_SHA512:
				{
					if((Encryption_t)value != ENCRYPTION_PLAIN)
					{
						std::clog << "> WARNING: You cannot change the encryption to SHA512, change it back in config.lua." << std::endl;
						return;
					}

					Database* db = Database::getInstance();
					DBQuery query;

					query << "SELECT `id`, `password`, `key` FROM `accounts`;";
					if(DBResult* result = db->storeQuery(query.str()))
					{
						do
						{
							query << "UPDATE `accounts` SET `password` = " << db->escapeString(transformToSHA512(result->getDataString("password"), false)) << ", `key` = " << db->escapeString(transformToSHA512(result->getDataString("key"), false)) << " WHERE `id` = " << result->getDataInt("id") << ";";
							db->query(query.str());
						}
						while(result->next());
						result->free();
					}

					registerDatabaseConfig("encryption", (int32_t)newValue);
					std::clog << "> Encryption set to SHA512." << std::endl;
					break;
				}

				default:
				{
					std::clog << "> WARNING: You cannot switch from hashed passwords to plain text, change back the passwordType in config.lua to the passwordType you were previously using." << std::endl;
					break;
				}
			}
		}
	}
	else
	{
		registerDatabaseConfig("encryption", (int32_t)newValue);
		if(g_config.getBool(ConfigManager::ACCOUNT_MANAGER))
		{
			switch(newValue)
			{
				case ENCRYPTION_MD5:
				{
					Database* db = Database::getInstance();
					DBQuery query;
					query << "UPDATE `accounts` SET `password` = " << db->escapeString(transformToMD5("1", false)) << " WHERE `id` = 1 AND `password` = '1';";
					db->query(query.str());
					break;
				}

				case ENCRYPTION_SHA1:
				{
					Database* db = Database::getInstance();
					DBQuery query;
					query << "UPDATE `accounts` SET `password` = " << db->escapeString(transformToSHA1("1", false)) << " WHERE `id` = 1 AND `password` = '1';";
					db->query(query.str());
					break;
				}

				case ENCRYPTION_SHA256:
				{
					Database* db = Database::getInstance();
					DBQuery query;
					query << "UPDATE `accounts` SET `password` = " << db->escapeString(transformToSHA256("1", false)) << " WHERE `id` = 1 AND `password` = '1';";
					db->query(query.str());
					break;
				}

				case ENCRYPTION_SHA512:
				{
					Database* db = Database::getInstance();
					DBQuery query;
					query << "UPDATE `accounts` SET `password` = " << db->escapeString(transformToSHA512("1", false)) << " WHERE `id` = 1 AND `password` = '1';";
					db->query(query.str());
					break;
				}

				default:
					break;
			}
		}
	}
}

void DatabaseManager::checkTriggers()
{
	Database* db = Database::getInstance();
	switch(db->getDatabaseEngine())
	{
		case DATABASE_ENGINE_MYSQL:
		{
			std::string triggerName[] =
			{
				"ondelete_accounts",
				"oncreate_guilds",
				"ondelete_guilds",
				"oncreate_players",
				"ondelete_players",
			};

			std::string triggerStatement[] =
			{
				"CREATE TRIGGER `ondelete_accounts` BEFORE DELETE ON `accounts` FOR EACH ROW BEGIN DELETE FROM `bans` WHERE `type` NOT IN(1, 2) AND `value` = OLD.`id`; END;",
				"CREATE TRIGGER `oncreate_guilds` AFTER INSERT ON `guilds` FOR EACH ROW BEGIN INSERT INTO `guild_ranks` (`name`, `level`, `guild_id`) VALUES ('Leader', 3, NEW.`id`); INSERT INTO `guild_ranks` (`name`, `level`, `guild_id`) VALUES ('Vice-Leader', 2, NEW.`id`); INSERT INTO `guild_ranks` (`name`, `level`, `guild_id`) VALUES ('Member', 1, NEW.`id`); END;",
				"CREATE TRIGGER `ondelete_guilds` BEFORE DELETE ON `guilds` FOR EACH ROW BEGIN UPDATE `players` SET `guildnick` = '', `rank_id` = 0 WHERE `rank_id` IN (SELECT `id` FROM `guild_ranks` WHERE `guild_id` = OLD.`id`); END;",
				"CREATE TRIGGER `oncreate_players` AFTER INSERT ON `players` FOR EACH ROW BEGIN INSERT INTO `player_skills` (`player_id`, `skillid`, `value`) VALUES (NEW.`id`, 0, 10); INSERT INTO `player_skills` (`player_id`, `skillid`, `value`) VALUES (NEW.`id`, 1, 10); INSERT INTO `player_skills` (`player_id`, `skillid`, `value`) VALUES (NEW.`id`, 2, 10); INSERT INTO `player_skills` (`player_id`, `skillid`, `value`) VALUES (NEW.`id`, 3, 10); INSERT INTO `player_skills` (`player_id`, `skillid`, `value`) VALUES (NEW.`id`, 4, 10); INSERT INTO `player_skills` (`player_id`, `skillid`, `value`) VALUES (NEW.`id`, 5, 10); INSERT INTO `player_skills` (`player_id`, `skillid`, `value`) VALUES (NEW.`id`, 6, 10); END;",
				"CREATE TRIGGER `ondelete_players` BEFORE DELETE ON `players` FOR EACH ROW BEGIN DELETE FROM `bans` WHERE `type` = 2 AND `value` = OLD.`id`; UPDATE `houses` SET `owner` = 0 WHERE `owner` = OLD.`id`; END;"
			};

			DBQuery query;
			for(uint32_t i = 0; i < sizeof(triggerName) / sizeof(std::string); ++i)
			{
				if(!triggerExists(triggerName[i]))
				{
					std::clog << "> Trigger: " << triggerName[i] << " does not exist, creating it..." << std::endl;
					db->query(triggerStatement[i]);
				}
			}

			break;
		}

		case DATABASE_ENGINE_SQLITE:
		{
			std::string triggerName[] =
			{
				"oncreate_guilds",
				"oncreate_players",
				"ondelete_accounts",
				"ondelete_players",
				"ondelete_guilds",
				"oninsert_players",
				"onupdate_players",
				"oninsert_guilds",
				"onupdate_guilds",
				"ondelete_houses",
				"ondelete_tiles",
				"oninsert_guild_ranks",
				"onupdate_guild_ranks",
				"oninsert_house_lists",
				"onupdate_house_lists",
				"oninsert_player_depotitems",
				"onupdate_player_depotitems",
				"oninsert_player_skills",
				"onupdate_player_skills",
				"oninsert_player_storage",
				"onupdate_player_storage",
				"oninsert_player_viplist",
				"onupdate_player_viplist",
				"oninsert_account_viplist",
				"onupdate_account_viplist",
				"oninsert_tile_items",
				"onupdate_tile_items",
				"oninsert_player_spells",
				"onupdate_player_spells",
				"oninsert_player_deaths",
				"onupdate_player_deaths",
				"oninsert_killers",
				"onupdate_killers",
				"oninsert_environment_killers",
				"onupdate_environment_killers",
				"oninsert_player_killers",
				"onupdate_player_killers"
			};

			std::string triggerStatement[] =
			{
				"CREATE TRIGGER `oncreate_guilds` \
AFTER INSERT ON `guilds` \
BEGIN \
	INSERT INTO `guild_ranks` (`name`, `level`, `guild_id`) VALUES (`Leader`, 3, NEW.`id`);\
	INSERT INTO `guild_ranks` (`name`, `level`, `guild_id`) VALUES (`Vice-Leader`, 2, NEW.`id`);\
	INSERT INTO `guild_ranks` (`name`, `level`, `guild_id`) VALUES (`Member`, 1, NEW.`id`);\
END;",

				"CREATE TRIGGER `oncreate_players`\
AFTER INSERT\
ON `players`\
BEGIN\
	INSERT INTO `player_skills` (`player_id`, `skillid`, `value`) VALUES (NEW.`id`, 0, 10);\
	INSERT INTO `player_skills` (`player_id`, `skillid`, `value`) VALUES (NEW.`id`, 1, 10);\
	INSERT INTO `player_skills` (`player_id`, `skillid`, `value`) VALUES (NEW.`id`, 2, 10);\
	INSERT INTO `player_skills` (`player_id`, `skillid`, `value`) VALUES (NEW.`id`, 3, 10);\
	INSERT INTO `player_skills` (`player_id`, `skillid`, `value`) VALUES (NEW.`id`, 4, 10);\
	INSERT INTO `player_skills` (`player_id`, `skillid`, `value`) VALUES (NEW.`id`, 5, 10);\
	INSERT INTO `player_skills` (`player_id`, `skillid`, `value`) VALUES (NEW.`id`, 6, 10);\
END;",
				"CREATE TRIGGER `ondelete_accounts`\
BEFORE DELETE\
ON `accounts`\
FOR EACH ROW\
BEGIN\
	DELETE FROM `players` WHERE `account_id` = OLD.`id`;\
	DELETE FROM `account_viplist` WHERE `account_id` = OLD.`id`;\
	DELETE FROM `bans` WHERE `type` IN (3, 4) AND `value` = OLD.`id`;\
END;",

				"CREATE TRIGGER `ondelete_players`\
BEFORE DELETE\
ON `players`\
FOR EACH ROW\
BEGIN\
	SELECT RAISE(ROLLBACK, 'DELETE on table `players` violates foreign: `ownerid` from table `guilds`')\
	WHERE (SELECT `id` FROM `guilds` WHERE `ownerid` = OLD.`id`) IS NOT NULL;\
\
	DELETE FROM `account_viplist` WHERE `player_id` = OLD.`id`;\
	DELETE FROM `player_viplist` WHERE `player_id` = OLD.`id` OR `vip_id` = OLD.`id`;\
	DELETE FROM `player_storage` WHERE `player_id` = OLD.`id`;\
	DELETE FROM `player_skills` WHERE `player_id` = OLD.`id`;\
	DELETE FROM `player_items` WHERE `player_id` = OLD.`id`;\
	DELETE FROM `player_depotitems` WHERE `player_id` = OLD.`id`;\
	DELETE FROM `player_spells` WHERE `player_id` = OLD.`id`;\
	DELETE FROM `player_killers` WHERE `player_id` = OLD.`id`;\
	DELETE FROM `player_deaths` WHERE `player_id` = OLD.`id`;\
	DELETE FROM `guild_invites` WHERE `player_id` = OLD.`id`;\
	DELETE FROM `bans` WHERE `type` IN (2, 5) AND `value` = OLD.`id`;\
	UPDATE `houses` SET `owner` = 0 WHERE `owner` = OLD.`id`;\
END;",
				"CREATE TRIGGER `ondelete_guilds`\
BEFORE DELETE\
ON `guilds`\
FOR EACH ROW\
BEGIN\
	UPDATE `players` SET `guildnick` = '', `rank_id` = 0 WHERE `rank_id` IN (SELECT `id` FROM `guild_ranks` WHERE `guild_id` = OLD.`id`);\
	DELETE FROM `guild_ranks` WHERE `guild_id` = OLD.`id`;\
	DELETE FROM `guild_invites` WHERE `guild_id` = OLD.`id`;\
END;",

				"CREATE TRIGGER `oninsert_players` BEFORE INSERT ON `players` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'INSERT on table `players` violates foreign: `account_id`') WHERE NEW.`account_id` IS NULL OR (SELECT `id` FROM `accounts` WHERE `id` = NEW.`account_id`) IS NULL; END;",
				"CREATE TRIGGER `onupdate_players` BEFORE UPDATE ON `players` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'UPDATE on table `players` violates foreign: `account_id`') WHERE NEW.`account_id` IS NULL OR (SELECT `id` FROM `accounts` WHERE `id` = NEW.`account_id`) IS NULL; END;",

				"CREATE TRIGGER `oninsert_guilds` BEFORE INSERT ON `guilds` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'INSERT on table `guilds` violates foreign: `ownerid`') WHERE NEW.`ownerid` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`ownerid`) IS NULL; END;",
				"CREATE TRIGGER `onupdate_guilds` BEFORE UPDATE ON `guilds` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'UPDATE on table `guilds` violates foreign: `ownerid`') WHERE NEW.`ownerid` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`ownerid`) IS NULL; END;",

				"CREATE TRIGGER `ondelete_houses` BEFORE DELETE ON `houses` FOR EACH ROW BEGIN DELETE FROM `house_lists` WHERE `house_id` = OLD.`id`; END;",
				"CREATE TRIGGER `ondelete_tiles` BEFORE DELETE ON `tiles` FOR EACH ROW BEGIN DELETE FROM `tile_items` WHERE `tile_id` = OLD.`id`; END;",

				"CREATE TRIGGER `oninsert_guild_ranks` BEFORE INSERT ON `guild_ranks` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'INSERT on table `guild_ranks` violates foreign: `guild_id`') WHERE NEW.`guild_id` IS NULL OR (SELECT `id` FROM `guilds` WHERE `id` = NEW.`guild_id`) IS NULL; END;",
				"CREATE TRIGGER `onupdate_guild_ranks` BEFORE UPDATE ON `guild_ranks` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'UPDATE on table `guild_ranks` violates foreign: `guild_id`') WHERE NEW.`guild_id` IS NULL OR (SELECT `id` FROM `guilds` WHERE `id` = NEW.`guild_id`) IS NULL; END;",

				"CREATE TRIGGER `oninsert_house_lists` BEFORE INSERT ON `house_lists` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'INSERT on table `house_lists` violates foreign: `house_id`') WHERE NEW.`house_id` IS NULL OR (SELECT `id` FROM `houses` WHERE `id` = NEW.`house_id`) IS NULL; END;",
				"CREATE TRIGGER `onupdate_house_lists` BEFORE UPDATE ON `house_lists` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'UPDATE on table `house_lists` violates foreign: `house_id`') WHERE NEW.`house_id` IS NULL OR (SELECT `id` FROM `houses` WHERE `id` = NEW.`house_id`) IS NULL; END;",

				"CREATE TRIGGER `oninsert_player_depotitems` BEFORE INSERT ON `player_depotitems` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'INSERT on table `player_depotitems` violates foreign: `player_id`') WHERE NEW.`player_id` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`player_id`) IS NULL; END;",
				"CREATE TRIGGER `onupdate_player_depotitems` BEFORE UPDATE ON `player_depotitems` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'UPDATE on table `player_depotitems` violates foreign: `player_id`') WHERE NEW.`player_id` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`player_id`) IS NULL; END;",

				"CREATE TRIGGER `oninsert_player_skills` BEFORE INSERT ON `player_skills` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'INSERT on table `player_skills` violates foreign: `player_id`') WHERE NEW.`player_id` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`player_id`) IS NULL; END;",
				"CREATE TRIGGER `onupdate_player_skills` BEFORE UPDATE ON `player_skills` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'UPDATE on table `player_skills` violates foreign: `player_id`') WHERE NEW.`player_id` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`player_id`) IS NULL; END;",

				"CREATE TRIGGER `oninsert_player_storage` BEFORE INSERT ON `player_storage` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'INSERT on table `player_storage` violates foreign: `player_id`') WHERE NEW.`player_id` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`player_id`) IS NULL; END;",
				"CREATE TRIGGER `onupdate_player_storage` BEFORE UPDATE ON `player_storage` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'UPDATE on table `player_storage` violates foreign: `player_id`') WHERE NEW.`player_id` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`player_id`) IS NULL; END;",

				"CREATE TRIGGER `oninsert_player_viplist` BEFORE INSERT ON `player_viplist` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'INSERT on table `player_viplist` violates foreign: `player_id`') WHERE NEW.`player_id` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`player_id`) IS NULL; SELECT RAISE(ROLLBACK, 'INSERT on table `player_viplist` violates foreign: `vip_id`') WHERE NEW.`vip_id` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`vip_id`) IS NULL; END;",
				"CREATE TRIGGER `onupdate_player_viplist` BEFORE UPDATE ON `player_viplist` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'UPDATE on table `player_viplist` violates foreign: `vip_id`') WHERE NEW.`vip_id` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`vip_id`) IS NULL; END;",

				"CREATE TRIGGER `oninsert_account_viplist` BEFORE INSERT ON `account_viplist` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'INSERT on table `account_viplist` violates foreign: `account_id`') WHERE NEW.`account_id` IS NULL OR (SELECT `id` FROM `accounts` WHERE `id` = NEW.`account_id`) IS NULL; SELECT RAISE(ROLLBACK, 'INSERT on table `account_viplist` violates foreign: `player_id`') WHERE NEW.`player_id` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`player_id`) IS NULL; END;",
				"CREATE TRIGGER `onupdate_account_viplist` BEFORE UPDATE ON `account_viplist` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'UPDATE on table `account_viplist` violates foreign: `player_id`') WHERE NEW.`player_id` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`player_id`) IS NULL; END;",

				"CREATE TRIGGER `oninsert_tile_items` BEFORE INSERT ON `tile_items` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'INSERT on table `tile_items` violates foreign: `tile_id`') WHERE NEW.`tile_id` IS NULL OR (SELECT `id` FROM `tiles` WHERE `id` = NEW.`tile_id`) IS NULL; END;",
				"CREATE TRIGGER `onupdate_tile_items` BEFORE UPDATE ON `tile_items` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'UPDATE on table `tile_items` violates foreign: `tile_id`') WHERE NEW.`tile_id` IS NULL OR (SELECT `id` FROM `tiles` WHERE `id` = NEW.`tile_id`) IS NULL; END;",

				"CREATE TRIGGER `oninsert_player_spells` BEFORE INSERT ON `player_spells` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'INSERT on table `player_spells` violates foreign: `player_id`') WHERE NEW.`player_id` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`player_id`) IS NULL; END;",
				"CREATE TRIGGER `onupdate_player_spells` BEFORE UPDATE ON `player_spells` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'UPDATE on table `player_spells` violates foreign: `player_id`') WHERE NEW.`player_id` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`player_id`) IS NULL; END;",
				"CREATE TRIGGER `oninsert_player_deaths` BEFORE INSERT ON `player_deaths` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'INSERT on table `player_deaths` violates foreign: `player_id`') WHERE NEW.`player_id` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`player_id`) IS NULL; END;",
				"CREATE TRIGGER `onupdate_player_deaths` BEFORE UPDATE ON `player_deaths` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'UPDATE on table `player_deaths` violates foreign: `player_id`') WHERE NEW.`player_id` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`player_id`) IS NULL; END;",

				"CREATE TRIGGER `oninsert_killers` BEFORE INSERT ON `killers` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'INSERT on table `killers` violates foreign: `death_id`') WHERE NEW.`death_id` IS NULL OR (SELECT `id` FROM `player_deaths` WHERE `id` = NEW.`death_id`) IS NULL; END;",
				"CREATE TRIGGER `onupdate_killers` BEFORE UPDATE ON `killers` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'UPDATE on table `killers` violates foreign: `death_id`') WHERE NEW.`death_id` IS NULL OR (SELECT `id` FROM `player_deaths` WHERE `id` = NEW.`death_id`) IS NULL; END;",
				"CREATE TRIGGER `oninsert_environment_killers` BEFORE INSERT ON `environment_killers` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'INSERT on table `enviroment_killers` violates foreign: `kill_id`') WHERE NEW.`kill_id` IS NULL OR (SELECT `id` FROM `killers` WHERE `id` = NEW.`kill_id`) IS NULL; END;",
				"CREATE TRIGGER `onupdate_environment_killers` BEFORE UPDATE ON `environment_killers` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'INSERT on table `enviroment_killers` violates foreign: `kill_id`') WHERE NEW.`kill_id` IS NULL OR (SELECT `id` FROM `killers` WHERE `id` = NEW.`kill_id`) IS NULL; END;",
				"CREATE TRIGGER `oninsert_player_killers` BEFORE INSERT ON `player_killers` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'INSERT on table `player_killers` violates foreign: `player_id`') WHERE NEW.`player_id` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`player_id`) IS NULL; SELECT RAISE(ROLLBACK, 'INSERT on table `player_killers` violates foreign: `kill_id`') WHERE NEW.`kill_id` IS NULL OR (SELECT `id` FROM `killers` WHERE `id` = NEW.`kill_id`) IS NULL; END;",
				"CREATE TRIGGER `onupdate_player_killers` BEFORE UPDATE ON `player_killers` FOR EACH ROW BEGIN SELECT RAISE(ROLLBACK, 'UPDATE on table `player_killers` violates foreign: `player_id`') WHERE NEW.`player_id` IS NULL OR (SELECT `id` FROM `players` WHERE `id` = NEW.`player_id`) IS NULL; SELECT RAISE(ROLLBACK, 'UPDATE on table `killers` violates foreign: `kill_id`') WHERE NEW.`kill_id` IS NULL OR (SELECT `id` FROM `killers` WHERE `id` = NEW.`kill_id`) IS NULL; END;"
			};

			DBQuery query;
			for(uint32_t i = 0; i < sizeof(triggerName) / sizeof(std::string); ++i)
			{
				if(!triggerExists(triggerName[i]))
				{
					std::clog << "> Trigger: " << triggerName[i] << " does not exist, creating it..." << std::endl;
					db->query(triggerStatement[i]);
				}
			}

			break;
		}

		case DATABASE_ENGINE_POSTGRESQL:
			//TODO: PostgreSQL support
			break;

		default:
			break;
	}
}
