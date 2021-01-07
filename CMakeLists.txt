cmake_minimum_required(VERSION 3.12)
project(Employees LANGUAGES CXX VERSION 1.0)

find_package(GTest REQUIRED)

add_executable(ManualTest main.cpp Company.cpp Leader.cpp Employee.cpp Container.cpp Application.cpp)
target_compile_features(ManualTest PUBLIC cxx_std_20)

enable_testing()
add_executable(Tests tests.cpp Company.cpp Leader.cpp Employee.cpp Container.cpp Application.cpp)
target_compile_features(Tests PUBLIC cxx_std_20)

target_link_libraries(Tests GTest::GTest GTest::Main)

add_test(AllTests Tests)

add_executable(DialogForm dialog.cpp Company.cpp Leader.cpp Employee.cpp Container.cpp Application.cpp)
target_compile_features(DialogForm PUBLIC cxx_std_20)
