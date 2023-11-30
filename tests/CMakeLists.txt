#cmake_minimum_required(VERSION 3.25)
#project(CoffeyServerTest)
#
#set(CMAKE_CXX_STANDARD 20)
#
#if (WIN32)
#    set(examples_LINK_LIBRARIES "gdi32" "wsock32" "ws2_32")
#    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og")
#    if (CMAKE_BUILD_TYPE STREQUAL "")
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
#    endif ()
#endif ()
#
#enable_testing()
#
#set(ENV{GTEST_INCLUDE_DIR} "F:/cpp/Libraries/googletest/googletest/include")
#find_package(Boost 1.82.0 REQUIRED)
#find_package(GTest REQUIRED)
#include_directories()
#
#if (Boost_FOUND)
#    message(STATUS "Boost library status: ")
#    message(STATUS "    version: ${Boost_VERSION}")
#    message(STATUS "    libraries: ${Boost_LIBRARIES}")
#    message(STATUS "    include dirs: ${Boost_INCLUDE_DIRS}")
#    include_directories(${Boost_INCLUDE_DIRS})
#endif ()
#
#add_executable(CoffeyServerTest
#        database_test.cpp
#)
#
## PostgreSQL
#add_subdirectory(../deps/libpqxx build-pqxx)
#target_link_libraries(CoffeyServerTest PRIVATE pqxx)
#
#target_link_libraries(CoffeyServerTest ${Boost_LIBRARIES})
#
#target_link_libraries(CoffeyServerTest
#        PRIVATE
#        GTest::GTest)
#add_test(CoffeyServer_gtests CoffeyServerTest)
#
