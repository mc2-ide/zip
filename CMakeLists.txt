cmake_minimum_required(VERSION 3.16)
project(zip)
include_directories(${CMAKE_JS_INC})

file(GLOB SOURCE_FILES "src/*")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})