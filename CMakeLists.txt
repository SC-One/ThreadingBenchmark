cmake_minimum_required(VERSION 3.5)

project(ThreadingBenchmark
    DESCRIPTION "the project just made for profiling std::future and std::thread in simple cases"
    LANGUAGES CXX
)

message(VERBOSE "Project description: ${CMAKE_PROJECT_DESCRIPTION}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)
find_package(Threads)
find_package(benchmark REQUIRED)

set(SIMPLE_CASES_PROJECT SimpleCases)

add_executable(${SIMPLE_CASES_PROJECT}
    SimpleCases.cpp
)

target_link_libraries(${SIMPLE_CASES_PROJECT}
    Qt5::Core
    Threads::Threads
    benchmark::benchmark
)
