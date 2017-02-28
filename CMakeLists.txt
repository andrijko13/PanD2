cmake_minimum_required (VERSION 2.6)
project (Magi_Engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

set(GCC_COVERAGE_COMPILE_FLAGS "")
set(GCC_COVERAGE_LINK_FLAGS    "")

include_directories(include)

set (Magi_Engine_VERSION_MAJOR 0)
set (Magi_Engine_VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

find_package(CUDA QUIET REQUIRED)

#set(CMAKE_MACOSX_RPATH 1)
 
file(GLOB SOURCES "src/lib/*.cpp")
ADD_LIBRARY( ajengine STATIC#SHARED
       ${SOURCES}
       )
#TARGET_LINK_LIBRARIES( MyLibraryName  ITKCommon )

add_executable(prog src/testing/main.cpp)
target_link_libraries(prog ajengine)
