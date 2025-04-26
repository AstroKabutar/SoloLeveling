#include <Mysql.h>
#include <Player.h>
#include <Auxiliary.h>
#include <PlayerGrowth.h>
#include <sstream>

PlayerGrowth::PlayerGrowth(std::string_view pname, int pid, Mysql& mysql)
: pg_pid{pid}, pg_name{pname}, pg_mysql{mysql}
{
    // check for the existence of details in database
    // from table players
    std::string sql_querry{"select exists (select player_id from players where player_id = ? and player_name = '?')"};

    sql_querry = Auxiliary::replace(sql_querry, "?", pg_pid);
    sql_querry = Auxiliary::replace(sql_querry, "?", pg_name);

    sql::SQLString querry{sql_querry};

    std::cout << sql_querry << "\n";
    pg_ispresent = mysql.exists(querry);
}

void PlayerGrowth::task(std::string_view task, std::string_view importance)
{
    std::string sql_querry{};
    sql::SQLString querry{};

    sql_querry = "insert into tasks(player_id, tasks, importance, status) values('?', '?', '?', '?')";
    sql_querry = Auxiliary::replace(sql_querry, "?", pg_pid);
    sql_querry = Auxiliary::replace(sql_querry, "?", task);
    sql_querry = Auxiliary::replace(sql_querry, "?", importance);
    sql_querry = Auxiliary::replace(sql_querry, "?", "INCOMPLETE");

    querry = sql_querry;

    pg_mysql.querry(querry);
}

void PlayerGrowth::gettasklist(TaskList& tasks)
{
    std::string sql_querry{};
    sql::SQLString querry{};
    std::string pid{Auxiliary::convert<int, std::string>(pg_pid, Util::tostring)};

    sql_querry = "select task_id as ID, tasks as Tasks, importance as Class, status from tasks where player_id like " + pid;
    querry = sql_querry;
    pg_mysql.fetch(querry, Fetch::LIST, tasks);
}

void PlayerGrowth::completetask(int taskid)
{
    std::string sql_querry{};
    sql::SQLString querry{};
    std::string tid{Auxiliary::convert<int, std::string>(taskid, Util::tostring)};

    /*Based on task id calculate the xp gained*/
    updatexp(tid);

    sql_querry = "update tasks set status = 'COMPLETED' where task_id like " + tid;
    querry = sql_querry;
    pg_mysql.querry(querry);
}



/*
1
select tasks.task_id, 
tasks.tasks,
importance.xp_gain as reward,
player_progression.current_xp as currentxp
from players inner join tasks on 
tasks.player_id = players.player_id inner join
importance on tasks.importance = importance.class inner join
player_progression on player_progression.player_id = players.player_id
where tasks.task_id like 2

2
select player_progression.current_level as level from player_progression 
inner join tasks on tasks.player_id = player_progression.player_id 
where tasks.task_id like 7

3
select levels.xp_required from levels 
inner join tasks on tasks.player_id = levels.player_id 
where tasks.task_id like 8

4
update levels
inner join tasks on tasks.player_id = levels.player_id
set level = 3,
xp_required = 60
where tasks.task_id like 8

5
update player_progression
set current_level = 3
where player_id = 1

6
insert into 
xp_transactions(player_id, xp_gained, transaction_date, tasks_completed)
values(4, 52.66, 'dsfsdf dsfsdf', 'done') 

7
update player_progression set current_level = 3,
current_xp = 30 
where player_id like 2;
*/
void PlayerGrowth::updatexp(std::string tid)
{
    // get data to display on the page
    if(tid == "getdata")
    {
        std::string sql_querry{};
        sql::SQLString querry{};
        std::string pid{Auxiliary::convert<int, std::string>(pg_pid, Util::tostring)};
        double xp_gained{};
    
        //sql_querry = "select tasks.task_id, tasks.tasks, importance.xp_gain as reward, xp_transactions.xp_gained as currentxp from players inner join tasks on tasks.player_id = players.player_id inner join importance on tasks.importance = importance.class inner join xp_transactions on xp_transactions.player_id = players.player_id where tasks.task_id like " + tid;
        sql_querry = "select player_progression.current_xp as currentxp from players inner join player_progression on player_progression.player_id = players.player_id where players.player_id like " + pid;
        querry = sql_querry;
    
        // get currentxp from database
        pg_current_xp = pg_mysql.getdata<double>(querry, Data::currentxp);
    

        sql_querry = "select player_progression.current_level as level from player_progression inner join players on players.player_id = player_progression.player_id where players.player_id like " + pid;
        querry = sql_querry;
        pg_level = pg_mysql.getdata<int>(querry, Data::level);
    
        sql_querry = "select levels.xp_required from levels inner join players on players.player_id = levels.player_id where players.player_id like " + pid;
        querry = sql_querry;
        pg_requiredxp = pg_mysql.getdata<double>(querry, Data::xp_required);
        return;
    }

    std::string sql_querry{};
    sql::SQLString querry{};
    std::string pid{Auxiliary::convert<int, std::string>(pg_pid, Util::tostring)};
    double xp_gained{};

    //sql_querry = "select tasks.task_id, tasks.tasks, importance.xp_gain as reward, xp_transactions.xp_gained as currentxp from players inner join tasks on tasks.player_id = players.player_id inner join importance on tasks.importance = importance.class inner join xp_transactions on xp_transactions.player_id = players.player_id where tasks.task_id like " + tid;
    sql_querry = "select tasks.task_id, tasks.tasks, importance.xp_gain as reward, player_progression.current_xp as currentxp from players inner join tasks on tasks.player_id = players.player_id inner join importance on tasks.importance = importance.class inner join player_progression on player_progression.player_id = players.player_id where tasks.task_id like " + tid;
    querry = sql_querry;

    // get tasks reward and currentxp from database
    std::string task{pg_mysql.getdata<std::string>(querry, Data::tasks)};   // <---- not getting full task string
    double reward{pg_mysql.getdata<double>(querry, Data::reward)};
    double currentxp{pg_mysql.getdata<double>(querry, Data::currentxp)};

    //xp gained
    xp_gained = (reward * currentxp) / 100;

    // new rewarded xp
    currentxp += xp_gained;
    pg_current_xp = currentxp;

    // check to see if player leveled
    sql_querry = "select player_progression.current_level as level from player_progression inner join tasks on tasks.player_id = player_progression.player_id where tasks.task_id like " + tid;
    querry = sql_querry;
    int level{pg_mysql.getdata<int>(querry, Data::level)};
    pg_level = level;

    sql_querry = "select levels.xp_required from levels inner join tasks on tasks.player_id = levels.player_id where tasks.task_id like " + tid;
    querry = sql_querry;
    double xp_required{pg_mysql.getdata<double>(querry, Data::xp_required)};
    pg_requiredxp = xp_required;
    

    std::cout << "Current xp - " << currentxp << " XP_Required - " << xp_required << " Current level " << level << '\n';
    
    if(currentxp >= xp_required)
    {
        std::cout << "Leveled up!!!\n";
        ++level;

        pg_level = level;

        // new threshold
        xp_required += (30 * xp_required) / 100 + 8;
        currentxp = 1;

        pg_requiredxp = xp_required;
        pg_current_xp = currentxp;

        // update the new level and xp in database
        sql_querry = "update levels inner join tasks on tasks.player_id = levels.player_id set level = '?', xp_required = '?' where tasks.task_id like " + tid;
        sql_querry = Auxiliary::replace(sql_querry, "?", level);
        sql_querry = Auxiliary::replace(sql_querry, "?", xp_required);
        querry = sql_querry;
        pg_mysql.querry(sql_querry);

        sql_querry = "update player_progression set current_level = ? where player_id = ?";
        sql_querry = Auxiliary::replace(sql_querry, "?", level);
        sql_querry = Auxiliary::replace(sql_querry, "?", pid);

        std::cout << "Current xp - " << currentxp << " XP_Required - " << xp_required << " Current level " << level << '\n';
    }

    std::cout << "Current xp - " << currentxp << " XP_Required - " << xp_required << " Current level " << level << '\n';

    // inserting updated data into xp_transactions
    std::string date{Auxiliary::getDate()};
    sql_querry = "insert into xp_transactions(player_id, xp_gained, transaction_date, tasks_completed) values('?', '?', '?', '?')";
    sql_querry = Auxiliary::replace(sql_querry, "?", pid);
    sql_querry = Auxiliary::replace(sql_querry, "?", xp_gained);
    sql_querry = Auxiliary::replace(sql_querry, "?", date);
    sql_querry = Auxiliary::replace(sql_querry, "?", task);
    querry = sql_querry;
    pg_mysql.querry(sql_querry);

    // inserting updated data into player_progression
    sql_querry = "update player_progression set current_level = ?, current_xp = ? where player_id like ?;";
    sql_querry = Auxiliary::replace(sql_querry, "?", level);
    sql_querry = Auxiliary::replace(sql_querry, "?", currentxp);
    sql_querry = Auxiliary::replace(sql_querry, "?", pid);
    querry = sql_querry;
    pg_mysql.querry(sql_querry);
}

/*
select 
players.player_id, 
tasks.task_id, 
tasks.tasks, 
tasks.importance as class,
importance.xp_gain as reward,
xp_transactions.xp_gained as currentxp
from players
inner join tasks on tasks.player_id = players.player_id
inner join importance on tasks.importance = importance.class
inner join xp_transactions on xp_transactions.player_id = players.player_id
where players.player_id like 4
*/

