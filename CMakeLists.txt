cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(NAME graph_project)
project(${NAME} VERSION 1.0)

option(VS_DEBUG_RELEASE "Generate only DEBUG and RELEASE configuration on VS" ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/_bin/")

message(STATUS "[INFO] Current directory: " ${CMAKE_SOURCE_DIR})

if(MSVC)
    include(ConfigureVS.cmake)
endif()

#-------------------------------------------------------------------------------
# Projects

add_subdirectory(application)

if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT application)
endif()
