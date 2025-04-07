#ifndef AUXILIARY_H
#define AUXILIARY_H
#include <sstream>

enum class Util;

// static class
class Auxiliary
{
public:
    Auxiliary() = delete;

    static std::string replace(std::string_view str, std::string_view mark, std::string_view replace);
    static std::string replace(std::string_view str, std::string_view mark, int replace);
    static std::string replace(std::string_view str, std::string_view mark, double replace);

    // get current date and time from system
    static std::string getDate();


    // static template function for convertion
    // for now only to string/fint/fdouble
    template <typename T, typename U>
    static U convert(T source, const Util& u);
};

enum class Util
{
    tostring,
    toint,
    todouble
};

template<typename T, typename U>
U Auxiliary::convert(T source, const Util& u)
{
    U target{};
    std::stringstream os{};

    switch (u)
    {
        case Util::tostring:
            os << source;
            os >> target;
        break;

        case Util::toint:
            os << source;
            os >> target;
        break;

        case Util::todouble:
            os << source;
            os >> target;
        break;    
    }

    // reset flag and clear string
    os.clear();
    os.str("");

    return target;
}

 
#endif // !AUXILIARY_H