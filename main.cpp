#include <string_view>

#include <iostream>
#include <crow.h>
#include <Mysql.h>
#include <Player.h>
#include <PlayerGrowth.h>
#include <Setup.h>
#include <Auxiliary.h>

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
    /*std::string name{getstring("Enter your name: ")};
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

    growth.task(task, importance);*/

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



// working
/*
int main() 
{
    crow::SimpleApp app;


    // Serve the HTML form dynamically at "/"
    CROW_ROUTE(app, "/")([]()
    {
        auto page = crow::mustache::load_text("post.html");
        return page;
    });

    // Handle POST request at /submit
    app.route_dynamic("/submit")
    .methods("POST"_method)
    ([](const crow::request& req){
        // Retrieve the raw body data (form data)
        std::string body = req.body;

        // Print the raw body data (for debugging purposes)
        std::cout << "Raw body data: " << body << std::endl;

        // Now, parse the body (assuming URL-encoded data: name=John&email=john@example.com)
        // We can manually parse the body as key-value pairs:
        std::string name;
        std::string email;
        std::string message;

        // Split body by '&' to get key-value pairs
        std::istringstream stream(body);
        std::string pair;
        while (std::getline(stream, pair, '&')) {
            size_t pos = pair.find("=");
            if (pos != std::string::npos) {
                std::string key = pair.substr(0, pos);
                std::string value = pair.substr(pos + 1);

                if (key == "name") {
                    name = value;
                } else if (key == "email") {
                    email = value;
                } else if (key == "message") {
                    message = value;
                }
            }
        }

        // Output the parsed data
        std::cout << "Name: " << name << std::endl;
        std::cout << "Email: " << email << std::endl;
        std::cout << "Message: " << message << std::endl;

        // Respond back with a simple success message
        return crow::response("Form submitted successfully!");
    });

    // Run the server on port 8080
    app.port(8080).multithreaded().run();
}
*/