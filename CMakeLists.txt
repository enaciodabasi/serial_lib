cmake_minimum_required(VERSION 3.0.0)
project(serial_lib)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/serial_lib)

add_library(
    ${PROJECT_NAME}
    STATIC
    src/port.cpp
    src/utils.cpp
    src/errors.cpp
)
target_link_directories(${PROJECT_NAME} PRIVATE include/serial_lib)

add_executable(deneme test/deneme.cpp)
target_link_libraries(deneme ${PROJECT_NAME})
target_link_directories(deneme PUBLIC include/serial_lib)