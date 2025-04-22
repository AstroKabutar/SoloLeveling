#ifndef AUXILIARY_H
#define AUXILIARY_H
#include <sstream>
#include <stdlib.h>

enum class Util;
class PlayerGrowth;
class Mysql;

// static class
class Auxiliary
{
public:
    Auxiliary() = delete;

    static std::string replace(std::string_view str, std::string_view mark, std::string_view replace);
    static std::string replace(std::string_view str, std::string_view mark, int replace);
    static std::string replace(std::string_view str, std::string_view mark, double replace);
    static std::string replace_all(std::string_view str, char mark, char replace);

    // get current date and time from system
    static std::string getDate();


    // static template function for convertion
    // for now only to string/fint/fdouble
    template <typename T, typename U>
    static U convert(T source, const Util& u);
};

struct TaskList
{
    std::vector<int> id{};
    std::vector<std::string> tasks{};
    std::vector<std::string> imp{};
    std::vector<std::string> status{};
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

// Class allocation management templates <only for PlayerGrowth class for now>

/* ---notes---

pointer = new (rawMemory) T{};
Explanation of Placement new:

    Placement new allows you to construct an object at a specific memory location (in this case, rawMemory), rather than having the memory allocated and managed by new.

    This allows you to control where the object is created, which is useful when you’ve already allocated memory (e.g., with calloc or malloc) and want to construct an object in that memory.
    
    rawMemory is a pointer to a memory block that you've already allocated using calloc or another allocation function.

The placement new syntax is: new (location) Type(args). This syntax tells the compiler to construct the object of type T at the specified
location rawMemory using the arguments passed to the constructor ({} in this case, which uses the default constructor for T).

*/
template <typename T>
class ClassAllocator
{
private:
    T* pointer{nullptr};

public:
    ClassAllocator(std::string_view pname, int pid, Mysql& mysql)
    {
        void* alloc = calloc(1, sizeof(T));
        pointer = new (alloc) T{pname, pid, mysql};
    }

    ~ClassAllocator()
    {
        free(pointer);
    }

    T* Get() const {    return pointer;     }
};

#endif // !AUXILIARY_H