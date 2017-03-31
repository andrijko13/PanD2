cmake_minimum_required (VERSION 2.6)
project (pand2)

set(CMAKE_CXX_COMPILER "g++")
enable_testing()

option(i386 "i386" ON)
option(compileStatic "staticCompile" OFF)

set(CMAKE_MACOSX_RPATH 1)

set(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11")# -stdlib=libc++")
set(GCC_COVERAGE_LINK_FLAGS    "")

include_directories(include)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})

set (pand2_VERSION_MAJOR 0)
set (pand2_VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

file(GLOB TEST_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/test/*.cpp)

file(GLOB SOURCES "src/lib/*.cpp")

#if (compileStatic)
#ADD_LIBRARY( ${PROJECT_NAME} STATIC # can make this shared
#       ${SOURCES}
#       )
#else(compileStatic)
ADD_LIBRARY( ${PROJECT_NAME} SHARED # can make this shared
       ${SOURCES}
       )
#endif(compileStatic)

#if (i386)
#set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32") # delete this line if working with x86-64
#endif (i386)

find_library(AJX ajx)
target_link_libraries(${PROJECT_NAME} ${AJX})

file(GLOB EXAMPLE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/examples/*.cpp)

foreach(example_src_file ${EXAMPLE_FILES})
        get_filename_component(exampleName ${example_src_file} NAME_WE)

        add_executable(${exampleName} ${example_src_file})
        target_link_libraries(${exampleName} ${PROJECT_NAME} ${Boost_LIBRARIES})
        #if (i386)
        #set_target_properties(${exampleName} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32") # delete this line if working with x86-64
        #endif (i386)
        set_target_properties(${exampleName} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/binaries/examples)
endforeach(example_src_file)

#if (! i386)
foreach(test_src_file ${TEST_FILES})
        get_filename_component(testName ${test_src_file} NAME_WE)

        add_executable(${testName} ${test_src_file})
        target_link_libraries(${testName} ${Boost_LIBRARIES} ${PROJECT_NAME})
        #set_target_properties(${testName} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
        set_target_properties(${testName} PROPERTIES 
            RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/binaries/tests)

        add_test(NAME ${testName} 
                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/binaries/tests 
                 COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/binaries/tests/${testName} )
endforeach(test_src_file)
#endif (! i386)

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib)

# Install library headers
file(GLOB HEADERS include/*.h)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})

