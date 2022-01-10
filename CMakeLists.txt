PROJECT(common_util)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -g -ggdb -std=c++17 -fno-strict-aliasing -Wno-register")

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -std=c++17 -fno-strict-aliasing -Wno-register")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -std=c++17 -fno-strict-aliasing -Wno-register")
MESSAGE("common CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/util/include")

FIND_PACKAGE(Boost REQUIRED COMPONENTS log)
IF(NOT Boost_FOUND)
    MESSAGE("Can not find Boost")
ENDIF()
MESSAGE(STATUS "Found Boost IncPath ${Boost_INCLUDE_DIRS}")
MESSAGE(STATUS "Found Boost LibPath ${Boost_LIBRARY_DIRS}")
MESSAGE(STATUS "Found Boost LIBRARIES ${Boost_LIBRARIES}")

ADD_DEFINITIONS(-DBOOST_SPIRIT_THREADSAFE)
ADD_DEFINITIONS(-DBOOST_ALL_DYN_LINK)
ADD_DEFINITIONS(-D_DEBUG)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

# gtest
IF (NOT TARGET gtest)
    ADD_SUBDIRECTORY(gtest)
    ENABLE_TESTING()
    INCLUDE_DIRECTORIES(SYSTEM
        ${gtest_SOURCE_DIR}
        ${gtest_SOURCE_DIR}/include)
ENDIF()

SET(SRCS "${PROJECT_SOURCE_DIR}/util/src/log.cpp"
"${PROJECT_SOURCE_DIR}/util/src/net.cpp"
)

ADD_LIBRARY(common STATIC ${SRCS})
TARGET_LINK_LIBRARIES(common boost_log)

ADD_EXECUTABLE(common_util_test
"${PROJECT_SOURCE_DIR}/util/test/main.cpp" 
"${PROJECT_SOURCE_DIR}/util/test/singleton.cpp" 
"${PROJECT_SOURCE_DIR}/util/test/log.cpp" 
"${PROJECT_SOURCE_DIR}/util/test/net.cpp" 
)
TARGET_LINK_LIBRARIES(common_util_test gtest common)
ADD_TEST(NAME Test COMMAND common_util_test)
