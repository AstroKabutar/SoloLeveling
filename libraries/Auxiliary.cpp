#include <string_view>
#include <string>
#include <iostream>
#include <fstream>
#include <Auxiliary.h>

std::string Auxiliary::replace_all(std::string_view str, char mark, char replace)
{
    std::string name{str}; 
    for(auto character{std::begin(name)}; character != std::end(name); ++character)
    {
        if(*character == mark)   {  *character = replace;   }
    }
    return name;
}

std::string Auxiliary::replace(std::string_view str, std::string_view mark, std::string_view replace)
{
    std::string source{str};
    std::string marking{mark};
    std::string substr{replace};

    // get first occurance of the mark
    auto pos{source.find(marking)};

    // get mark length
    auto len{mark.size()};

    // replace the substring
    source.replace(pos, len, substr);

    // return the source str
    return source;
} 

std::string Auxiliary::replace(std::string_view str, std::string_view mark, int replace)
{
    std::stringstream os{};
    std::string source{str};
    std::string marking{mark};
    std::string substr{};

    os << replace;

    os >> substr;

    // get first occurance of the mark
    auto pos{source.find(marking)};

    // get mark length
    auto len{mark.size()};

    // replace the substring
    source.replace(pos, len, substr);

    // return the source str
    return source;
}

std::string Auxiliary::replace(std::string_view str, std::string_view mark, double replace)
{
    std::stringstream os{};
    std::string source{str};
    std::string marking{mark};
    std::string substr{};

    os << replace;

    os >> substr;

    // get first occurance of the mark
    auto pos{source.find(marking)};

    // get mark length
    auto len{mark.size()};

    // replace the substring
    source.replace(pos, len, substr);

    // return the source str
    return source;
}

std::string Auxiliary::getDate()
{
    std::string date{};
    // create a date.txt file to read it into date
    const char* datein{"date >> date.txt"};
    const char* dateout{"rm date.txt"};

    std::system(datein);
    std::ifstream file("date.txt");
    try
    {
        if (file.is_open())
        {
            std::getline(file, date);  // Read the single line
            file.close();
        }
        else
            throw std::runtime_error("date.txt not found");
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << "\nError: " << e.what() << "\nExiting application\n";
    }
    std::system(dateout);    

    return date;
}