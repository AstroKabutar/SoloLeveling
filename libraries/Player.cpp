#include <iostream>
#include <fstream>
#include <string_view>
#include <Mysql.h>
#include <Player.h>
#include <Auxiliary.h>

Player::Player(std::string_view pname, std::string_view dob, Mysql& mysql)
{
    // name of the player
    p_name = pname;

    // date of birth
    // need to get it from the webpage but for now
    // assume for testing
    p_dob = dob;

    // get player creation date
    p_creationdate = Auxiliary::getDate();
    std::cout << "Player " << p_name << " Created at " << p_creationdate << '\n';

    // insert the player data into player table
    std::string sql_querry{"insert into players(player_name, dob, created_at) values('?', '?', '?')"};

    sql_querry = Auxiliary::replace(sql_querry, "?", p_name);
    sql_querry = Auxiliary::replace(sql_querry, "?", p_dob);
    sql_querry = Auxiliary::replace(sql_querry, "?", p_creationdate);

    sql::SQLString querry{sql_querry};
    mysql.querry(querry);

    // output the player id and name after creation to note it down
    sql_querry = "select player_id as ID, player_name as Name from players where player_name like '?'";
    sql_querry = Auxiliary::replace(sql_querry, "?", p_name);
    querry = sql_querry;

    std::cout << "Please keep this unique ID with you\n";
    TaskList tasks{};   //just temporarily, find a way to remove it later during cleanup
    mysql.fetch(querry, Fetch::ID, tasks);
    p_pid = mysql.getpid(querry);

    std::cout << "Initiating player database population\n";
    initialize(mysql);
}

void Player::initialize(Mysql& mysql)
{
    sql::SQLString querry{};
    std::string sql_querry{};

    // DB table player progression
    std::cout << "Populating DB player progression\n";
    sql_querry = "insert into player_progression(player_id, current_level, current_xp) values('?', '?', '?')";
    sql_querry = Auxiliary::replace(sql_querry, "?", p_pid);
    sql_querry = Auxiliary::replace(sql_querry, "?", p_current_level);
    sql_querry = Auxiliary::replace(sql_querry, "?", p_current_xp);

    querry = sql_querry;
    mysql.querry(querry);

    // DB table levels
    std::cout << "Populating DB levels\n";
    sql_querry = "insert into levels(player_id, level, xp_required) values('?', '?', '?')";
    sql_querry = Auxiliary::replace(sql_querry, "?", p_pid);
    sql_querry = Auxiliary::replace(sql_querry, "?", p_level);
    sql_querry = Auxiliary::replace(sql_querry, "?", p_xp_required);

    querry = sql_querry;
    mysql.querry(querry);

    // DB table xp_transactions
    std::cout << "Populating DB xp_transactions\n";
    sql_querry = "insert into xp_transactions(player_id, xp_gained, transaction_date, tasks_completed) values('?', '?', '?', '?')";
    sql_querry = Auxiliary::replace(sql_querry, "?", p_pid);
    sql_querry = Auxiliary::replace(sql_querry, "?", p_xp_gained);
    p_transaction_date = Auxiliary::getDate();
    sql_querry = Auxiliary::replace(sql_querry, "?", p_transaction_date);
    sql_querry = Auxiliary::replace(sql_querry, "?", p_tasks_completed);

    querry = sql_querry;
    mysql.querry(querry);

}