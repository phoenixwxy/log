cmake_minimum_required(VERSION 3.0.0)
project(log VERSION 0.1.0)

include(CTest)
enable_testing()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
      "Choose the type of build, options are: Debug Release."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

message(${CMAKE_BUILD_TYPE})

if(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/log/src)
set(UTILS_SRC ${PROJECT_SOURCE_DIR}/log/utils)

# Add sources
file(GLOB SOURCES
    # "${PROJECT_SOURCE_DIR}"
    "${SOURCE_DIR}/*.c"
    "${SOURCE_DIR}/*.cpp"
    "${UTILS_SRC}/*.cpp"
)

include_directories("${PROJECT_SOURCE_DIR}/log/include")
include_directories("${PROJECT_SOURCE_DIR}/log/utils")

add_library(log ${SOURCES})

# file(COPY ${PROJECT_SOURCE_DIR}/log/config/PLogSettings.txt DESTINATION ${PROJECT_SOURCE_DIR}/bin)

# add_custom_command(TARGET log PRE_BUILD
#         COMMAND ${CMAKE_COMMAND} -E
#         remove ${PROJECT_SOURCE_DIR}/bin)

add_custom_command(TARGET log POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E
        copy_if_different ${PROJECT_SOURCE_DIR}/log/config/PLogSettings.txt ${PROJECT_SOURCE_DIR}/bin)

#############################################################
## Test Log System
set(TEST_SRC ${PROJECT_SOURCE_DIR}/log/test)
set(LIB_LINK_DIR ${PROJECT_SOURCE_DIR}/lib)

include_directories("${PROJECT_SOURCE_DIR}/log/test")
include_directories("${PROJECT_SOURCE_DIR}/log/utils")
include_directories("${PROJECT_SOURCE_DIR}/log/include")

file(GLOB TEST_SOURCE
    "${TEST_SRC}/*.cpp"
)

link_directories(${LIB_LINK_DIR})

add_executable(test_main ${TEST_SOURCE})
target_link_libraries(test_main liblog.a)
add_dependencies(test_main log)


############################################################
## set out lib directory
set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/lib/debug)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/lib/release)

############################################################
## set out bin directory
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/debug)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/release)

# set(CMAKE_DEBUG_POSTFIX "_d")
# set(CMAKE_RELEASE_POSTFIX "_r")

# set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_POSTFIX "_d")
# set_target_properties(${TARGET_NAME} PROPERTIES RELEASE_POSTFIX "_r")


set_property(TARGET log PROPERTY CXX_STANDARD 11)
set_property(TARGET log PROPERTY CXX_STANDARD_REQUIRED ON)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
