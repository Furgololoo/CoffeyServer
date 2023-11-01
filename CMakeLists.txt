cmake_minimum_required(VERSION 3.24)
project(CoffeyServer)

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    set(examples_LINK_LIBRARIES "gdi32" "wsock32" "ws2_32")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og")
    if (CMAKE_BUILD_TYPE STREQUAL "")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
    endif ()
endif ()

set(PostgreSQL_LIBRARY "H:/PostgreSQL/lib/libpq.lib")
set(PostgreSQL_INCLUDE_DIR "H:/PostgreSQL/include")

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
        #        src/server/servermanager.cpp src/server/servermanager.h
        #        src/server/listener.cpp src/server/listener.h
        #        src/server/session.cpp src/server/session.h

        # Request
        src/server/request/request.cpp src/server/request/request.h
        #        src/server/request/requestactions.h
        #        src/server/request/content_id.h
        #        src/database/database.cpp
        #        src/database/database.h

        # Buffer
        src/buffer/buffer.cpp src/buffer/buffer.h

        # Helpers
        #        src/helpers/json_helper.cpp src/helpers/json_helper.h

        src/utils/config.h
)

# PostgreSQL
add_subdirectory(deps/libpqxx-7.8.1 build-pqxx)
target_link_libraries(CoffeyServer pqxx)

target_link_libraries(CoffeyServer ${Boost_LIBRARIES})
target_link_libraries(CoffeyServer ${examples_LINK_LIBRARIES})
