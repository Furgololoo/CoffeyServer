cmake_minimum_required(VERSION 3.25)
project(CoffeyServer)

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    set(examples_LINK_LIBRARIES "gdi32" "wsock32" "ws2_32")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og")
    if (CMAKE_BUILD_TYPE STREQUAL "")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
    endif ()
endif ()

find_package(OpenSSL REQUIRED)
find_package(Boost 1.82.0 REQUIRED)

if (Boost_FOUND)
    message(STATUS "Boost library status: ")
    message(STATUS "    version: ${Boost_VERSION}")
    message(STATUS "    libraries: ${Boost_LIBRARIES}")
    message(STATUS "    include dirs: ${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})
endif ()
if (OpenSSL_FOUND)
    message(STATUS "OpenSSL library status: ")
    message(STATUS "    version: ${OpenSSL_VERSION}")
    message(STATUS "    libraries: ${OpenSSL_LIBRARIES}")
    message(STATUS "    include dirs: F:/cpp/openssl/include")
    include_directories("F:/cpp/openssl/include")
endif ()


add_executable(CoffeyServer
        src/main.cpp

        # Communication
        src/server/servermanager.cpp src/server/servermanager.h
        src/server/listener.cpp src/server/listener.h
        src/server/session.cpp src/server/session.h

        # Request
        src/server/request/request.cpp src/server/request/request.h
        src/server/request/requestprocessing.cpp src/server/request/requestprocessing.h
        src/server/request/login_requestprocessing.cpp
        src/server/request/requestactions.h
        src/server/request/content_id.h

        # Database
        src/database/database.cpp src/database/database.h

        # Buffer
        src/buffer/buffer.cpp src/buffer/buffer.h

        # Helpers
        src/helpers/json_helper.cpp src/helpers/json_helper.h
        src/utils/config.h

        #        tests/database_test.cpp
)

#add_subdirectory(tests)
add_subdirectory(deps/libpqxx build-pqxx)
target_link_libraries(CoffeyServer PRIVATE pqxx)
target_link_libraries(CoffeyServer PRIVATE ${Boost_LIBRARIES})
target_link_libraries(CoffeyServer PRIVATE OpenSSL::SSL OpenSSL::Crypto)
