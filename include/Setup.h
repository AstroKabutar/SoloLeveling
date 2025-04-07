#ifndef SETUP_H
#define SETUP_H 

// sql::SQLString 
#include <cppconn/sqlstring.h>

class Setup
{
public:
    Setup(Mysql& mysql);
};


// constants
namespace firstrun
{
    // create database
    const sql::SQLString database\
    {"\
        create database if not exists Users\
    "};

    // switch database
    const sql::SQLString switchdb\
    {"\
        use Users\
    "};

    // create table players 1
    const sql::SQLString players\
    {"\
        create table if not exists players\
        (\
            player_id int not null primary key auto_increment,\
            player_name varchar(200),\
            dob date,\
            created_at varchar(50)\
        )\
    "};

    // create tables levels 3
    const sql::SQLString levels\
    {"\
        create table if not exists levels\
        (\
            player_id int,\
            level int not null,\
            xp_required double,\
            FOREIGN KEY (player_id) REFERENCES players(player_id)\
        )\
    "};

    // create tables player_progression 2
    const sql::SQLString player_progression\
    {"\
        create table if not exists player_progression\
        (\
            player_id int,\
            current_level int,\
            current_xp double,\
            FOREIGN KEY (player_id) REFERENCES players(player_id)\
        )\
    "};

    // create tables xp_transactions 4
    const sql::SQLString xp_transactions\
    {"\
        create table if not exists xp_transactions\
        (\
            player_id INT,\
            xp_gained double,\
            transaction_date varchar(50),\
            tasks_completed varchar(5000),\
            FOREIGN KEY (player_id) REFERENCES players(player_id)\
        )\
    "};

    // create table tasks
    const sql::SQLString tasks\
    {"\
        create table if not exists tasks\
        (\
            player_id INT,\
            task_id INT primary key not null auto_increment,\
            tasks varchar(5000),\
            importance varchar(1),\
            status varchar(100),\
            FOREIGN KEY (player_id) REFERENCES players(player_id),\
            FOREIGN KEY (importance) REFERENCES importance(class)\
        )\
    "};

    // create table importance  need to be made or altered outside of program
    // can change so best is to go via external sql script here
    // class is set like solo leveling anime
    // S, A, B, C, D, E
    // xp_gain is percentage increase
    const sql::SQLString importance\
    {"\
        create table if not exists importance\
        (\
            class varchar(1) primary key not null,\
            xp_gain double not null\
        )\
    "};
};

#endif // !SETUP_H



/*
create table a (dob date);

describe a;

insert into a VALUES (str_to_date('08-06-1999', '%d-%m-%Y'));
select DATE_FORMAT(dob, '%d-%m-%Y') from a;
*/