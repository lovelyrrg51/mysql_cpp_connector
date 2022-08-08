# CMake Minimum Required
cmake_minimum_required(VERSION 3.22)

# Project Name
project(MySQL_Cpp_Example)

# Include Directories
include_directories(${PROJECT_SOURCE_DIR})
include(FindPkgConfig)

# Package Check Modules
pkg_check_modules(LIBMYSQLCLIENT REQUIRED mysqlclient)

# Add MysqlClient Flags
foreach(FLAG ${LIBMYSQLCLIENT_CFLAGS_OTHER})
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAG}")
endforeach()

# Link Directories
link_directories(${LIBMYSQLCLIENT_LIBRARY_DIRS})

# Add Executable
add_executable(output main.cpp)

# Target Include Directories
target_include_directories(output PRIVATE ${LIBMYSQLCLIENT_INCLUDE_DIRS})

# Target Include Libraries
target_link_libraries(output PRIVATE ${LIBMYSQLCLIENT_LIBRARIES})