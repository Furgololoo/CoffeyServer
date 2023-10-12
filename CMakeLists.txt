cmake_minimum_required(VERSION 3.27)
project(CoffeyServer)

set(CMAKE_CXX_STANDARD 20)
set(examples_LINK_LIBRARIES "gdi32" "wsock32" "ws2_32")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og")

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
endif ()

find_package(Boost REQUIRED COMPONENTS)

if (Boost_FOUND)
    message(STATUS "Boost library status: ")
    message(STATUS "    version: ${Boost_VERSION}")
    message(STATUS "    libraries: ${Boost_LIBRARIES}")
    message(STATUS "    include dirs: ${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})
endif ()

add_executable(CoffeyServer
        src/main.cpp

        # Server
        src/server/serverworker.cpp src/server/serverworker.h
        src/server/servermanager.cpp src/server/servermanager.h
)


target_link_libraries(CoffeyServer ${Boost_LIBRARIES})
target_link_libraries(CoffeyServer ${examples_LINK_LIBRARIES})
