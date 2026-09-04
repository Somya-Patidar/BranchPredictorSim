cmake_minimum_required(VERSION 3.16)

project(BranchPredictorSim VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(BranchPredictorSim
    src/main.cpp
    src/Metrics.cpp
    src/TraceReader.cpp
    src/Simulator.cpp
    src/AlwaysTaken.cpp
    src/AlwaysNotTaken.cpp
)