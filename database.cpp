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
#include <string>

#include "database.h"
#include "databasemysql.h"

boost::recursive_mutex DBQuery::databaseLock;
Database* _Database::m_instance = NULL;

Database* _Database::getInstance()
{
	if(!m_instance)
		m_instance = new DatabaseMySQL;

	m_instance->use();
	return m_instance;
}

DBResult* _Database::verifyResult(DBResult* result)
{
	if(result->next())
		return result;

	result->free();
	return NULL;
}

void DBInsert::setQuery(std::string query)
{
	m_query = query;
	m_buf = "";
	m_rows = 0;
}

bool DBInsert::addRow(std::string row)
{
	if(!m_db->multiLine())
		return m_db->query(m_query + "(" + row + ")");

	++m_rows;
	if(m_buf.empty())
		m_buf = "(" + row + ")";
	else if(m_buf.length() > 8192)
	{
		if(!execute())
			return false;

		m_buf = "(" + row + ")";
	}
	else
		m_buf += ",(" + row + ")";

	return true;
}

bool DBInsert::addRow(std::stringstream& row)
{
	bool ret = addRow(row.str());
	row.str("");
	return ret;
}

bool DBInsert::execute()
{
	if(!m_db->multiLine() || m_buf.empty() || !m_rows)
		return true;

	m_rows = 0;
	bool ret = m_db->query(m_query + m_buf);
	m_buf = "";
	return ret;
}
