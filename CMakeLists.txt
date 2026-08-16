cmake_minimum_required(VERSION 3.20)

project(riscy_emu VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(gsl GIT_REPOSITORY https://github.com/microsoft/GSL GIT_TAG v4.2.2 GIT_SHALLOW ON)

FetchContent_MakeAvailable(gsl)

set(SOURCE_DIR "src")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE INCLUDE_FILES CONFIGURE_DEPENDS "${SOURCE_DIR}/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE Microsoft.GSL::GSL)
