#pragma once
#include "MysqlConnect.hpp"
#include "BinSemaphore.hpp"
#include <deque>
//#include <semaphore>
#include <mutex>
#include <thread>

namespace DBPool {

    class MySqlConnectPool
    {
    public:
        MySqlConnectPool() {
            
        }

        MysqlConnect*get()
        {
            mSem.acquire();  
            std::lock_guard<std::mutex> lk(mMutex);
            MysqlConnect*con =  mPool.front();
            mPool.pop_front();
            return con;
        }

        void put(MysqlConnect*con)
        {
            std::lock_guard<std::mutex> lk(mMutex);
            mPool.push_back(con);
            mSem.release();
        }

        int size() {
            std::lock_guard<std::mutex>lk(mMutex);
            return mPool.size();
        }

    private:
        std::deque<MysqlConnect*> mPool;
        //std::counting_semaphore<> mSem{0};
        CounterSema<10000> mSem{ 0 };
        std::mutex mMutex;
    };


    class DBProc
    {
    public:

        DBProc(MySqlConnectPool* pool)
        {
            mPool = pool;
            mConnect = pool->get();
        }

        ~DBProc() {
            mPool->put(mConnect);
            mConnect = nullptr;
        }

        MysqlExector*GetResult() { return mStore; }

        std::string GetOutParam(std::string name)
        {
            MysqlExector*etor  = GetResult();
            if(!etor) return "";
            return etor->OutParamValue(name);
        }

        /*
        name		要执行的存储过程名
        outparams	输出参数列表，按照存储过程的定义填写参数名随便，个数要相同
        format		输入参数格式化，按照存储过程定义顺序格式化
        */
        int Execute(const char* name, const char* pOutParams, const char* format, ...)
        {
            if (!mConnect)
            {
                std::cout << "Invalidate DATABASE connection!" << std::endl;
                return -1;
            }
            va_list ap;
            va_start(ap, format);
            int ret = this->ExecuteImpl(name, pOutParams, format, ap);
            va_end(ap);
            return ret;
        }

        int Execute_WithOutResult(const char* name, const char* pOutParams, const char* format, ...)
        {
            std::string new_output_params = "@result," + std::string(pOutParams);
            if (!mConnect)
            {
                std::cout << "Invalidate DATABASE connection!" << std::endl;
                return -1;
            }
            va_list ap;
            va_start(ap, format);
            int ret = this->ExecuteImpl(name, pOutParams, format, ap);
            va_end(ap);
            return ret;
        }

        int Query(std::string stringStream) {

            std::string strQuery;
            int n = mConnect->Escpae(strQuery, stringStream.c_str(), 0);
            std::cout << strQuery << ",orgstr:" << stringStream << std::endl;;

            int result = -1;
            if (!mStore) delete mStore;
            mStore = new MysqlExector();
            if (!mStore->SetConnector(mConnect))
            {
                std::cout << "SetConnector failure" << std::endl;
                result = -2;
            }
            else
            {
                long long enter = GetTickCount();
                if (!mStore->ExecQeury(mConnect, strQuery,""))
                {
                    //m_store->RollBack(); // 2016-04-20
                    result = -3;
                }
                else {
                    //m_store->Commit(); // 2016-04-20
                    result = 0;
                }
                long long tickCount = GetTickCount() - enter;
                if (tickCount > 100)
                {
                    std::cout << "[SQL]>" << strQuery << " DBID=" << _dbid << ", tickCount=" << tickCount << std::endl;
                }
            }

            if (m_isLog)
            {
                std::cout << "[SQL]>" << strQuery << " DBID=" << _dbid << ", @result==>>" << result << std::endl;
            }
            else
            {
                if ((0 != result))
                {
                    std::cout << "[SQL]>" << strQuery << " DBID=" << _dbid << ", @result==>>" << result << std::endl;
                }
            }
            return result;
        }

    private:
        MySqlConnectPool* mPool = nullptr;
        MysqlConnect    *mConnect = nullptr;
        MysqlExector    *mStore = nullptr;
        int _dbid = 0;
        bool m_isLog = true;
    private:
        int ExecuteImpl(const char* name, const char* pOutParams, const char* format, va_list ap)
        {
            if (!mConnect) {
                std::cout << " connect ptr = nullptr" << std::endl;
            }

            std::ostringstream stringStream;
            size_t len = (format == nullptr) ? 0: std::strlen(format);
            size_t i = 0;
            stringStream << "CALL " << name << "(";
            if (pOutParams && std::strlen(pOutParams)) {
                stringStream << pOutParams;
            }
            if (len) stringStream << ",";

            while (i < len)
            {
                if ('%' != format[i])
                {
                    stringStream << format[i++];
                    continue;
                }
                i++;
                if ('s' == format[i])
                {
                    const char* para = (const char*)va_arg(ap, const char*);
                    std::string str;
                    int ret = mConnect->Escpae(str, para, 0);
                    if (ret != 0)
                    {
                        //va_end(ap);
                        return -1;
                    }
                    stringStream << str;
                }
                else
                    if ('b' == format[i]) // binary string
                    {
                        const char* para = (const char*)va_arg(ap, const char*);
                        size_t paralen = (size_t)va_arg(ap, size_t);
                        std::string str;
                        int ret = mConnect->Escpae(str, para, paralen);
                        if (ret != 0)
                        {
                            //va_end(ap);
                            return -1;
                        }
                        stringStream << str;
                    }
                    else if ('d' == format[i])
                    {
                        int para = (int)va_arg(ap, int);
                        stringStream << para;
                    }
                    else if ('u' == format[i])
                    {
                        unsigned int para = (unsigned int)va_arg(ap, unsigned int);
                        stringStream << para;
                    }
                    else if ('l' == format[i])
                    {
                        if (i + 2 < len && 'l' == format[i + 1] && 'd' == format[i + 2])
                        {
                            int64_t para = (int64_t)va_arg(ap, int64_t);
                            stringStream << para;
                            i += 2;
                        }
                        else if (i + 2 < len && 'l' == format[i + 1] && 'u' == format[i + 2])
                        {
                            uint64_t para = (uint64_t)va_arg(ap, uint64_t);
                            stringStream << para;
                            i += 2;
                        }
                        else stringStream << format[i];
                    }
                    else if ('c' == format[i])
                    {
                        char para = (char)va_arg(ap, int);
                        stringStream << para;
                    }
                    else if ('f' == format[i])
                    {
                        float para = (float)va_arg(ap, double);
                        stringStream << para;
                    }
                i++;
            }
            //va_end(ap);
            stringStream << ')';

            std::string strQuery = stringStream.str();
            std::string strQueryResult;
            if (pOutParams && strlen(pOutParams)) {
                strQueryResult += pOutParams;
            }

            int result = -1;
            if (!mStore) delete mStore;
            mStore = new MysqlExector();
            if (!mStore->SetConnector(mConnect))
            {
                std::cout << "SetTransAction failure" << std::endl;;
                result = -2;
            }
            else
            {
                long long enter = GetTickCount();
                if (!mStore->ExecQeury(mConnect, strQuery, strQueryResult))
                {
                    //m_store->RollBack(); // 2016-04-20
                    result = -3;
                }else{
                    result = 0;
                }

                long long tickCount = GetTickCount() - enter;
                if (tickCount > 100)
                {
                    std::cout << "[SQL]>" << strQuery << " DBID=" << _dbid << ", tickCount=" << tickCount << std::endl;;
                }
            }

            if (m_isLog)
            {
                std::cout << "[SQL]>" << strQuery << " DBID=" << _dbid << ", @result==>>" << result << std::endl;;
            }
            else
            {
                if ((0 != result))
                {
                    std::cout << "[SQL]>" << strQuery << " DBID=" << _dbid << ", @result==>>" << result << std::endl;;
                }
            }
            return result;
        }
    };
}
