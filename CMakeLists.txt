cmake_minimum_required(VERSION 3.13)
project(vaja_IV_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(run src/main.cpp src/MCQoscilator.cpp src/MCQoscilator.h src/MCQoscilator_ah.cpp src/MCQoscilator_ah.h)
target_include_directories(run PRIVATE pcg_random/include)