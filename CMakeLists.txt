cmake_minimum_required(VERSION 3.24)
project(CoffeyServer)

set(CMAKE_CXX_STANDARD 20)
#set(examples_LINK_LIBRARIES "gdi32" "wsock32" "ws2_32")

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og")

#if (CMAKE_BUILD_TYPE STREQUAL "")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
#endif ()

find_package(Boost 1.82.0 REQUIRED)

if (Boost_FOUND)
    message(STATUS "Boost library status: ")
    message(STATUS "    version: ${Boost_VERSION}")
    message(STATUS "    libraries: ${Boost_LIBRARIES}")
    message(STATUS "    include dirs: ${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})
endif ()

add_executable(CoffeyServer
        src/main.cpp

        # Communication
        src/server/serverworker.cpp src/server/serverworker.h
        src/server/servermanager.cpp src/server/servermanager.h
        src/server/listener.cpp src/server/listener.h
        src/server/session.cpp src/server/session.h

        # Request
        src/server/request/request.cpp src/server/request/request.h
        src/server/request/requesttypes.h
        src/server/request/requestactions.h)


target_link_libraries(CoffeyServer ${Boost_LIBRARIES})
target_link_libraries(CoffeyServer ${examples_LINK_LIBRARIES})
