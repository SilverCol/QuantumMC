add_executable(anharmonic main_ah.cpp MCQoscilator_ah.cpp)
target_include_directories(anharmonic PRIVATE ../pcg_random/include)
