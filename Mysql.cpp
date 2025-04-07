#include <iostream>
#include <sstream>
#include <cstdlib>
#include <Mysql.h>

Mysql::Mysql()
{
    // get env variable values
    const char* temp{};

    temp = std::getenv("hostName");
    hostName = temp;

    temp = std::getenv("userName");
    userName = temp;

    temp = std::getenv("password");
    password = temp;

    temp = std::getenv("schema");
    schema = temp;

    temp = std::getenv("port");
    std::stringstream os{};
    os << temp;
    os >> port;

    temp = std::getenv("OPT_RECONNECT");
    if(temp == "false")
        OPT_RECONNECT = false;
    else
        OPT_RECONNECT = true;



    // using env set up the connection
    connection_properties["hostName"] = hostName;
    connection_properties["userName"] = userName;
    connection_properties["password"] = password;
    connection_properties["schema"] = schema;
    connection_properties["port"] = port;
    connection_properties["OPT_RECONNECT"] = OPT_RECONNECT;

    // DB connected and ready to use
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect(connection_properties);
    stmt = con->createStatement();

    std::cout << con << " Connected to DB\n";
}