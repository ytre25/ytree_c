project(main)

cmake_minimum_required(VERSION 2.6)
message(${CMAKE_CURRENT_SOURCE_DIR})
message(${PROJECT_NAME})

set(GROUP_NETWORK 
	${CMAKE_CURRENT_SOURCE_DIR}/network/tcpserver.h
       	${CMAKE_CURRENT_SOURCE_DIR}/network/tcpserver.cpp)

source_group("network" FILES ${GROUP_NETWORK})

include_directories()
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/ 
	${CMAKE_CURRENT_SOURCE_DIR}/network/)


add_executable(${PROJECT_NAME}
	${GROUP_NETWORK}
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)


target_link_libraries(${PROJECT_NAME} uv)
