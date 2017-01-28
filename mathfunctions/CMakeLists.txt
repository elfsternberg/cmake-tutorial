# Defines an executable to be built in line with the project.
# 
add_executable(maketable maketable.cpp)


# Defines a custom command that must be run in order to complete
# compilation.  The output can be defined, and therefore must exist to
# make sense to the add_library below.
#
add_custom_command (
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/table.h
    COMMAND maketable ${CMAKE_CURRENT_BINARY_DIR}/table.h

    # Defines a dependency, so ensures compilation order
    DEPENDS maketable
)

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

# Specify that mathfunctions is a library and list its requirements.
# Note that "table.h" is a requirement, and its source is listed
# above as an output, making it a dependency, which in turn has a
# dependency on maketable.
#
add_library(mathfunctions mysqrt.cpp ${CMAKE_CURRENT_BINARY_DIR}/table.h )

# Specify where these things are to be installed.
#
install (FILES mathfunctions.h DESTINATION include)
