#pragma once
#include "DataPacket.h"

class ProcessDB
{
    MYSQL* connection = NULL, conn;
    MYSQL_RES* res;
    MYSQL_ROW row;

public:
    void Init()
    {
        mysql_init(&conn);

        //mysql_set_character_set(&conn, "utf8mb4");
        connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);

        //mysql_query(connection, "set names euckr");

        //if (mysql_set_character_set(&conn, "utf8mb4") != 0) {
        //    fprintf(stderr, "charset 설정 실패: %s\n", mysql_error(&conn));
        //}
    }

    static inline void DrainResults(MYSQL* c) {
        while (mysql_more_results(c)) {
            mysql_next_result(c);
            if (MYSQL_RES* r = mysql_store_result(c)) mysql_free_result(r);
        }
    }

    static void LogStmtErr(const char* stage, MYSQL_STMT* s, MYSQL* c) {
        char buf[1024];
        _snprintf_s(buf, sizeof(buf), _TRUNCATE,
            "[mysql][%s] stmt_errno=%u stmt_error=%s | sqlstate=%s | conn_errno=%u conn_error=%s\n",
            stage,
            s ? mysql_stmt_errno(s) : 0, s ? mysql_stmt_error(s) : "(null)",
            s ? mysql_stmt_sqlstate(s) : "(null)",
            mysql_errno(c), mysql_error(c));
        OutputDebugStringA(buf);
    }


    static bool IsSafeIdent(const std::string& s) {
        if (s.empty() || s.size() > 64) return false;
        for (unsigned char c : s) {
            if (!(std::isalnum(c) || c == '_')) return false; // 영숫자/언더스코어만 허용
        }
        return true;
    }

    QUERY_RETURN_TYPE CreateNewTable(string DefalutTableName, string newTableName)
    {
        string query = "";

        query.append("create table " + DefalutTableName + "_" + newTableName + " like " + DB_NAME + "." + DefalutTableName + "; ");

        int query_stat = mysql_query(connection, query.c_str());

        //if (query_stat != 0)
        //{
        //    fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        //    return RETURN_ERROR;
        //}

        if (query_stat != 0)
            return RETURN_ERROR;

        if (mysql_affected_rows(connection) == 0)
            return RETURN_NONE;

        return RETURN_SUCCESS;
    }

    string SearchData(string tableName)
    {
        mysql_set_character_set(connection, "utf8mb4");

        string result = "";

        string query = "";

        query.append("select * from " + tableName + ";");

        mysql_query(connection, query.c_str());

        res = mysql_store_result(connection);

        while ((row = mysql_fetch_row(res)) != NULL)
        {
            result = row[0];
        }

        mysql_free_result(res);

        return result;
    }

    string SearchData(string tableName, string columnName, string whereCondition)
    {
        string result = "";

        string query = "";

        query.append("select " + columnName + " from " + tableName + " " + whereCondition + ";");

        mysql_query(connection, query.c_str());

        res = mysql_store_result(connection);

        while ((row = mysql_fetch_row(res)) != NULL)
        {
            result = row[0];
        }

        mysql_free_result(res);

        return result;
    }

    string SearchData(string tableName, string columnName, string whereConditionColumnName, string whereConditionData)
    {
        string result = "";

        string query = "";

        query.append("select " + columnName + " from " + tableName + " " + whereConditionColumnName + "'" + whereConditionData + "';");

        mysql_query(connection, query.c_str());

        res = mysql_store_result(connection);

        while ((row = mysql_fetch_row(res)) != NULL)
        {
            result = row[0];
        }

        mysql_free_result(res);

        return result;
    }

    vector<string> SearchData(string tableName, string columnName, string whereConditionColumnName, string whereConditionData, int columnSize)
    {
        vector<string> result;

        string query = "";

        query.append("select " + columnName + " from " + tableName + " " + whereConditionColumnName + "'" + whereConditionData + "';");

        mysql_query(connection, query.c_str());

        res = mysql_store_result(connection);

        while ((row = mysql_fetch_row(res)) != NULL)
        {
            for(int i = 0; i < columnSize; i++)
                result.push_back(row[i]);
        }

        mysql_free_result(res);

        return result;
    }

    //int SearchData(string tableName, string whereConditionColumnName, string whereConditionData)
    //{
    //    vector<string> result;

    //    string query = "";

    //    query.append("select * from " + tableName + " " + whereConditionColumnName + "'" + whereConditionData + "';");

    //    mysql_query(connection, query.c_str());

    //    res = mysql_store_result(connection);

    //    while ((row = mysql_fetch_row(res)) != NULL)
    //    {
    //        for (int i = 0; i < columnSize; i++)
    //            result.push_back(row[i]);
    //    }

    //    mysql_free_result(res);

    //    return result;
    //}

    vector<string> SearchData(string tableName, string columnName, vector<string> columns, vector<string> datas)
    {
        vector<string> result;

        string query = "";

        string tempWhereCondition = " where ";

        for (int i = 0; i < datas.size(); i++)
        {
            tempWhereCondition.append(columns[i] + " = '" + datas[i] + "'");

            if (i + 1 != datas.size())
                tempWhereCondition.append(" AND ");
        }

        query.append("select " + columnName + " from " + tableName + " " + tempWhereCondition + ";");

        mysql_query(connection, query.c_str());

        res = mysql_store_result(connection);

        while ((row = mysql_fetch_row(res)) != NULL)
        {
            result.push_back(row[0]);
        }

        mysql_free_result(res);

        return result;
    }

    list<string> SearchData(string tableName, string whereConditionColumnName, string whereConditionData, bool isBreak, int columnSize = 1)
    {
        list<string> result;

        string query = "";

        query.append("select * from " + tableName + " " + whereConditionColumnName + "'" + whereConditionData + "';");

        mysql_query(connection, query.c_str());

        res = mysql_store_result(connection);

        while ((row = mysql_fetch_row(res)) != NULL)
        {
            for (int i = 0; i < columnSize; i++)
            {
                result.push_back(row[i]);
            }

            if(isBreak)
                break;
        }

        mysql_free_result(res);

        return result;
    }

    vector<vector<string>> SearchData(string tableName, int columnSize, SEARCH_DIRECTION_TYPE _type = SEARCH_DIRECTION_TYPE::VERTICAL_TYPE)
    {
        mysql_set_character_set(connection, "utf8mb4");

        vector<vector<string>> result;

        switch (_type)
        {
        case VERTICAL_TYPE:
        {
            //세로로 1줄 씩 저장
            string query = "";

            for (int i = 0; i < columnSize; i++)
                result.push_back(vector<string>());

            query.append("select * from " + tableName);

            mysql_query(connection, query.c_str());

            res = mysql_store_result(connection);

            while ((row = mysql_fetch_row(res)) != NULL)
            {
                for (int i = 0; i < columnSize; i++)
                {
                    result[i].push_back(row[i]);
                }
            }

            mysql_free_result(res);

            //return result;
        }
            break;
        case HORIZON_TYPE:
        {
            //가로로 1줄 씩 저장
            string query = "";

            query.append("select * from " + tableName);

            mysql_query(connection, query.c_str());

            res = mysql_store_result(connection);

            int j = 0;
            while ((row = mysql_fetch_row(res)) != NULL)
            {
                result.push_back(vector<string>());
                for (int i = 0; i < columnSize; i++)
                {
                    result[j].push_back(row[i]);
                }
                j++;
            }

            mysql_free_result(res);

            //return result;
        }
            break;
        default:
            break;
        }

        return result;
    }

    vector<string> SearchData(string tableName, string columnName)
    {
        mysql_set_character_set(connection, "utf8mb4");

        vector<string> result;

        string query = "";

        query.append("select " + columnName + " from " + tableName);

        mysql_query(connection, query.c_str());

        res = mysql_store_result(connection);

        while ((row = mysql_fetch_row(res)) != NULL)
        {
            result.push_back(row[0]);
        }

        mysql_free_result(res);

        return result;
    }

    QUERY_RETURN_TYPE UpdateData(string tableName, vector<string> columns, vector<string> values, const string& whereColumn, const string& whereValue)
    {
        string query = "";
        
        string tempValueQuery = "";
        for (int i = 0; i < columns.size(); i++)
        {
            tempValueQuery += columns[i] + " = '" + values[i] + "',";
        }
        tempValueQuery.pop_back();

        query.append("update " + tableName + " set " + tempValueQuery + whereColumn + "'" + whereValue + "';");

        int query_stat = mysql_query(connection, query.c_str());

        //if (query_stat != 0)
        //{
        //    fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        //    return RETURN_ERROR;
        //}

        if (query_stat != 0)
            return RETURN_ERROR;

        //if (mysql_affected_rows(connection) == 0)
        //    return RETURN_NONE;

        return RETURN_SUCCESS;
    }

    QUERY_RETURN_TYPE UpdateData(string tableName, string column, string data, const string& whereColumn, const string& whereValue)
    {
        string query = "";

        query.append("update " + tableName + " set " + column + " = '" + data + "' " + whereColumn + "'" + whereValue + "';");

        int query_stat = mysql_query(connection, query.c_str());

        //if (query_stat != 0)
        //{
        //    fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        //    return RETURN_ERROR;
        //}

        if (query_stat != 0)
            return RETURN_ERROR;

        if (mysql_affected_rows(connection) == 0)
            return RETURN_NONE;

        return RETURN_SUCCESS;
    }

    QUERY_RETURN_TYPE UpdateData(string tableName, vector<string> columns, vector<string> values, const string& whereCondition)
    {
        string query = "";

        string tempValueQuery = "";
        for (int i = 0; i < columns.size(); i++)
        {
            tempValueQuery += columns[i] + " = '" + values[i] + "',";
        }
        tempValueQuery.pop_back();

        query.append("update " + tableName + " set " + tempValueQuery + whereCondition + ";");

        int query_stat = mysql_query(connection, query.c_str());

        //if (query_stat != 0)
        //{
        //    fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        //    return RETURN_ERROR;
        //}

        if (query_stat != 0)
            return RETURN_ERROR;

        if (mysql_affected_rows(connection) == 0)
            return RETURN_NONE;

        return RETURN_SUCCESS;
    }

    QUERY_RETURN_TYPE UpdateData(string tableName, string column, string data, const string& whereCondition)
    {
        string query = "";

        query.append("update " + tableName + " set " + column + " = '" + data + "' " + whereCondition + ";");

        int query_stat = mysql_query(connection, query.c_str());

        //if (query_stat != 0)
        //{
        //    fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        //    return RETURN_ERROR;
        //}

        if (query_stat != 0)
            return RETURN_ERROR;

        if (mysql_affected_rows(connection) == 0)
            return RETURN_NONE;

        return RETURN_SUCCESS;
    }

    QUERY_RETURN_TYPE InsertData(string tableName, string column, vector<string> values)
    {
        string query = "";
        
        string tempValueQuery = "";
        for (int i = 0; i < values.size(); i++)
            tempValueQuery += "'" + values[i] + "',";
        tempValueQuery.pop_back();

        query.append("insert into " + tableName + "(" + column + ") values (" + tempValueQuery + ");");

        int query_stat = mysql_query(connection, query.c_str());

        //if (query_stat != 0)
        //{
        //    fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        //    return RETURN_ERROR;
        //}

        if (query_stat != 0)
            return RETURN_ERROR;

        if (mysql_affected_rows(connection) == 0)
            return RETURN_NONE;

        return RETURN_SUCCESS;
    }

    QUERY_RETURN_TYPE InsertData(string tableName, string column, string value)
    {
        string query = "";

        query.append("insert into " + tableName + "(" + column + ") values ('" + value + "');");

        int query_stat = mysql_query(connection, query.c_str());

        //if (query_stat != 0)
        //{
        //    fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        //    return RETURN_ERROR;
        //}

        if (query_stat != 0)
            return RETURN_ERROR;

        if (mysql_affected_rows(connection) == 0)
            return RETURN_NONE;

        return RETURN_SUCCESS;
    }

    QUERY_RETURN_TYPE InsertInmateByCodeName(
        const std::string& prisonerNumber,
        const std::string& inmateName,
        const std::string& statusName /* 예: "수감" */)
    {
        const char* sql =
            "INSERT INTO inmate (PRISONER_NUMBER, INMATE_NAME, STATUS_CODE) "
            "SELECT ?, ?, c.CODE_KEY "
            "FROM code c "
            "WHERE c.CATEGORY='status' "
            "LIMIT 1";

        MYSQL_STMT* stmt = mysql_stmt_init(connection);
        if (!stmt) return RETURN_ERROR;
        if (mysql_stmt_prepare(stmt, sql, (unsigned long)strlen(sql)) != 0) {
            fprintf(stderr, "prepare: %s\n", mysql_stmt_error(stmt));
            mysql_stmt_close(stmt); return RETURN_ERROR;
        }

        MYSQL_BIND b[3]{}; unsigned long l0 = prisonerNumber.size(),
            l1 = inmateName.size(),
            l2 = statusName.size();
        b[0].buffer_type = MYSQL_TYPE_STRING; b[0].buffer = (void*)prisonerNumber.c_str(); b[0].length = &l0; b[0].buffer_length = l0;
        b[1].buffer_type = MYSQL_TYPE_STRING; b[1].buffer = (void*)inmateName.c_str();    b[1].length = &l1; b[1].buffer_length = l1;
        b[2].buffer_type = MYSQL_TYPE_STRING; b[2].buffer = (void*)statusName.c_str();    b[2].length = &l2; b[2].buffer_length = l2;

        if (mysql_stmt_bind_param(stmt, b) != 0) { fprintf(stderr, "bind: %s\n", mysql_stmt_error(stmt)); mysql_stmt_close(stmt); return RETURN_ERROR; }
        if (mysql_stmt_execute(stmt) != 0) { fprintf(stderr, "exec: %s\n", mysql_stmt_error(stmt)); mysql_stmt_close(stmt); return RETURN_ERROR; }

        my_ulonglong aff = mysql_stmt_affected_rows(stmt);
        mysql_stmt_close(stmt);
        return (aff == 1) ? RETURN_SUCCESS : RETURN_NONE; // 0이면 매칭되는 코드 없음
    }

    QUERY_RETURN_TYPE DeleteData(string tableName, string whereCondition)
    {
        string query = "";

        query.append("delete from " + tableName + " " + whereCondition);

        int query_stat = mysql_query(connection, query.c_str());

        //if (query_stat != 0)
        //{
        //    fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        //    return RETURN_ERROR;
        //}

        if (query_stat != 0)
            return RETURN_ERROR;

        if (mysql_affected_rows(connection) == 0)
            return RETURN_NONE;

        return RETURN_SUCCESS;
    }

    QUERY_RETURN_TYPE DeleteTable(string tableFrontName, string tableBackName)
    {
        string query = "";

        query.append("drop table " + tableFrontName + "_" + tableBackName);

        int query_stat = mysql_query(connection, query.c_str());

        //if (query_stat != 0)
        //{
        //    fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        //    return RETURN_ERROR;
        //}

        if (query_stat != 0)
            return RETURN_ERROR;

        return RETURN_SUCCESS;
    }

    vector<string> TableColumnNames(string schemaName, string tableName)
    {
        mysql_set_character_set(connection, "utf8mb4");

        vector<string> result;

        string query = "";

        query.append("SELECT COLUMN_NAME FROM information_schema.COLUMNS WHERE TABLE_SCHEMA = '" + schemaName + "' AND TABLE_NAME = '" + tableName + "' ORDER BY ORDINAL_POSITION");

        mysql_query(connection, query.c_str());

        res = mysql_store_result(connection);

        while ((row = mysql_fetch_row(res)) != NULL)
        {
            result.push_back(row[0]);
            //std::cout << row[0] << "\n";
        }

        mysql_free_result(res);

        return result;
    }

    bool SearchTableName(string tableName, string _dbName)
    {
        string result = "";

        string query = "";

        query.append("SELECT COUNT(*) FROM information_schema.TABLES WHERE TABLE_SCHEMA = '" + _dbName + "' AND TABLE_NAME = '" + tableName + "';");

        mysql_query(connection, query.c_str());

        res = mysql_store_result(connection);

        while ((row = mysql_fetch_row(res)) != NULL)
        {
            result = row[0];
        }

        mysql_free_result(res);

        return result == "1" ? true : false;
    }

    int SearchDataToCount(string tableName, vector<string> columns, vector<string> datas, string logicType)
    {
        mysql_set_character_set(connection, "utf8mb4");

        string result;

        string query = "";

        string tempWhereCondition = "where ";

        for (int i = 0; i < datas.size(); i++)
        {
            tempWhereCondition.append(columns[i] + " = '" + datas[i] + "'");

            if (i + 1 != datas.size())
                tempWhereCondition.append(" " + logicType + " ");
        }

        query.append("select count(*) from " + tableName + " " + tempWhereCondition + ";"); 

        mysql_query(connection, query.c_str());

        res = mysql_store_result(connection);

        while ((row = mysql_fetch_row(res)) != NULL)
        {
            result = row[0];
        }

        mysql_free_result(res);

        return stoi(result);
    }

    int SearchDataToCount(string tableName, string whereConditionColumnName, string whereConditionData)
    {
        string result;

        string query = "";

        query.append("select count(*) from " + tableName + " " + whereConditionColumnName + "'" + whereConditionData + "';");

        mysql_query(connection, query.c_str());

        res = mysql_store_result(connection);

        while ((row = mysql_fetch_row(res)) != NULL)
        {
            result = row[0];
        }

        mysql_free_result(res);

        return stoi(result);
    }

    string JoinSearchData(string searchColumnName, string fromTableName, string joinTableName, string fromColumnName)
    {
        string result = "";

        string query = "";

        query.append("select t2." + searchColumnName + " from " + fromTableName + " as t join " + joinTableName + " as t2 on t." + fromColumnName + " = t2.ID;");

        mysql_query(connection, query.c_str());

        res = mysql_store_result(connection);

        while ((row = mysql_fetch_row(res)) != NULL)
        {
            result = row[0];
        }

        mysql_free_result(res);

        return result;
    }

    unordered_map<string, vector<string>> JoinSearchData(vector<string> searchColumnNames, string selectT, string fromTableName, string joinTableName, string fromColumnName, string whereConditionColumnName, string whereConditionData)
    {
        unordered_map<string, vector<string>> result;

        string query = "";

        string searchColumnName = "";

        for (int i = 0; i < searchColumnNames.size(); i++)
        {
            result[searchColumnNames[i]] = vector<string>();
        }

        for (int i = 0; i < searchColumnNames.size(); i++)
        {
            searchColumnName.append(selectT + "." + searchColumnNames[i] + ",");
        }
        searchColumnName.pop_back();

        query.append("select " + searchColumnName + " from " + fromTableName + " as t join " + joinTableName + " as t2 on t." + fromColumnName + " = t2.ID " + whereConditionColumnName + "'" + whereConditionData + "';");

        mysql_query(connection, query.c_str());

        res = mysql_store_result(connection);

        while ((row = mysql_fetch_row(res)) != NULL)
        {
            for (int i = 0; i < searchColumnNames.size(); i++)
            {
                result[searchColumnNames[i]].push_back(row[i]);
            }
        }

        mysql_free_result(res);

        return result;
    }

    vector<string> LastSearchData(string tableName, int columnSize)
    {
        vector<string> result;

        string query = "";

        query.append("select * from " + tableName + " order by id desc limit 1");

        mysql_query(connection, query.c_str());

        res = mysql_store_result(connection);

        while ((row = mysql_fetch_row(res)) != NULL)
        {
            for (int i = 0; i < columnSize; i++)
            {
                result.push_back(row[i]);
            }
        }

        mysql_free_result(res);

        return result;
    }

    QUERY_RETURN_TYPE LogDataOptimization()
    {
        string query = "";

        query.append("DELETE FROM logdata WHERE ID < (SELECT ID FROM (SELECT ID FROM logdata ORDER BY ID DESC LIMIT 1 OFFSET 30) AS t);");

        int query_stat = mysql_query(connection, query.c_str());

        //if (query_stat != 0)
        //{
        //    fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        //    return RETURN_ERROR;
        //}

        if (query_stat != 0)
            return RETURN_ERROR;

        if (mysql_affected_rows(connection) == 0)
            return RETURN_NONE;

        return RETURN_SUCCESS;
    }
};