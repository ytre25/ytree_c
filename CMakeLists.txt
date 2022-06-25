project(main)

cmake_minimum_required(VERSION 2.6)
message(${CMAKE_CURRENT_SOURCE_DIR})
message(${PROJECT_NAME})

set(GROUP_NETWORK 
	${CMAKE_CURRENT_SOURCE_DIR}/network/tcpserver.h
       	${CMAKE_CURRENT_SOURCE_DIR}/network/tcpserver.cpp)
set(GROUP_UVSERVER 
	${CMAKE_CURRENT_SOURCE_DIR}/uvserver/uvserver.h
       	${CMAKE_CURRENT_SOURCE_DIR}/uvserver/uvserver.cpp)


source_group("network" FILES ${GROUP_NETWORK})
source_group("uvserver" FILES ${GROUP_UVSERVER})


include_directories()
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/ 
	${CMAKE_CURRENT_SOURCE_DIR}/network/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -D_GUN_SOURCE")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=gnu++14")


add_executable(${PROJECT_NAME}
	${GROUP_NETWORK}
	${GROUP_UVSERVER}
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)


target_link_libraries(${PROJECT_NAME} uv m dl)
