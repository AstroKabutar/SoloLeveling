#ifndef PLAYERGROWTH_H
#define PLAYERGROWTH_H

// sql::SQLString 
#include <cppconn/sqlstring.h>

class Mysql;

class PlayerGrowth
{
private:

    const int pg_pid{};
    const std::string pg_name{};
    bool pg_ispresent{};
    Mysql pg_mysql{};

public:
    PlayerGrowth(std::string_view pname, int pid, Mysql& mysql);

    // return 
    bool PExists() const    { return pg_ispresent; }

    // create task
    void task(std::string_view task, std::string_view importance);

    // get entire player tasks
    void gettasklist();

    // complete task
    void completetask(int tid);

private:
    // calculate xp
    void updatexp(std::string tid);
};


#endif // PLAYERGROWTH_H