#include <string_view>
#include <iostream>
#include <sstream>
#include <crow.h>
#include <Mysql.h>
#include <Player.h>
#include <PlayerGrowth.h>
#include <Setup.h>
#include <Auxiliary.h>

int main() 
{
    crow::SimpleApp app;
        
    // custom made mysql database object
    Mysql mysql{};

    // Bootstrap
    Setup bootstrap{mysql};

    std::cout << "-----------------------------This is a test---------------\n";

/*---------------------------------------GET REQESTS----------------------------------------------*/

    // Serve the HTML form dynamically at "/"
    CROW_ROUTE(app, "/LoadGame")([]()
    {
        auto page = crow::mustache::load_text("LoadGame.html");
        return page;
    });

    CROW_ROUTE(app, "/")([]()
    {
        auto page = crow::mustache::load_text("index.html");
        return page;
    });

/*---------------------------------------POST REQESTS----------------------------------------------*/


    // Handle POST reqest at /LoadGame
    app.route_dynamic("/LoadGame")
    .methods("POST"_method)
    ([&mysql](const crow::request& req)
    {
        // Retrieve the raw body data (form data)
        std::string body = req.body;

        // Print the raw body data (for debugging purposes)
        std::cout << "Raw body data: " << body << std::endl;

        // Now, parse the body (assuming URL-encoded data: name=John&email=john@example.com)
        // We can manually parse the body as key-value pairs: given in id in html
        std::string pname{};
        std::string pid{};
        std::stringstream os{};

        // Split body by '&' to get key-value pairs
        std::istringstream stream(body);
        std::string pair;
        while (std::getline(stream, pair, '&')) 
        {
            //std::cout << "\n-------------- " << pair <<" ----------\n";
            size_t pos = pair.find("=");
            if (pos != std::string::npos) 
            {
                std::string key = pair.substr(0, pos);
                std::string value = pair.substr(pos + 1);

                if (key == "Name") 
                {
                    pname = value;
                } else if (key == "PID") 
                {
                    pid = value;
                }
            }
        }

        return R"(
            <html>
                <head>
                    <script src="/static/LoadGame.js"></script>
                </head>
                <body></body>
            </html>
        )";
    });

    // Handle POST request at /
    app.route_dynamic("/")
    .methods("POST"_method)
    ([&mysql](const crow::request& req)
    {
        // Retrieve the raw body data (form data)
        std::string body = req.body;

        // Print the raw body data (for debugging purposes)
        std::cout << "Raw body data: " << body << std::endl;

        // Now, parse the body (assuming URL-encoded data: name=John&email=john@example.com)
        // We can manually parse the body as key-value pairs: given in id in html
        std::string name;
        std::string dob;

        // Split body by '&' to get key-value pairs
        std::istringstream stream(body);
        std::string pair;
        while (std::getline(stream, pair, '&')) 
        {
            //std::cout << "\n-------------- " << pair <<" ----------\n";
            size_t pos = pair.find("=");
            if (pos != std::string::npos) 
            {
                std::string key = pair.substr(0, pos);
                std::string value = pair.substr(pos + 1);

                if (key == "name") 
                {
                    name = value;
                } else if (key == "dob") 
                {
                    dob = value;
                }
            }
        }

        // create player object to put in DB
        Player player(name, dob, mysql);

        return R"(
            <html>
                <head>
                    <script src="/static/index.js"></script>
                </head>
                <body></body>
            </html>
        )";
    });

    // Run the server on port 8000
    app.port(8000).multithreaded().run();
}



































/*
std::string getstring(std::string_view message)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << message;
    std::string tmp{};
    std::getline(std::cin, tmp);
    return tmp;
}

int getint(std::string_view message)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << message;
    int tmp{};
    std::cin >> tmp;
    return tmp;
}


int main()
{
    // crow application
    //crow::SimpleApp app{};

    // custom made mysql database object
    Mysql mysql{};

    // setup before run
    Setup setup{mysql};

    //------------CLI TEST-----------------//   WORKING
    // create a dummy player using cli
    std::string name{getstring("Enter your name: ")};
    std::string dob{getstring("Enter the DOB in yyyy-mm-dd format: ")};

    // create player object to put in DB
    Player player(name, dob, mysql);

    //-------------existing player growth check----------------//
    name = getstring("Enter your name: ");
    int ID{getint("Enter your ID: ")};
    PlayerGrowth growth(name, ID, mysql);
    std::cout << growth.PExists() << '\n';

    //------------create tasks for player by player-----------//
    std::string task{getstring("Enter the task: ")};
    std::string importance{getstring("Enter the importance S,A,B,C,D,E: ")};

    growth.task(task, importance);

    //-------------A CLI loop testing-------------//
    std::string name{getstring("Enter your name: ")};
    std::string dob{getstring("Enter the DOB in yyyy-mm-dd format: ")};
    Player player(name, dob, mysql);

    name = getstring("Enter your name: ");
    int ID{getint("Enter your ID: ")};
    PlayerGrowth growth(name, ID, mysql);

    int i{};
    while(i < 3)
    {
        std::string task{getstring("Enter the task: ")};
        std::string importance{getstring("Enter the importance S,A,B,C,D,E: ")};

        growth.task(task, importance);
        std::cout << "Done\n";
        // maybe get task pid during creation and if completed
        // tell the task id and it will be completed
        // when we need to set the task to be completed
        // -----------get a list of task this player has-------- 1 DONE
        // -----------task completance using task id ----------- 2 DONE
        // -----------xp calculation based above --------------- 3 DONE

        ++i;
    }
    // get a list of task this player has with its status
    std::cout << "\n===================\n";
    growth.gettasklist();
    std::cout << "\n===================\n";

    // complete a task
    int taskid{getint("Taskid which was completed: ")};
    growth.completetask(taskid);

    std::cout << "\n===================\n";
    growth.gettasklist();
    std::cout << "\n===================\n";
}
*/