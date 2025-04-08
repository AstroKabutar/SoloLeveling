#ifndef PLAYER_H
#define PLAYER_H

// sql::SQLString 
#include <cppconn/sqlstring.h>

class Mysql;

class Player
{
private:
    std::string  p_name{};
    std::string  p_creationdate{};
    std::string  p_dob{};

    int p_pid{};

    // DB table levels
    int p_level{2};
    double p_xp_required{10};

    // DB table player progression
    double p_current_xp{3.48};
    int p_current_level{1};

    // DB table xp_transactionsdes
    double p_xp_gained{3.48};
    std::string p_transaction_date{};
    std::string p_tasks_completed{"Welcome Player"};

    // populates the database with player initials
    void initialize(Mysql& mysql);

public:
    Player(std::string_view pname, std::string_view dob, Mysql& mysql);

};

#endif // !PLAYER_H