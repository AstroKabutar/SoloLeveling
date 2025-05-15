#include <string_view>
#include <iostream>
#include <sstream>
#include <vector>
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

    // getting crowport hosting from env file
    const char* crow_port_env{std::getenv("HTTP_PORT")};
    std::stringstream os{};
    os << crow_port_env;
    std::uint16_t crow_port_env_int{};
    os >> crow_port_env_int;
    os.clear();
    os.str("");

    const char* thread_count{std::getenv("THREADS")};
    os << thread_count;
    std::uint16_t threads{};
    os >> threads;
    os.clear();
    os.str("");


    // session storage
    ClassAllocator<PlayerGrowth>* session = static_cast<ClassAllocator<PlayerGrowth>*>(calloc(1, sizeof(ClassAllocator<PlayerGrowth>)));
    //ClassAllocator<PlayerGrowth>* session = static_cast<ClassAllocator<PlayerGrowth>*>(malloc(1 * sizeof(ClassAllocator<PlayerGrowth>)));

/*---------------------------------------GET REQESTS----------------------------------------------*/

    // Serve the HTML form dynamically at "/"
    CROW_ROUTE(app, "/LoadGame")([]()
    {
        return crow::mustache::load_text("LoadGame.html");
    });

    CROW_ROUTE(app, "/Begin")([]()
    {
        return crow::mustache::load_text("index.html");
    });

    /*CROW_ROUTE(app, "/Tasks")([]()
    {
        return crow::mustache::load_text("tasks.html");
    });*/

/*--------------------------TESTING GROUNDS--------------------------------------------------------*/

    CROW_ROUTE(app, "/api/gettasks")
    ([&session] {
        crow::json::wvalue json;
        TaskList tasksl{};

        // for testing now
        session->Get()->gettasklist(tasksl);

        std::vector<int> id{};
        std::vector<std::string> tasks{};
        std::vector<std::string> imp{};
        std::vector<std::string> status{};

        std::vector<crow::json::wvalue> task_list{};

        // populating the above containers
        for(int x{}; x < tasksl.id.size(); ++x)
        {
            id.push_back(tasksl.id[x]);
            tasks.push_back(tasksl.tasks[x]);
            imp.push_back(tasksl.imp[x]);
            status.push_back(tasksl.status[x]);
        }

        for(int i{}; i < id.size(); ++i)
        {
            crow::json::wvalue temp;
            // if error pops then will convert id to string
            temp["ID"] = id[i];
            temp["Tasks"] = tasks[i];
            temp["Importance"] = imp[i];
            temp["Status"] = status[i];
            task_list.push_back(temp);
        }

        json["tasks_list"] = std::move(task_list);

        return crow::response(json);
    });

    // ------------------- get player stats ------------------ //
    CROW_ROUTE(app, "/api/playerstats")
    ([&session] {
        crow::json::wvalue json;

        // for testing now
        session->Get()->updatexp("getdata");        

        std::string pname{session->Get()->pg_name};
        double current_xp{session->Get()->pg_current_xp};
        int current_level{session->Get()->pg_level};
        double required_xp{session->Get()->pg_requiredxp};

        std::vector<crow::json::wvalue> Player_Stats{};

        crow::json::wvalue temp;
        temp["pname"] = pname;
        temp["current_xp"] = current_xp;
        temp["current_level"] = current_level;
        temp["required_xp"] = required_xp;
        Player_Stats.push_back(temp);

        json["Player_Stats"] = std::move(Player_Stats);

        return crow::response(json);
    });

    /*crow::json::wvalue json;

    std::vector<std::string> id = {"1", "2", "3"};
    std::vector<std::string> tasks = {"Task 1", "Task 2", "Task 3"};
    std::vector<std::string> imp = {"High", "Medium", "Low"};
    std::vector<std::string> status = {"Pending", "Completed", "Pending"};
    
    // Vector to hold the JSON objects
    std::vector<crow::json::wvalue> items;
    
    for (size_t i = 0; i < id.size(); ++i) {
        crow::json::wvalue task;
        task["id"] = id[i];
        task["task"] = tasks[i];
        task["importance"] = imp[i];
        task["status"] = status[i];
        items.push_back(task);
    }
    
    // Assign vector to JSON array field
    json["items"] = std::move(items);
    
    return crow::response(json);*/
    
    


/*---------------------------------------------------------------------------------------------*/




/*---------------------------------------POST REQESTS----------------------------------------------*/

    // Handle POST request at /Tasks route for task related things
   /* app.route_dynamic("/Tasks")
    .methods("POST"_method)
    ([&mysql, &os, &sessions]
    {

    });*/

    // Handle POST reqest at /LoadGame
    app.route_dynamic("/LoadGame")
    .methods("POST"_method)
    ([&mysql, &os, &session](const crow::request& req)
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

        // get other data
        std::string importance{};
        std::string new_task{};
        int task_id{};

        // Split body by '&' to get key-value pairs
        std::istringstream stream(body);
        std::string pair;
        while (std::getline(stream, pair, '&')) 
        {
            std::cout << "\n-------------- " << pair <<" ----------\n";
            size_t pos = pair.find("=");
            if (pos != std::string::npos) 
            {
                std::string key = pair.substr(0, pos);
                std::string value = pair.substr(pos + 1);

                if (key == "Name") 
                {
                    pname = value;
                    pname = Auxiliary::replace_all(pname, '+', ' ');
                } else if (key == "PID") 
                {
                    pid = value;
                }
                else if (key == "taskInput") 
                {
                    new_task = value;
                    new_task = Auxiliary::replace_all(new_task, '+', ' ');
                } 
                else if (key == "Importance") 
                {
                    importance = value;
                }
                else if(key == "task_id")
                {
                    os << value;
                    os >> task_id;
                    os.clear();
                    os.str("");
                }
            }
        }

        // check for player existence then proceed
        os << pid;
        int id{};
        os >> id;
        os.clear();
        os.str("");
        if (id < 100 && id >= 0)
        {
            new (session) ClassAllocator<PlayerGrowth>{pname, id, mysql};

            std::cout << "Session variable error\n";
            if((!(session->Get()->PExists())))
            {
                std::string error = R"(
                    <html>
                        <head>
                            <script>
                            alert("No player found");
                            window.location.href = "/Begin";
                            </script>
                        </head>
                    </html>
                )";

                return crow::response(error);
            }   
        }
        
        // check if new task is entered then insert into database
        // check if completed then proceed to complete the task
        if(!new_task.empty())
        {
            session->Get()->task(new_task, importance);
        }
        if(task_id>0)
        {
            session->Get()->completetask(task_id);
        }

        // reload with updated stats
        std::string redirect = R"(
            <html>
                <head>
                    <script>
                        window.location.href = "/LoadGame?init=1";
                    </script>
                </head>
            </html>
            )";
        return crow::response(redirect);
    });

    // Handle POST request at /Begin
    app.route_dynamic("/Begin")
    .methods("POST"_method)
    ([&mysql, &os](const crow::request& req)
    {
        // Retrieve the raw body data (form data)
        std::string body = req.body;

        // Print the raw body data (for debugging purposes)
        std::cout << "Raw body data: " << body << '\n';

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
                    name = Auxiliary::replace_all(name, '+', ' ');
                }
                else if (key == "dob") 
                {
                    dob = value;
                }
            }
        }

        // create player object to put in DB
        Player player(name, dob, mysql);
        int playerid{player.getpid()};
        std::string pid{};
        os << playerid;
        os >> pid;
        os.clear();
        os.str("");

        std::string new_player = R"(
            <html>
                <head>
                    <script>
                        alert("Welcome Player, Your ID is )" + pid + R"(."); 
                        window.location.href = "/LoadGame";
                    </script>
                </head>
            </html>
            )";

        return crow::response(new_player);
    });

    // Run the server on port xxxxx
    //app.port(crow_port_env_int).multithreaded().run();
    app.port(crow_port_env_int).concurrency(threads).run();
    

    delete session;
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