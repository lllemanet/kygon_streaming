cmake_minimum_required(VERSION 3.21.1)

project(kygon VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Network Quick)

qt_standard_project_setup()

include_directories(src)

add_subdirectory(src/app)
add_subdirectory(src/server)
