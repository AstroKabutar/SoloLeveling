#ifndef PLAYERGROWTH_H
#define PLAYERGROWTH_H

// sql::SQLString 
#include <cppconn/sqlstring.h>

class Mysql;
struct TaskList;

class PlayerGrowth
{
private:
    const int pg_pid{};
    bool pg_ispresent{};
    Mysql pg_mysql{};

public:

    const std::string pg_name{};
    double pg_current_xp{};
    int pg_level{};
    double pg_requiredxp{};

    PlayerGrowth(std::string_view pname, int pid, Mysql& mysql);

    // return 
    bool PExists() const    { return pg_ispresent; }

    // create task
    void task(std::string_view task, std::string_view importance);

    // get entire player tasks
    void gettasklist(TaskList& tasks);

    // complete task
    void completetask(int tid);

    // get player id
    int getplayerid() const {   return pg_pid;  }

//private:
    // calculate xp
    void updatexp(std::string tid);
};

#endif // PLAYERGROWTH_H