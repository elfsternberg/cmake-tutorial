cmake_minimum_required (VERSION 2.6)
project(tutorial)
set (tutorial_VERSION_MAJOR 1)
set (tutorial_VERSION_MINOR 0)

option (USE_MYMATH "Use tutorial provided math implementation" ON)

include (CheckFunctionExists)
set(CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES} "-lm")
check_function_exists (log HAVE_LOG)
check_function_exists (exp HAVE_EXP)

configure_file (
    "${PROJECT_SOURCE_DIR}/tutorial_config.h.in"
    "${PROJECT_BINARY_DIR}/tutorial_config.h"
)

include_directories("${PROJECT_BINARY_DIR}")

add_executable(tutorial tutorial.cpp)
install (TARGETS tutorial DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/tutorial_config.h" DESTINATION include)

if (USE_MYMATH)
    include_directories ("${PROJECT_SOURCE_DIR}/mathfunctions")
    add_subdirectory(mathfunctions)
    set (EXTRA_LIBS ${EXTRA_LIBS} mathfunctions)
endif (USE_MYMATH)

target_link_libraries(tutorial ${EXTRA_LIBS})

include(CTest)
add_test (TutorialRuns tutorial 25)

macro (do_test arg result)
    add_test (TutorialComp${arg} tutorial ${arg})
    set_tests_properties(TutorialComp${arg} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

do_test(25 "25 is 5")
do_test(-25 "-25 is -nan")
do_test(0.0001 "0\\\\.0001 is 0\\\\.01")

add_test (TutorialUsage tutorial)
set_tests_properties (TutorialUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")


