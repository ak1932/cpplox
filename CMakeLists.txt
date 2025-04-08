set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.13.4)
project(CPPLOX)

file(GLOB cpplox_SRC 
    "src/*.hpp"
    "src/*.h" 
    "src/*.cpp"
)

add_executable(${PROJECT_NAME} ${cpplox_SRC})
