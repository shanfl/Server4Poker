#include "../../dbpool/MySqlConnectPool.hpp"
using namespace DBPool;
int main()
{
    MysqlInit mysqlinitonce;

    MySqlConnectPool pool;
	for (int i = 0; i < 2; i++) {
        MysqlConnect*con = new MysqlConnect("127.0.0.1", "root", "3Flin@123", "test", "utf8mb4", 3306);
		if(con->Connect())
			pool.put(con);
		else {
			delete con;
		}
	}

    {
       // DBProc proc(&pool);
       // proc.Query("select * from t1;");
    }

    DBProc proc(&pool);
    proc.Execute("sp_123","@result,@res2",nullptr);

    std::string res = proc.GetOutParam("@result");
    std::string res2 = proc.GetOutParam("@res2");

    std::cout << "res:" << res << ", res2:" <<  res2 << std::endl;









    return 0;
}
