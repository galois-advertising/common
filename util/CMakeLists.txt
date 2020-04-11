project(common_util)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -std=c++2a -fno-strict-aliasing -Wno-register")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -std=c++2a -fno-strict-aliasing -Wno-register")
set(CMAKE_BUILD_TYPE "Release")

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/")

find_package(Boost REQUIRED COMPONENTS log)
if(NOT Boost_FOUND)
    message("Can not find Boost")
endif()
message(STATUS "Found Boost IncPath ${Boost_INCLUDE_DIRS}")
message(STATUS "Found Boost LibPath ${Boost_LIBRARY_DIRS}")
message(STATUS "Found Boost LIBRARIES ${Boost_LIBRARIES}")

add_definitions(-DBOOST_SPIRIT_THREADSAFE)
add_definitions(-DBOOST_ALL_DYN_LINK)
add_definitions(-D_DEBUG)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

set(SRCS "${PROJECT_SOURCE_DIR}/src/log.cpp"
"${PROJECT_SOURCE_DIR}/src/net.cpp"
)

ADD_LIBRARY(common_util STATIC ${SRCS})
target_link_libraries(common_util boost_log-mt)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(common_util_test
"${PROJECT_SOURCE_DIR}/test/main.cpp" 
"${PROJECT_SOURCE_DIR}/test/singleton.cpp" 
"${PROJECT_SOURCE_DIR}/test/log.cpp" 
"${PROJECT_SOURCE_DIR}/test/net.cpp" 
)
target_link_libraries(common_util_test ${GTEST_BOTH_LIBRARIES} common_util)
add_test(NAME Test COMMAND common_util_test)