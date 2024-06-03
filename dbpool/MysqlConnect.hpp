#pragma once
#ifdef WIN32
#pragma warning(disable:4996)
#include <mysql.h> //文件位于 MySQL 提供的 C API 目录中
#include <mysqld_error.h>
#else
#include <mysql/mysql.h> //文件位于 MySQL 提供的 C API 目录中
#include <mysql/mysqld_error.h>
#endif
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <cstring>
#include <thread>

#ifndef WIN32

#include <time.h>
// 返回自系统开机以来的毫秒数（tick）
static unsigned long GetTickCount()
{
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);

	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

#endif


std::vector<std::string> split( const std::string& str, const std::string& delims, unsigned int maxSplits, bool preserveDelims = false)
{
    std::vector<std::string> ret;
    // Pre-allocate some space for performance
    ret.reserve(maxSplits ? maxSplits+1 : 10);    // 10 is guessed capacity for most case

    unsigned int numSplits = 0;

    // Use STL methods
    size_t start, pos;
    start = 0;
    do
    {
        pos = str.find_first_of(delims, start);
        if (pos == start)
        {
            // Do nothing
            start = pos + 1;
        }
        else if (pos == std::string::npos || (maxSplits && numSplits == maxSplits))
        {
            // Copy the rest of the string
            ret.push_back( str.substr(start) );
            break;
        }
        else
        {
            // Copy up to delimiter
            ret.push_back( str.substr(start, pos - start) );

            if(preserveDelims)
            {
                // Sometimes there could be more than one delimiter in a row.
                // Loop until we don't find any more delims
                size_t delimStart = pos, delimPos;
                delimPos = str.find_first_not_of(delims, delimStart);
                if (delimPos == std::string::npos)
                {
                    // Copy the rest of the string
                    ret.push_back( str.substr(delimStart) );
                }
                else
                {
                    ret.push_back( str.substr(delimStart, delimPos - delimStart) );
                }
            }

            start = pos + 1;
        }
        // parse up to next real data
        start = str.find_first_not_of(delims, start);
        ++numSplits;

    } while (pos != std::string::npos);
    return ret;
}
std::string join(std::vector<std::string> &vs,char c){
        if(vs.size() == 0) return "";
        if(vs.size() == 1) return vs[0];

        std::string ret;
        for(int i = 0;i < vs.size()-1;i++){
            ret += vs[i];
            if(i != (vs.size()-1))
                ret.append(c,1);
        }
        return ret;
    }

namespace DBPool
{
class MysqlInit{
public:
	MysqlInit()
	{
		init();
	}

	~MysqlInit() 
	{
		uninit();
	}
private:
    void init()
	{
        mysql_library_init(0, NULL, NULL);
    }

	void uninit() {
		mysql_library_end();
	}
};

class MysqlConnect
{
public:
    MysqlConnect(std::string host,std::string user,std::string password,std::string dbname,std::string charset,uint32_t port):
        mHost(host),mUser(user),mPasswd(password),mDbName(dbname),mCharset(charset),mPort(port)
    {

    }

    ~MysqlConnect(){
        Disconnect();
    }

    bool Connect()
    {
        //初始化数据结构
        if (NULL == (mConnect = mysql_init(mConnect)))
        {
            return false;
        }

        bool recon = true;
        mysql_options(mConnect, MYSQL_OPT_RECONNECT, (const char*)&recon);
	    mysql_options(mConnect, MYSQL_SET_CHARSET_NAME, mCharset.c_str());

        if (NULL == mysql_real_connect(mConnect, mHost.c_str(), mUser.c_str(), mPasswd.c_str(), mDbName.c_str(), mPort, NULL, CLIENT_MULTI_STATEMENTS /*| CLIENT_MULTI_RESULTS*/))
        {
            //LOG(ERROR) << "Connect Mysql Host=" << m_host << " dbname=" << m_dbname << " port=" << m_port << " failed, err=" << mysql_errno(m_conn) << ":" << mysql_error(m_conn);
            return false;
        }

        //设置字符集
        mysql_set_character_set(mConnect, mCharset.c_str());
        return true;
    }

    //中断连接
    bool Disconnect()
    {
        if (mConnect)
        {
            mysql_close(mConnect);
            mConnect = NULL;
        }
        return true;
    }

    //得到连接
    void * ReConnect()
    {
        if (mConnect == NULL)
        {
            return NULL;
        }

        Disconnect(); // 2016-4-15
        if (!Connect())
        {
            return NULL;
        }

        //LOG(INFO) << "ReConnect Mysql Host=" << m_host << " dbname=" << m_dbname << " port=" << m_port << " Success!!";
        return mConnect;
    }

	MYSQL *GetConnect() {
		return mConnect;
	}

    // string escape
    int Escpae(std::string& result, const char* param,size_t paramLen=0)
    {
        if (NULL == param)
        {
            return 1;
        }

        if (NULL == mConnect)
        {
            return 2;
        }

        if(paramLen==0)
            paramLen = std::strlen(param);
        char* safeString = new char[paramLen * 2 + 1];
        unsigned long n = mysql_real_escape_string(mConnect, safeString, param, paramLen);
        if ((unsigned long)-1 == n)
        {
            std::string m_err = mysql_error(mConnect);
            std::cout << "--Escpae Err=" << mysql_errno(mConnect) << " " << m_err << ", Reconnect DB!--" << std::endl;
            return 3;
        }

        safeString[n] = 0;
        result.assign(safeString, n);
        delete safeString;
        return 0;
    }

private:
    std::string mHost;
    std::string mUser;
    std::string mPasswd;
    std::string mDbName;
    std::string mCharset;
    uint32_t    mPort;

    MYSQL *mConnect = nullptr;
};


enum class FieldType
{
	CHAR = 1, INT = 2, DATETIME = 3, DOUBLE = 4, DEC = 5, UNKNOWN = 6
};

struct Field 
{
	std::string name;
	FieldType type;
	unsigned int length;
	//查询列表中的列位置
	unsigned int index;

	static FieldType SetFieldType(enum_field_types fieldtype)
	{
		FieldType type;
		switch (fieldtype)
		{
		case MYSQL_TYPE_STRING:
			//
		case MYSQL_TYPE_VAR_STRING:
			//
			//case MYSQL_TYPE_TEXT:
			//
		case MYSQL_TYPE_BLOB:
			//
		case MYSQL_TYPE_SET:
			//
		case MYSQL_TYPE_GEOMETRY:
			//
		case MYSQL_TYPE_NULL:
			type = FieldType::CHAR;
			break;
		case MYSQL_TYPE_TINY:
			//
		case MYSQL_TYPE_SHORT:
			//
		case MYSQL_TYPE_LONG:
			//
		case MYSQL_TYPE_INT24:
			//
		case MYSQL_TYPE_BIT:
			//
		case MYSQL_TYPE_ENUM:
			//
		case MYSQL_TYPE_YEAR:
		case MYSQL_TYPE_LONGLONG:
			type = FieldType::INT;
			break;
		case MYSQL_TYPE_DECIMAL:
			//
		case MYSQL_TYPE_NEWDECIMAL:
			type = FieldType::DEC;
			break;
		case MYSQL_TYPE_FLOAT:
			//
		case MYSQL_TYPE_DOUBLE:
			type = FieldType::DOUBLE;
			break;
		case MYSQL_TYPE_TIMESTAMP:
			//
		case MYSQL_TYPE_DATE:
			//
		case MYSQL_TYPE_TIME:
			type = FieldType::DATETIME;
			break;
		default:
			type = FieldType::UNKNOWN;
			break;
		}
		return type;
	}
};


using Row = std::vector<std::string>;

struct Result
{
    void clear()
    {
        column_meta.clear();
        column_name_index_map.clear();
        result_table.clear();
    }
	std::map<int,Field> column_meta;
    std::map<std::string,int> column_name_index_map;
	std::vector<Row> result_table;

	int column_cnt() { return column_meta.size(); }
	int row_cnt() { return result_table.size(); }

	std::string result(int row, int column) {
		return result_table[row][column];
	}

	int add_field(int index,Field f) {
		column_meta[index] = f;
        column_name_index_map[f.name] = index;
		return column_meta.size();
	}

    std::string result(int row,std::string column_name){
        if(column_name_index_map.find(column_name) == column_name_index_map.end())
            return "";//throw std::exception();
        int index_column = column_name_index_map[column_name];
        return result_table[row][index_column];
    }
};



    class MysqlExector
    {
    private:
        //指向  mysql 的连接指针
        MYSQL * m_connptr;

        //指向  mysql 的查询数据集
        //MYSQL_RES *m_resultptr;

        //操作影响的记录数
        my_ulonglong m_row;

        //错误代码
        int m_errno;

        //错误原因
        std::string m_err;

        //新的自增的序列号
        my_ulonglong m_increaseID;

        //事务提交模式
        bool m_autocommit;

        //字段索引和字段类型的对应表
        // enum  filedtype_t
        // {CHAR = 1,INT = 2,DATETIME = 3,DOUBLE = 4,DEC = 5,UNKNOWN = 6};
        struct typeset_t
        {
            std::string name;
            FieldType type;
            unsigned int length;
            //查询列表中的列位置
            unsigned int index;
            typeset_t() {
                index = 0;
                length = 0;
                type = FieldType::UNKNOWN;
            }
        };


        std::vector<Result> multiResult;
        Result outParamResult;

        //取得信息状态
        bool m_getstatus;


        //清除临时对象
        void Clear(){
            // m_recordset.clear();
            // m_fieldtype.clear();
            multiResult.clear();
            outParamResult.clear();
            SetIncreaseID(0);
        }

        //设置自增序列号
        void SetIncreaseID(long id) {
            m_increaseID = id;
        }

        uint64_t LastInsertId()
        {
            if (NULL == m_connptr)
            {
                return 0;
            }
            return mysql_insert_id(m_connptr);
        }

    public:
        MysqlExector():m_connptr(NULL),m_err(""), m_increaseID(0),
        m_autocommit(false), m_getstatus(false){

        }
        ~MysqlExector(){
            Clear();
        }

        std::vector<Result>& GetMultiResTable() {
            return multiResult;
        }

        size_t Result_Cnt(){
            return multiResult.size();
        }

        size_t Row_Cnt(int result_index = 0){
            multiResult[result_index].row_cnt();
        }
        
        size_t Column_Cnt(int result_index = 0){
            multiResult[result_index].column_cnt();
        }

            //设置连接对象
        bool SetConnector(MysqlConnect * conn){
            if (conn == 0)
            {
                return false;
            }

            m_connptr = (MYSQL *)conn->GetConnect();
            if (m_connptr == NULL)
            {
                return false;
            }

            //mysql_autocommit(m_connptr, m_autocommit); // 2016-4-20
            return true;
        }

            //得到当前执行状态
        bool GetStatus(){
            return m_getstatus;
        }

        const std::string What(){
            return m_err;
        }

        //
        std::string OutParamValue(std::string name){
            return outParamResult.result(0,name);
        }

        bool HandleData(MYSQL_RES *resultptr) 
        {            
            // TODO: BUGFIX
            if (nullptr == resultptr)
            {
                m_err = mysql_error(m_connptr);
                m_errno = mysql_errno(m_connptr);
                if(m_errno == 0 )
                    return true;

                std::cout << ">>> DB EEROR " << mysql_errno(m_connptr) << ":" << mysql_error(m_connptr) << std::endl;
                return false;
            }

            //得到查询返回的行数
            m_row = mysql_affected_rows(m_connptr);
            if (0 > m_row)
            {
                m_err = mysql_error(m_connptr);
                std::cout << ">>> DB EEROR " << mysql_errno(m_connptr) << ":" << mysql_error(m_connptr) << '\t'   << std::endl;
                return false;
            }

            //指向  mysql 的查询字段集
            MYSQL_FIELD *fieldptr = NULL;

            Result singleres;
            //取得各字段名和类型
            while ((fieldptr = mysql_fetch_field(resultptr)))
            {
                Field f;
                f.index = singleres.column_cnt();
                f.length = fieldptr->length;
                f.name = fieldptr->name;
                f.type = f.SetFieldType(fieldptr->type);
                singleres.add_field(f.index, f);
            }

            MYSQL_ROW currrow = NULL;
            while ((currrow = mysql_fetch_row(resultptr)))
            {
                //读行的记录
                const unsigned int colcount = mysql_num_fields(resultptr);
                Row row;
                for (unsigned int i = 0; i < colcount; ++i)
                {
                    row.push_back(currrow[i] ? currrow[i] : "NULL");
                }
                singleres.result_table.push_back(row);
            }

            this->multiResult.push_back(singleres);

            mysql_free_result(resultptr);
            return true;
        }

        bool ExecQeury(MysqlConnect * conn, const std::string &ddl,std::string outParams) 
        {
            //清除缓冲
            Clear();

            if (0 == mysql_real_query(m_connptr, ddl.c_str(), ddl.size()))
            {
                mysql_affected_rows(m_connptr);
                m_increaseID = mysql_insert_id(m_connptr);
            }
            else {
                m_err = mysql_error(m_connptr);
                m_errno = mysql_errno(m_connptr);
                std::cout << ">>> DB EEROR " << m_errno << ":" << mysql_error(m_connptr) << "\t,ddl=" << ddl << '\t' << std::endl;;
                if (m_errno >= 2000 && m_errno <= 2014) // 重连2016-04-20
                {
                    m_connptr = (MYSQL *)conn->ReConnect();
                    if (NULL == m_connptr)
                    {
                        return false;
                    }

                    if (0 == mysql_real_query(m_connptr, ddl.c_str(), ddl.size()))
                    {
                        mysql_affected_rows(m_connptr);
                        m_increaseID = mysql_insert_id(m_connptr);
                    }
                    else
                    {
                        m_err = mysql_error(m_connptr);
                        m_errno = mysql_errno(m_connptr);
                        std::cout << ">>> DB EEROR " << m_errno << ":" << mysql_error(m_connptr) << '\t' << ddl << std::endl;
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }

            bool next = false;
            do {
                MYSQL_RES * resultptr = mysql_store_result(m_connptr);
                bool ret = this->HandleData(resultptr);
                if (!ret) 
                    return false;

                //mysql_use_result(m_connptr);
                // -1 - > 无
                // 0 -> 还有
                // > 0 -> 出错
                int flag = mysql_next_result(m_connptr);
                if (flag > 0) {
                    m_err = mysql_error(m_connptr);
                    m_errno = mysql_errno(m_connptr);
                    std::cout << "db-error:" << m_err << ",errno:" << m_errno << ",flags:" << flag << std::endl;;
                    return false;
                }
                else if (flag == 0)
                    next = true;
                else
                    next = false;
            } while (next);

            std::string resultQuery;
            if(outParams.size()){
                resultQuery = "select " + outParams;        
            }

            if(resultQuery.size())
            {
                std::cout << "sql:" << resultQuery << std::endl;
                mysql_query(m_connptr, resultQuery.c_str());
                MYSQL_RES * resultptr = mysql_store_result(m_connptr);
                if (NULL == resultptr)
                {
                    m_err = mysql_error(m_connptr);
                    std::cout << ">>> DB EEROR " << mysql_errno(m_connptr) << ":" << mysql_error(m_connptr) << '\t' << ddl << '\t' << resultQuery  << " ,err:" << m_err ;
                    return false;
                }

                int rowAffect = mysql_affected_rows(m_connptr);
                if (0 > rowAffect)
                {
                    m_err = mysql_error(m_connptr);
                    std::cout << ">>> DB EEROR " << mysql_errno(m_connptr) << ":" << mysql_error(m_connptr) << '\t' << ddl << '\t' << resultQuery;
                    return false;
                }

                            //指向  mysql 的查询字段集
                MYSQL_FIELD *fieldptr = NULL;

                //Result singleres;
                //取得各字段名和类型
                while ((fieldptr = mysql_fetch_field(resultptr)))
                {
                    Field f;
                    f.index = outParamResult.column_cnt();
                    f.length = fieldptr->length;
                    f.name = fieldptr->name;
                    f.type = f.SetFieldType(fieldptr->type);
                    outParamResult.add_field(f.index, f);
                }

                MYSQL_ROW currrow = NULL;
                while ((currrow = mysql_fetch_row(resultptr)))
                {
                    //读行的记录
                    const unsigned int colcount = mysql_num_fields(resultptr);
                    Row row;
                    for (unsigned int i = 0; i < colcount; ++i)
                    {
                        row.push_back(currrow[i] ? currrow[i] : "NULL");
                    }
                    outParamResult.result_table.push_back(row);
                }
                mysql_free_result(resultptr);                
            }
            return true;
        }

        //得到新自增的序列号
        my_ulonglong GetIncreaseID()
        {
            return m_increaseID;
        }

        //事务提交
        virtual bool Commit(){
            if (m_autocommit)
            {
                return true;
            }

            if (mysql_commit(m_connptr) == 0)
            {
                return true;
            }

            return false;
        }

        //事务回滚
        virtual bool RollBack()
        {
            if (m_autocommit)
            {
                return true;
            }

            if (mysql_rollback(m_connptr) == 0)
            {
                return true;
            }

            return false;
        }
    };
}   // end namespace DBPool
