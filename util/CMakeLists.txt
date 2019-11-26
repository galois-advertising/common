project(common)
cmake_minimum_required(VERSION 2.8)
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
message(${PROJECT_SOURCE_DIR})
message(${PROJECT_BINARY_DIR})
set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)
#configure_file (
#  "${PROJECT_SOURCE_DIR}/common/config.h.in"
#  "${PROJECT_BINARY_DIR}/common/config.h"
#  )
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-Bsymbolic")
else()
endif()

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

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

ADD_LIBRARY(common STATIC ${PROJECT_SOURCE_DIR}/src/log.cpp)
target_link_libraries(common boost_log-mt)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(common_test
"${PROJECT_SOURCE_DIR}/test/main.cpp" 
"${PROJECT_SOURCE_DIR}/test/singleton.cpp" 
"${PROJECT_SOURCE_DIR}/test/log.cpp" 
)
target_link_libraries(common_test ${GTEST_BOTH_LIBRARIES} common)
add_test(NAME Test COMMAND common_test)