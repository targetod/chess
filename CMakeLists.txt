cmake_minimum_required(VERSION 2.8.12)

project(chess)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set (CMAKE_BUILD_TYPE Debug)
#set (CMAKE_BUILD_TYPE Release)
# Boost
set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)


set (CMAKE_CXX_STANDARD 14)

#SET(GCC_COVERAGE_LINK_FLAGS    "-pthread")

#set (CMAKE_CXX_FLAGS "-lboost_system")
#set (CMAKE_CXX_FLAGS "-lboost_thread")
#set (CMAKE_CXX_FLAGS "-lpthread")

# my settings boost path
SET (BOOST_MIN_VERSION "1.60.0")
#set(Boost_NO_SYSTEM_PATHS TRUE)
#if (Boost_NO_SYSTEM_PATHS)
#  set(BOOST_ROOT "/usr/local")
#  set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
#  set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
#endif (Boost_NO_SYSTEM_PATHS)

find_package(Boost ${BOOST_MIN_VERSION}  REQUIRED COMPONENTS
    system
    coroutine
    thread
    context)
if(Boost_FOUND )
  include_directories(${Boost_INCLUDE_DIRS})
endif()

FILE(GLOB_RECURSE HEADER "*engine/*.h")
#FILE(GLOB_RECURSE SRC "engine/*.cpp")
SET (SRC engine/chessboard.cpp
    engine/global.cpp
    engine/aiplayer.cpp    
    engine/humanplayer.cpp
    engine/perfomancemeasurement.cpp
    engine/config.cpp
    engine/asyncplayer.cpp
    engine/asyncaiplayer.cpp)

include_directories("engine")
include_directories("tests")


##########GTEST
# Download and unpack googletest at configure time

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  #message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(unit_test tests/tests.cpp ${SRC} ${HEADER})
target_link_libraries(unit_test gtest_main ${Boost_LIBRARIES})

#####Examples
add_executable(example_ai_vs_human examples/ai_vs_human.cpp ${SRC} ${HEADER})
target_link_libraries(example_ai_vs_human ${Boost_LIBRARIES} pthread)

add_executable(example_ai_vs_ai examples/ai_vs_ai.cpp ${SRC} ${HEADER})
target_link_libraries(example_ai_vs_ai ${Boost_LIBRARIES} pthread)

add_executable(example_ai_vs_ai_async examples/ai_vs_ai_async.cpp ${SRC} ${HEADER})
target_link_libraries(example_ai_vs_ai_async ${Boost_LIBRARIES} pthread)

#add_custom_command(
#     TARGET unit_test
#     POST_BUILD
#     COMMAND ./unit_test
#     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#     COMMENT "Run tests"
#)


