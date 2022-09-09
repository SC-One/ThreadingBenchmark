cmake_minimum_required(VERSION 3.5)

project(ThreadingBenchmark
    DESCRIPTION "the project just made for profiling std::future and std::thread in simple cases"
    LANGUAGES CXX
)

message(VERBOSE "Project description: ${CMAKE_PROJECT_DESCRIPTION}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads)
find_package(benchmark REQUIRED)


## simple cases exe
set(SIMPLE_CASES_PRJ_NAME SimpleCases)
add_executable(${SIMPLE_CASES_PRJ_NAME}
    SimpleCases.cpp
)
target_link_libraries(${SIMPLE_CASES_PRJ_NAME}
    Qt5::Core
    Threads::Threads
    benchmark::benchmark
)

### writer/reader exe
set(WRITER_READER_PRJ_NAME Writer)
add_executable(${WRITER_READER_PRJ_NAME}
    WriterReader.cpp
)
target_link_libraries(${WRITER_READER_PRJ_NAME}
    Qt5::Core
    Threads::Threads
    benchmark::benchmark
)


