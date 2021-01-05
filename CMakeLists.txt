cmake_minimum_required(VERSION 3.12)
project(Employees LANGUAGES CXX VERSION 1.0)

add_executable(ManualTest main.cpp Company.cpp Leader.cpp Employee.cpp Container.cpp)
target_compile_features(ManualTest PUBLIC cxx_std_20)