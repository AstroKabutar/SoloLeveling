cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SoloLeveling VERSION 1.0)

# set include directories
set(CROW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/crow"
                     "${CMAKE_SOURCE_DIR}/crow/include")

#file(GLOB_RECURSE CROW_INCLUDE_DIR CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/crow/*.h")
#message(STATUS "${CROW_INCLUDE_DIR}")


set(SQL_CONNECTION_HEADER /usr/include)
set(CUSTOM_INCLUDES "${CMAKE_SOURCE_DIR}/include")

# set target link libraries
set(SQL_CONNECTION_LIB /usr/lib/aarch64-linux-gnu/libmysqlcppconn.so)      # aarch gnu for rasberry pi
#file(GLOB_RECURSE CUSTOM_INCLUDE_LIBRARIES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/libraries/*.cpp")     # add all library


# executable name SoloLeveling
#add_executable(SoloLeveling main.cpp ${CUSTOM_INCLUDE_LIBRARIES})
add_executable(SoloLeveling main.cpp)

# Add the include directories to the target
target_include_directories(SoloLeveling PUBLIC ${CROW_INCLUDE_DIR}
                                                ${SQL_CONNECTION_HEADER}
                                                ${CUSTOM_INCLUDES})

#add_subdirectory("${CMAKE_SOURCE_DIR}/libraries")  # alternative to glob with more modular control on which library to add and which to not
add_subdirectory(libraries)

# Link libraries to the final executable
target_link_libraries(SoloLeveling PRIVATE ${SQL_CONNECTION_LIB}
                                            CUSTOM_INCLUDE_LIBRARIES)