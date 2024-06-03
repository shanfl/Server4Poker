project(dbpool_test)


add_executable(mysqlcon main.cpp ../../dbpool/MysqlConnect.hpp ../../dbpool/BinSemaphore.hpp ../../dbpool/MySqlConnectPool.hpp)
target_link_libraries(mysqlcon mysqlclient)
