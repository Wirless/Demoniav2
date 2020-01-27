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

#ifndef __CONST__
#define __CONST__
#include "definitions.h"

enum OperatingSystem_t
{
	CLIENTOS_LINUX				= 0x01,
	CLIENTOS_WINDOWS			= 0x02,
	CLIENTOS_FLASH				= 0x03,

	CLIENTOS_OTCLIENT_LINUX		= 0x0A,
	CLIENTOS_OTCLIENT_WINDOWS	= 0x0B,
	CLIENTOS_OTCLIENT_MAC		= 0x0C,
};

enum ReportType_t
{
	REPORT_NAME = 0x00,
	REPORT_STATEMENT = 0x01,
	REPORT_BOT = 0x02
};

enum MagicEffect_t
{
	MAGIC_EFFECT_DRAW_BLOOD			= 0x00,
	MAGIC_EFFECT_LOSE_ENERGY		= 0x01,
	MAGIC_EFFECT_POFF				= 0x02,
	MAGIC_EFFECT_BLOCKHIT			= 0x03,
	MAGIC_EFFECT_EXPLOSION_AREA		= 0x04,
	MAGIC_EFFECT_EXPLOSION_DAMAGE	= 0x05,
	MAGIC_EFFECT_FIRE_AREA			= 0x06,
	MAGIC_EFFECT_YELLOW_RINGS		= 0x07,
	MAGIC_EFFECT_POISON_RINGS		= 0x08,
	MAGIC_EFFECT_HIT_AREA			= 0x09,
	MAGIC_EFFECT_TELEPORT			= 0x0A, //10
	MAGIC_EFFECT_ENERGY_DAMAGE		= 0x0B, //11
	MAGIC_EFFECT_WRAPS_BLUE			= 0x0C, //12
	MAGIC_EFFECT_WRAPS_RED			= 0x0D, //13
	MAGIC_EFFECT_WRAPS_GREEN		= 0x0E, //14
	MAGIC_EFFECT_HITBY_FIRE			= 0x0F, //15
	MAGIC_EFFECT_POISON				= 0x10, //16
	MAGIC_EFFECT_MORT_AREA			= 0x11, //17
	MAGIC_EFFECT_SOUND_GREEN		= 0x12, //18
	MAGIC_EFFECT_SOUND_RED			= 0x13, //19
	MAGIC_EFFECT_POISON_AREA		= 0x14, //20
	MAGIC_EFFECT_SOUND_YELLOW		= 0x15, //21
	MAGIC_EFFECT_SOUND_PURPLE		= 0x16, //22
	MAGIC_EFFECT_SOUND_BLUE			= 0x17, //23
	MAGIC_EFFECT_SOUND_WHITE		= 0x18, //24
	MAGIC_EFFECT_BUBBLES = 25,
	MAGIC_EFFECT_CRAPS = 26,
	MAGIC_EFFECT_GIFT_WRAPS = 27,
	MAGIC_EFFECT_FIREWORK_YELLOW = 28,
	MAGIC_EFFECT_FIREWORK_RED = 29,
	MAGIC_EFFECT_FIREWORK_BLUE = 30,
	MAGIC_EFFECT_STUN = 31,
	MAGIC_EFFECT_SLEEP = 32,
	MAGIC_EFFECT_WATERCREATURE = 33,
	MAGIC_EFFECT_GROUNDSHAKER = 34,
	MAGIC_EFFECT_HEARTS = 35,
	MAGIC_EFFECT_FIREATTACK = 36,
	MAGIC_EFFECT_ENERGYAREA = 37,
	MAGIC_EFFECT_SMALLCLOUDS = 38,
	MAGIC_EFFECT_HOLYDAMAGE = 39,
	MAGIC_EFFECT_BIGCLOUDS = 40,
	MAGIC_EFFECT_ICEAREA = 41,
	MAGIC_EFFECT_ICETORNADO = 42,
	MAGIC_EFFECT_ICEATTACK = 43,
	MAGIC_EFFECT_STONES = 44,
	MAGIC_EFFECT_SMALLPLANTS = 45,
	MAGIC_EFFECT_CARNIPHILA = 46,
	MAGIC_EFFECT_PURPLEENERGY = 47,
	MAGIC_EFFECT_YELLOWENERGY = 48,
	MAGIC_EFFECT_HOLYAREA = 49,
	MAGIC_EFFECT_BIGPLANTS = 50,
	MAGIC_EFFECT_CAKE = 51,
	MAGIC_EFFECT_GIANTICE = 52,
	MAGIC_EFFECT_WATERSPLASH = 53,
	MAGIC_EFFECT_PLANTATTACK = 54,
	MAGIC_EFFECT_TUTORIALARROW = 55,
	MAGIC_EFFECT_TUTORIALSQUARE = 56,
	MAGIC_EFFECT_MIRRORHORIZONTAL = 57,
	MAGIC_EFFECT_MIRRORVERTICAL = 58,
	MAGIC_EFFECT_SKULLHORIZONTAL = 59,
	MAGIC_EFFECT_SKULLVERTICAL = 60,
	MAGIC_EFFECT_ASSASSIN = 61,
	MAGIC_EFFECT_STEPSHORIZONTAL = 62,
	MAGIC_EFFECT_BLOODYSTEPS = 63,
	MAGIC_EFFECT_STEPSVERTICAL = 64,
	MAGIC_EFFECT_YALAHARIGHOST = 65,
	MAGIC_EFFECT_BATS = 66,
	MAGIC_EFFECT_SMOKE = 67,
	MAGIC_EFFECT_INSECTS = 68,
	MAGIC_EFFECT_DRAGONHEAD = 69,
	MAGIC_EFFECT_ORCSHAMAN = 70,
	MAGIC_EFFECT_ORCSHAMAN_FIRE = 71,
	MAGIC_EFFECT_THUNDER = 72,
	MAGIC_EFFECT_FERUMBRAS = 73,
	MAGIC_EFFECT_CONFETTI_HORIZONTAL = 74,
	MAGIC_EFFECT_CONFETTI_VERTICAL = 75,
	// 77-157 are empty
	MAGIC_EFFECT_BLACKSMOKE = 76,
	MAGIC_EFFECT_NEW_SUDDENDEATH = 77,
	MAGIC_EFFECT_SKULLRX = 78,
	MAGIC_EFFECT_POGCHAMP = 79,

	/* new 	CONST_ME_SKULLRX = 78
	CONST_ME_POGCHAMP = 79 */
	MAGIC_EFFECT_LAST = MAGIC_EFFECT_POGCHAMP,

	//for internal use, dont send to client
	MAGIC_EFFECT_NONE				= 0xFF,
	MAGIC_EFFECT_UNKNOWN			= 0xFFFF
};

enum ShootEffect_t
{
	SHOOT_EFFECT_SPEAR			= 0x00,	//0????????????
	SHOOT_EFFECT_BOLT			= 0x01,	//1
	SHOOT_EFFECT_ARROW			= 0x02,	//2
	SHOOT_EFFECT_FIRE			= 0x03,	//3
	SHOOT_EFFECT_ENERGY			= 0x04,	//4
	SHOOT_EFFECT_POISONARROW	= 0x05,	//5
	SHOOT_EFFECT_BURSTARROW		= 0x06,	//6
	SHOOT_EFFECT_THROWINGSTAR	= 0x07,	//7
	SHOOT_EFFECT_THROWINGKNIFE	= 0x08,	//8
	SHOOT_EFFECT_SMALLSTONE		= 0x09,	//9
	SHOOT_EFFECT_DEATH			= 0x0A, //10
	SHOOT_EFFECT_LARGEROCK		= 0x0B, //11
	SHOOT_EFFECT_SNOWBALL		= 0x0C, //12
	SHOOT_EFFECT_POWERBOLT		= 0x0D, //13
	SHOOT_EFFECT_POISONFIELD	= 0x0E, //14
//EXE	SHOOT_EFFECT_SUDDENDEATH	= 0x0F, //15
	SHOOT_EFFECT_INFERNALBOLT	= 0x0F, //16 brokenbolt if not working switch with SWORD EFFECT 
	SHOOT_EFFECT_SWORD			= 0x10, //17
	SHOOT_EFFECT_AXE			= 0x11, //18
	SHOOT_EFFECT_CLUB			= 0x12, //19
	SHOOT_EFFECT_ETHEREALSPEAR	= 0x13, //20
	SHOOT_EFFECT_FRIGO			= 0x14, //21
	SHOOT_EFFECT_TERRA			= 0x15, //22
	SHOOT_EFFECT_SAN			= 0x16, //23
	SHOOT_EFFECT_DEATHX			= 0x17, //24
	SHOOT_EFFECT_ARROWVIS		= 0x18, //25
	SHOOT_EFFECT_ARROWFIRE		= 0x19, //26
	SHOOT_EFFECT_ARROWICE		= 0x1A, //27
	SHOOT_EFFECT_VISDX			= 0x1B, //28
	SHOOT_EFFECT_FRIGOX			= 0x1C, //29
	SHOOT_EFFECT_HOLYSAN		= 0x1D, //30
	SHOOT_EFFECT_EARTHX			= 0x1E, //31
	SHOOT_EFFECT_ASSASSINSTAR	= 0x1F, //32?
	/*TO DO
EFFECTS INTERNAL CONST LIB
	*/
	
	SHOOT_EFFECT_LAST			= SHOOT_EFFECT_ASSASSINSTAR,

	//for internal use, dont send to client
	SHOOT_EFFECT_WEAPONTYPE		= 0xFE, //254
	SHOOT_EFFECT_NONE			= 0xFF,
	SHOOT_EFFECT_UNKNOWN		= 0xFFFF
};

enum MessageClasses
{
	MSG_NONE					= 0x00,

	MSG_SPEAK_SAY				= 0x01,
	MSG_SPEAK_WHISPER			= 0x02,
	MSG_SPEAK_YELL				= 0x03,
	MSG_SPEAK_PRIVATE			= 0x04,
	MSG_CHANNEL_Y				= 0x05,
	MSG_CHANNEL_RVR				= 0x06,
	MSG_SPEAK_ANSWER_RVR		= 0x07,
	MSG_CONTINUE_RVR			= 0x08,
	MSG_BROADCAST				= 0x09,
	MSG_CHANNEL_RN				= 0x0A,
	MSG_SPEAK_PRIVATE_RED		= 0x0B,
	MSG_CHANNEL_O				= 0x0C,
	MSG_CHANNEL_W				= 0x0D,
	MSG_CHANNEL_RA				= 0x0E,
	MSG_SPEAK_MONSTER_SAY		= 0x10,
	MSG_SPEAK_MONSTER_YELL		= 0x11,

	MSG_SPEAK_FIRST				= MSG_SPEAK_SAY,
	MSG_SPEAK_LAST				= MSG_CHANNEL_RA,
	MSG_SPEAK_MONSTER_FIRST		= MSG_SPEAK_MONSTER_SAY,
	MSG_SPEAK_MONSTER_LAST		= MSG_SPEAK_MONSTER_YELL,

	MSG_EVENT_ORANGE			= 0x10,	/*Orange message in the console*/
	MSG_STATUS_CONSOLE_ORANGE	= 0x11,	/*Orange message in the console*/
	MSG_STATUS_WARNING			= 0x12,	/*Red message in game window and in the console*/
	MSG_EVENT_ADVANCE			= 0x13,	/*White message in game window and in the console*/
	MSG_EVENT_DEFAULT			= 0x14,	/*White message at the bottom of the game window and in the console*/
	MSG_STATUS_DEFAULT			= 0x15,	/*White message at the bottom of the game window and in the console*/
	MSG_INFO_DESCR				= 0x16,	/*Green message in game window and in the console*/
	MSG_STATUS_SMALL			= 0x17,	/*White message at the bottom of the game window"*/
	MSG_STATUS_CONSOLE_BLUE		= 0x18,	/*Blue message in the console*/
	MSG_STATUS_CONSOLE_RED		= 0x19	/*Red message in the console*/
};

enum FluidColors_t
{
	FLUID_EMPTY		= 0x00,
	FLUID_BLUE		= 0x01,
	FLUID_RED		= 0x02,
	FLUID_BROWN		= 0x03,
	FLUID_GREEN		= 0x04,
	FLUID_YELLOW	= 0x05,
	FLUID_WHITE		= 0x06,
	FLUID_PURPLE	= 0x07
};

enum FluidTypes_t
{
	FLUID_NONE			= FLUID_EMPTY,
	FLUID_WATER			= FLUID_BLUE,
	FLUID_BLOOD			= FLUID_RED,
	FLUID_BEER			= FLUID_BROWN,
	FLUID_SLIME			= FLUID_GREEN,
	FLUID_LEMONADE		= FLUID_YELLOW,
	FLUID_MILK			= FLUID_WHITE,
	FLUID_MANA			= FLUID_PURPLE,

	FLUID_LIFE			= FLUID_RED + 8,
	FLUID_OIL			= FLUID_BROWN + 8,
	FLUID_URINE			= FLUID_YELLOW + 8,
	FLUID_COCONUTMILK	= FLUID_WHITE + 8,
	FLUID_WINE			= FLUID_PURPLE + 8,

	FLUID_MUD			= FLUID_BROWN + 16,
	FLUID_FRUITJUICE	= FLUID_YELLOW + 16,

	FLUID_LAVA			= FLUID_RED + 24,
	FLUID_RUM			= FLUID_BROWN + 24,
	FLUID_SWAMP			= FLUID_GREEN + 24,

	FLUID_TEA			= FLUID_BROWN + 32,
	FLUID_MEAD			= FLUID_BROWN + 40
};

const uint8_t reverseFluidMap[] =
{
	FLUID_EMPTY,
	FLUID_WATER,
	FLUID_MANA,
	FLUID_BEER,
	FLUID_EMPTY,
	FLUID_BLOOD,
	FLUID_SLIME,
	FLUID_EMPTY,
	FLUID_LEMONADE,
	FLUID_MILK
};

enum ClientFluidTypes_t
{
	CLIENTFLUID_EMPTY	= 0x00,
	CLIENTFLUID_BLUE	= 0x01,
	CLIENTFLUID_RED		= 0x02,
	CLIENTFLUID_BROWN	= 0x03,
	CLIENTFLUID_GREEN	= 0x04,
	CLIENTFLUID_YELLOW	= 0x05,
	CLIENTFLUID_WHITE	= 0x06,
	CLIENTFLUID_PURPLE	= 0x07
};

const uint8_t fluidMap[] =
{
	CLIENTFLUID_EMPTY,
	CLIENTFLUID_BLUE,
	CLIENTFLUID_RED,
	CLIENTFLUID_BROWN,
	CLIENTFLUID_GREEN,
	CLIENTFLUID_YELLOW,
	CLIENTFLUID_WHITE,
	CLIENTFLUID_PURPLE
};

enum Color_t
{
	COLOR_BLACK			= 0,
	COLOR_BLUE			= 5,
	COLOR_GREEN			= 18,
	COLOR_LIGHTGREEN	= 66,
	COLOR_DARKBROWN		= 78,
	COLOR_LIGHTBLUE		= 89,
	COLOR_ICEBLUE		= 94,
	COLOR_MAYABLUE		= 95,
	COLOR_DARKRED		= 108,
	COLOR_DARKPURPLE	= 112,
	COLOR_BROWN			= 120,
	COLOR_GREY			= 129,
	COLOR_TEAL			= 143,
	COLOR_DARKPINK		= 152,
	COLOR_PURPLE		= 154,
	COLOR_DARKORANGE	= 156,
	COLOR_RED			= 180,
	COLOR_PINK			= 190,
	COLOR_ORANGE		= 192,
	COLOR_DARKYELLOW	= 205,
	COLOR_YELLOW		= 210,
	COLOR_WHITE			= 215,

	COLOR_NONE			= 255,
	COLOR_UNKNOWN		= 256
};

enum Icons_t
{
	ICON_NONE		= 0,
	ICON_POISON		= 1 << 0,
	ICON_BURN		= 1 << 1,
	ICON_ENERGY		= 1 << 2,
	ICON_DRUNK		= 1 << 3,
	ICON_MANASHIELD	= 1 << 4,
	ICON_PARALYZE	= 1 << 5,
	ICON_HASTE		= 1 << 6,
	ICON_SWORDS		= 1 << 7
};

enum skills_t
{
	SKILL_NONE = -1,
	SKILL_FIRST = 0,
	SKILL_FIST = SKILL_FIRST,
	SKILL_CLUB,
	SKILL_SWORD,
	SKILL_AXE,
	SKILL_DIST,
	SKILL_SHIELD,
	SKILL_FISH,
	SKILL__MAGLEVEL,
	SKILL__LEVEL,
	SKILL__EXPERIENCE,
	SKILL_LAST = SKILL_FISH,
	SKILL__LAST = SKILL__EXPERIENCE
};

enum WeaponType_t
{
	WEAPON_NONE = 0,
	WEAPON_SWORD,
	WEAPON_CLUB,
	WEAPON_AXE,
	WEAPON_DIST,
	WEAPON_SHIELD,
	WEAPON_FIST,
	WEAPON_WAND,
	WEAPON_AMMO
};

enum Ammo_t
{
	AMMO_NONE = 0,
	AMMO_BOLT,
	AMMO_ARROW,
	AMMO_SPEAR,
	AMMO_THROWINGSTAR,
	AMMO_THROWINGKNIFE,
	AMMO_STONE,
	AMMO_SNOWBALL,
	AMMO_ASSASSINSTAR
};

enum AmmoAction_t
{
	AMMOACTION_NONE = 0,
	AMMOACTION_REMOVECOUNT,
	AMMOACTION_REMOVECHARGE,
	AMMOACTION_MOVE,
	AMMOACTION_MOVEBACK
};

enum WieldInfo_t
{
	WIELDINFO_LEVEL		= 1,
	WIELDINFO_MAGLV		= 2,
	WIELDINFO_VOCREQ	= 4,
	WIELDINFO_PREMIUM	= 8
};

enum Skulls_t
{
	SKULL_NONE = 0,
	SKULL_YELLOW,
	SKULL_GREEN,
	SKULL_WHITE,
	SKULL_RED,
	SKULL_LAST = SKULL_RED
};

enum PartyShields_t
{
	SHIELD_NONE = 0,
	SHIELD_WHITEYELLOW,
	SHIELD_WHITEBLUE,
	SHIELD_BLUE,
	SHIELD_YELLOW,
	SHIELD_LAST = SHIELD_YELLOW
};

enum SpellGroup_t
{
	SPELLGROUP_NONE		= 0,
	SPELLGROUP_ATTACK	= 1,
	SPELLGROUP_HEALING	= 2,
	SPELLGROUP_SUPPORT	= 3,
	SPELLGROUP_SPECIAL	= 4
};

enum item_t
{
	ITEM_FIREFIELD			= 1487,
	ITEM_FIREFIELD_SAFE		= 1500,

	ITEM_POISONFIELD		= 1490,
	ITEM_POISONFIELD_SAFE	= 1503,

	ITEM_ENERGYFIELD		= 1491,
	ITEM_ENERGYFIELD_SAFE	= 1504,

	ITEM_MAGICWALL			= 1497,
	ITEM_MAGICWALL_SAFE		= ITEM_MAGICWALL,

	ITEM_WILDGROWTH			= 1499,
	ITEM_WILDGROWTH_SAFE	= ITEM_WILDGROWTH,

	ITEM_DEPOT				= 2594,
	ITEM_LOCKER				= 2589,

	ITEM_MALE_CORPSE		= 3058,
	ITEM_FEMALE_CORPSE		= 3065,

	ITEM_FULLSPLASH			= 2016,
	ITEM_SMALLSPLASH		= 2019,

	ITEM_PARCEL				= 2595,
	ITEM_PARCEL_STAMPED		= 2596,
	ITEM_LETTER				= 2597,
	ITEM_LETTER_STAMPED		= 2598,
	ITEM_LABEL				= 2599,

	ITEM_STEALTH_RING		= 2202,
	ITEM_HOUSE_TRANSFER		= 1968 //read-only
};

enum PlayerFlags
{
	PlayerFlag_CannotUseCombat = 0,			//2^0 = 1
	PlayerFlag_CannotAttackPlayer,			//2^1 = 2
	PlayerFlag_CannotAttackMonster,			//2^2 = 4
	PlayerFlag_CannotBeAttacked,			//2^3 = 8
	PlayerFlag_CanConvinceAll,				//2^4 = 16
	PlayerFlag_CanSummonAll,				//2^5 = 32
	PlayerFlag_CanIllusionAll,				//2^6 = 64
	PlayerFlag_CanSenseInvisibility,		//2^7 = 128
	PlayerFlag_IgnoredByMonsters,			//2^8 = 256
	PlayerFlag_NotGainInFight,				//2^9 = 512
	PlayerFlag_HasInfiniteMana,				//2^10 = 1024
	PlayerFlag_HasInfiniteSoul,				//2^11 = 2048
	PlayerFlag_HasNoExhaustion,				//2^12 = 4096
	PlayerFlag_CannotUseSpells,				//2^13 = 8192
	PlayerFlag_CannotPickupItem,			//2^14 = 16384
	PlayerFlag_CanAlwaysLogin,				//2^15 = 32768
	PlayerFlag_CanBroadcast,				//2^16 = 65536
	PlayerFlag_CanEditHouses,				//2^17 = 131072
	PlayerFlag_CannotBeBanned,				//2^18 = 262144
	PlayerFlag_CannotBePushed,				//2^19 = 524288
	PlayerFlag_HasInfiniteCapacity,			//2^20 = 1048576
	PlayerFlag_CanPushAllCreatures,			//2^21 = 2097152
	PlayerFlag_CanTalkRedPrivate,			//2^22 = 4194304
	PlayerFlag_CanTalkRedChannel,			//2^23 = 8388608
	PlayerFlag_TalkOrangeHelpChannel,		//2^24 = 16777216
	PlayerFlag_NotGainExperience,			//2^25 = 33554432
	PlayerFlag_NotGainMana,					//2^26 = 67108864
	PlayerFlag_NotGainHealth,				//2^27 = 134217728
	PlayerFlag_NotGainSkill,				//2^28 = 268435456
	PlayerFlag_SetMaxSpeed,					//2^29 = 536870912
	PlayerFlag_SpecialVIP,					//2^30 = 1073741824
	PlayerFlag_NotGenerateLoot,				//2^31 = 2147483648
	PlayerFlag_CanTalkRedChannelAnonymous,	//2^32 = 4294967296
	PlayerFlag_IgnoreProtectionZone,		//2^33 = 8589934592
	PlayerFlag_IgnoreSpellCheck,			//2^34 = 17179869184
	PlayerFlag_IgnoreEquipCheck,			//2^35 = 34359738368
	PlayerFlag_CannotBeMuted,				//2^36 = 68719476736
	PlayerFlag_IsAlwaysPremium,				//2^37 = 137438953472
	PlayerFlag_CanAnswerRuleViolations,		//2^38 = 274877906944
	PlayerFlag_39,							//2^39 = 549755813888 //not used by us
	PlayerFlag_ShowGroupNameInsteadOfVocation,	//2^40 = 1099511627776
	PlayerFlag_HasInfiniteStamina,			//2^41 = 2199023255552
	PlayerFlag_CannotMoveItems,				//2^42 = 4398046511104
	PlayerFlag_CannotMoveCreatures,			//2^43 = 8796093022208
	PlayerFlag_CanReportBugs,				//2^44 = 17592186044416
	PlayerFlag_45,							//2^45 = 35184372088832 //not used by us
	PlayerFlag_CannotBeSeen,				//2^46 = 70368744177664
	PlayerFlag_HideHealth,					//2^47 = 140737488355328
	PlayerFlag_CanPassThroughAllCreatures,	//2^48 = 281474976710656

	PlayerFlag_LastFlag
};

enum PlayerCustomFlags
{
	PlayerCustomFlag_AllowIdle = 0,				//2^0 = 1
	PlayerCustomFlag_CanSeePosition,			//2^1 = 2
	PlayerCustomFlag_CanSeeItemDetails,			//2^2 = 4
	PlayerCustomFlag_CanSeeCreatureDetails,		//2^3 = 8
	PlayerCustomFlag_NotSearchable,				//2^4 = 16
	PlayerCustomFlag_GamemasterPrivileges,		//2^5 = 32
	PlayerCustomFlag_CanThrowAnywhere,			//2^6 = 64
	PlayerCustomFlag_CanPushAllItems,			//2^7 = 128
	PlayerCustomFlag_CanMoveAnywhere,			//2^8 = 256
	PlayerCustomFlag_CanMoveFromFar,			//2^9 = 512
	PlayerCustomFlag_CanUseFar,					//2^10 = 1024
	PlayerCustomFlag_CanLoginMultipleCharacters,//2^11 = 2048 (account flag)
	PlayerCustomFlag_CanLogoutAnytime,			//2^12 = 4096 (account flag)
	PlayerCustomFlag_HideLevel,					//2^13 = 8192
	PlayerCustomFlag_IsProtected,				//2^14 = 16384
	PlayerCustomFlag_IsImmune,					//2^15 = 32768
	PlayerCustomFlag_NotGainSkull,				//2^16 = 65536
	PlayerCustomFlag_NotGainUnjustified,		//2^17 = 131072
	PlayerCustomFlag_IgnorePacification,		//2^18 = 262144
	PlayerCustomFlag_IgnoreLoginDelay,			//2^19 = 524288
	PlayerCustomFlag_CanStairhop,				//2^20 = 1048576
	PlayerCustomFlag_CanTurnhop,				//2^21 = 2097152
	PlayerCustomFlag_IgnoreHouseRent,			//2^22 = 4194304
	PlayerCustomFlag_CanWearAllAddons,			//2^23 = 8388608
	PlayerCustomFlag_IsWalkable,				//2^24 = 16777216
	PlayerCustomFlag_CanUseAllMounts,			//2^25 = 33554432
	PlayerCustomFlag_HasFullLight,				//2^26 = 67108864

	PlayerCustomFlag_LastFlag
};

#define NETWORK_CRYPTOHEADER_SIZE 8
#define NETWORK_RETRY_TIMEOUT 5000
#define NETWORK_DEFAULT_SIZE 4096
#define NETWORK_HEADER_SIZE 2
#define NETWORK_MAX_SIZE 24576

#define IPBAN_FLAG 128
#define LOCALHOST 2130706433
#define SWIMMING_OUTFIT 267
#define GRATIS_PREMIUM 65535

#endif
