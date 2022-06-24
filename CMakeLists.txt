

project(main)

cmake_minimum_required(VERSION 2.6)
message(${CMAKE_CURRENT_SOURCE_DIR})
message(${PROJECT_NAME})
#include_directories()
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(${PROJECT_NAME} uv)