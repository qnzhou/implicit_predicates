cmake_minimum_required(VERSION 3.14)

project(implicit_predicates LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
include(absl)
#include(spdlog)
#include(mshio)
include(indirect_predicates)

# Internal lib contains the specialized indirect predicates.
file(GLOB INTERNAL_INC_FILES ${CMAKE_CURRENT_LIST_DIR}/include/internal/*.h)
file(GLOB INTERNAL_SRC_FILES ${CMAKE_CURRENT_LIST_DIR}/src/internal/*.cpp)

add_library(internal_implicit_predicates STATIC ${INTERNAL_SRC_FILES} ${INTERNAL_INC_FILES})
target_link_libraries(internal_implicit_predicates PUBLIC
    indirect_predicates::indirect_predicates)
target_compile_features(internal_implicit_predicates PRIVATE cxx_std_17)
target_compile_options(internal_implicit_predicates PRIVATE "-O0"
    "-Wno-format-security" "-Wno-unknown-pragmas" "-Wno-return-type")
add_library(implicit_predicates::internal ALIAS internal_implicit_predicates)

file(GLOB INC_FILES ${CMAKE_CURRENT_LIST_DIR}/include/*.h)
file(GLOB SRC_FILES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_library(implicit_predicates STATIC ${SRC_FILES} ${INC_FILES})
target_link_libraries(implicit_predicates PUBLIC
    absl::numeric #mshio::mshio spdlog::spdlog
    implicit_predicates::internal)
target_include_directories(implicit_predicates PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
target_compile_features(implicit_predicates PRIVATE cxx_std_17)
if(NOT MSVC)
    target_compile_options(implicit_predicates PRIVATE "-Wall")
endif()
add_library(implicit_predicates::implicit_predicates ALIAS implicit_predicates)

option(IMPLICIT_PREDICATES_UNIT_TESTS "Build implicit predicates unit tests" OFF)
if (IMPLICIT_PREDICATES_UNIT_TESTS)
    include(CTest)
    enable_testing()
    include(Catch2)

    file(GLOB TEST_FILES "${CMAKE_CURRENT_LIST_DIR}/tests/*.cpp")
    add_executable(implicit_predicates_tests ${TEST_FILES})
    target_link_libraries(implicit_predicates_tests PRIVATE
        implicit_predicates::implicit_predicates Catch2::Catch2)
    target_compile_features(implicit_predicates_tests PRIVATE cxx_std_17)
    target_compile_definitions(implicit_predicates_tests PRIVATE CATCH_CONFIG_ENABLE_BENCHMARKING)
    catch_discover_tests(implicit_predicates_tests)
endif()
