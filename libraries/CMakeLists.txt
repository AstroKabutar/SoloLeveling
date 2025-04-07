set(mylib 
    Mysql.cpp
    Player.cpp
    Setup.cpp
    Auxiliary.cpp
    PlayerGrowth.cpp
)

add_library(CUSTOM_INCLUDE_LIBRARIES STATIC ${mylib})

# making sure these libraries can see the includes
target_include_directories(CUSTOM_INCLUDE_LIBRARIES PRIVATE "${CUSTOM_INCLUDES}")

# linking the libraries so the libraries can use it
target_link_libraries(CUSTOM_INCLUDE_LIBRARIES PRIVATE ${SQL_CONNECTION_LIB})

foreach(file IN LISTS mylib)
    message(STATUS "Library added: ${file}")
endforeach()
