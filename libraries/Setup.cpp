#include <Mysql.h>
#include <Setup.h>

Setup::Setup(Mysql& mysql)
{
    // create database
    mysql.querry(firstrun::database);

    // switch database
    //mysql.querry(firstrun::switchdb);

    // create base tables in the database
    mysql.querry(firstrun::players);
    mysql.querry(firstrun::levels);
    mysql.querry(firstrun::player_progression);
    mysql.querry(firstrun::xp_transactions);
    mysql.querry(firstrun::importance);
    mysql.querry(firstrun::tasks);
}