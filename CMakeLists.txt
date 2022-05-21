cmake_minimum_required(VERSION 3.0.0)
project(ellipsoid VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)


set(CMAKE_BUILD_TYPE Debug)
message(STATUS ${TESTS})
# set(TESTS)
# set(CMAKE_BUILD_TYPE Release)


set(DEFAULT_BUILD_TYPE Release)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE DEFAULT_BUILD_TYPE)
  message(STATUS "ELLIPSOID: Using default build type: ${CMAKE_BUILD_TYPE}")
else()
  message(STATUS "ELLIPSOID: Build type: ${CMAKE_BUILD_TYPE}")
endif()


if(CMAKE_BUILD_TYPE STREQUAL Release)
  add_library(ellipsoid SHARED)
else()
  add_executable(ellipsoid main.cpp)
  target_compile_definitions(ellipsoid PUBLIC ELLIPSOID_DEBUG)

  target_compile_definitions(ellipsoid PUBLIC EP_OPENGL)
endif()

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)


add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)

target_compile_features(ellipsoid PRIVATE cxx_std_17)