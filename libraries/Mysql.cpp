#include <iostream>
#include <cstdlib>
#include <string_view>
#include <sstream>

#include <Mysql.h>

Mysql::Mysql()
{
    std::cout << "Connecting to DB\n";

    // get env variable values
    // utility
    std::string x{};   
    sql::SQLString x1{}; 
    std::stringstream ss{};

    try
    {
        const char* temp1{std::getenv("HOSTNAME")};
        if(temp1 == nullptr)
            throw std::runtime_error("ENV HOSTNAME is not found");
        x = temp1;
        x1 = x;
        hostName = x1;
        std::cout << hostName << ':';

        const char* temp2{std::getenv("USERNAME")};
        if(temp2 == nullptr)
            throw std::runtime_error("ENV USERNAME is not found");
        x = temp2;
        userName = sql::SQLString{x};
        std::cout << userName << ':';

        const char* temp3{std::getenv("PASSWORD")};
        if(temp3 == nullptr)
            throw std::runtime_error("ENV PASSWORD is not found");
        x = temp3;
        password = sql::SQLString{x};
        std::cout << password << ':';

        const char* temp4{std::getenv("SCHEMA")};
        if(temp4 == nullptr)
            throw std::runtime_error("ENV SCHEMA is not found");
        x = temp4;
        schema = sql::SQLString{x};
        std::cout << schema << ':';


        const char* temp5{std::getenv("PORT")};
        if(temp5 == nullptr)
            throw std::runtime_error("ENV PORT is not found");
        x = temp5;
        ss << x;
        ss >> port;
        //port = sql::SQLString{x};
        std::cout << port << ":\n";

        const char* temp{std::getenv("OPT_RECONNECT")};
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

    catch(const std::runtime_error& e)
    {
        std::cerr << "\nError: " << e.what() << "\nExiting application\n";
    }
}

void Mysql::querry(const sql::SQLString& statement)
{
    stmt->execute(statement);
    std::cout << "Querry \'" << statement << "\' successfully ran\n";
    //std::cout << "Querry Successfully ran\n";
}

void Mysql::fetch(const sql::SQLString& statement, const Fetch& f)
{
    switch (f)
    {
        case Fetch::ID:
            res = stmt->executeQuery(statement);

            res->next();
            std::cout << "ID" << " " << "Name" << '\n';
            std::cout << res->getInt("ID") << " " << res->getString("Name") << '\n';
        break;

        case Fetch::LIST:
            res = stmt->executeQuery(statement);
            while(res->next())
            {
                std::cout << res->getInt(1) << " ";
                std::cout << res->getString(2) << " ";
                std::cout << res->getString(3) << " ";
                std::cout << res->getString(4) << '\n';
            }
        break;
    }

}

bool Mysql::exists(const sql::SQLString& statement)
{
    res = stmt->executeQuery(statement);

    res->next();

    bool ispresent{res->getBoolean(1)};

    return ispresent;
}

int Mysql::getpid(const sql::SQLString& statement)
{
    res = stmt->executeQuery(statement);
    res->next();
    int pid{res->getInt("ID")};
    return pid;
}