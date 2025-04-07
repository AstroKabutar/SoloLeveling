#ifndef MYSQL_H
#define MYSQL_H
#include <sstream>

// without these headers this header file wont compile
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

enum class Fetch;
enum class Data;

class Mysql
{
private:

    sql::mysql::MySQL_Driver *driver{};
    sql::Connection *con{};
    sql::ConnectOptionsMap connection_properties{};
    sql::Statement *stmt{};
    sql::ResultSet *res{};

    sql::SQLString hostName{};
    sql::SQLString userName{};
    sql::SQLString password{};
    sql::SQLString schema{};

    int port{};
    bool OPT_RECONNECT{};

    /*
    sql::SQLString hostName{"tcp://localhost:8000/Users"};
    sql::SQLString userName{"root"};
    sql::SQLString password{"Secure"};
    sql::SQLString schema{"Global"};
    bool OPT_RECONNECT{};
    */
public:
    Mysql();

    // for manipulating the data 
    void querry(const sql::SQLString& statement);

    // for using select statements
    void fetch(const sql::SQLString& statement, const Fetch& f);

    // for checking of a piece of data exists in db
    bool exists(const sql::SQLString& statement);

    // get pid
    int getpid(const sql::SQLString& statement);

    // template function to return data as requested
    template <typename T>
    T getdata(const sql::SQLString& statement, const Data& d);
};

enum class Data
{
    currentxp,
    tasks,
    reward,
    xp_required,
    level

};

template<typename T>
T Mysql::getdata(const sql::SQLString& statement, const Data& d)
{
    res = stmt->executeQuery(statement);
    T what{};
    std::stringstream os{};
    std::cout << "Querry \'" << statement << "\' successfully ran\n";
    res->next();

    switch (d)
    {
        case Data::currentxp:
            what = res->getDouble("currentxp");
        break;

        case Data::reward:
            what = res->getDouble("reward");
        break;

        case Data::tasks:
            os << res->getString("tasks");
            os >> what;
        break;

        case Data::xp_required:
            what = res->getDouble("xp_required");
        break;

        case Data::level:
            what = res->getInt("level");
        break;
    }

    return what;
}

/*
ID   --> get player id and name
LIST --> get a list of all the tasks owned by player
*/
enum class Fetch
{
    ID,
    LIST
};

#endif // !MYSQL_H


/*
hostName="tcp://localhost:8000/Users"
userName="root"
password="Secure"
schema="Users"
port=8000
OPT_RECONNECT=true
*/