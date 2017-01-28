#
# Cmake Tutorial
#
# This is a working example of the tutorial from the CMake website.  It
# isn't intended to be anything more than that.
#

# Specify what versions of Cmake we support.
#
cmake_minimum_required (VERSION 2.6)

# Enables the use of VERSION inside the project() function.
#
cmake_policy (SET CMP0048 NEW)

# Specify the name of the project.  This results in the following
# variables being set and available for use later.
#
# PROJECT_NAME, PROJECT_SOURCE_DIR, ${PROJECT_NAME}_SOURCE_DIR,
# PROJECT_BINARY_DIR, ${PROJECT_NAME}_BINARY_DIR
#
project(tutorial VERSION 1.1 LANGUAGES "CXX")
#
# 'project' takes arguments, 'VERSION' and 'LANGUAGE'.  See the
# accompanying documentation.

# These variables are set using the VERSION argument above.  This is an
# alternative (older) variant.
#
set (tutorial_VERSION_MAJOR 1)
set (tutorial_VERSION_MINOR 2)

# Another way:
#
set (${PROJECT_NAME}_VERSION_MAJOR 1)
set (${PROJECT_NAME}_VERSION_MINOR 4)

#
# As with Makefiles, "last declaration wins."
#

# Specify an option that can control future options.  This can also
# modify the behavior inside ".in" configuration files in the project
# proper, defining them and making them available to preprocessors.
#
option (USE_MYMATH "Use tutorial provided math implementation" ON)

# Include a CMAKE module
#
include (CheckFunctionExists)

# Specify extra libraries needed to make programs.  This must be
# declared before check_function_exists() is called, or the linker will
# fail when linking math functions.
# 
set(CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES} "-lm")

# Attempt to build a test program that links and dereferences these
# functions.  If the build is successful, set the variable as an option.
#
check_function_exists (log HAVE_LOG)
check_function_exists (exp HAVE_EXP)

# Preprocess a configuration file, making simple textual substitutions.
#
configure_file (
    "${PROJECT_SOURCE_DIR}/tutorial_config.h.in"
    "${PROJECT_BINARY_DIR}/tutorial_config.h"
)

include_directories("${PROJECT_BINARY_DIR}")

# Define the executable to be build, along with the source dependencies.
# 
add_executable(tutorial tutorial.cpp)

# Describe the installation destination.
#
install (TARGETS tutorial DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/tutorial_config.h" DESTINATION include)

# If the option is set above, include a subdirectory.  It will have its
# own CMakeLists.txt file to describe how its contents are to be built.
#
if (USE_MYMATH)
    include_directories ("${PROJECT_SOURCE_DIR}/mathfunctions")
    add_subdirectory(mathfunctions)
    set (EXTRA_LIBS ${EXTRA_LIBS} mathfunctions)

    # Ensure that the extra libraries are included as a requirement for
    # a target.  This creates a dependency graph that must be resolved
    # in the correct order.
    #
    target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})
endif (USE_MYMATH)

# Define basic unit tests that run a program and analyze the output for
# very simple strings
#
include(CTest)

# A basic test... does it run at all?
#
add_test (TutorialRuns tutorial 25)

# A defined macro that tests the propertis of the results.  The first
# argument to add_test and set_tests_properties is a token to identify
# the test to the reviewer.
#
macro (do_test arg result)
    add_test (TutorialComp${arg} tutorial ${arg})
    set_tests_properties(TutorialComp${arg} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

do_test(25 "25 is 5")
do_test(-25 "-25 is -nan")
do_test(0.0001 "0\\\\.0001 is 0\\\\.01")

add_test (TutorialUsage tutorial)
set_tests_properties (TutorialUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")


