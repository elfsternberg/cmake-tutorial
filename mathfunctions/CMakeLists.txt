add_executable(maketable maketable.cpp)

add_custom_command (
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/table.h
    COMMAND maketable ${CMAKE_CURRENT_BINARY_DIR}/table.h
    DEPENDS maketable
)

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
add_library(mathfunctions mysqrt.cpp ${CMAKE_CURRENT_BINARY_DIR}/table.h )
install (FILES mathfunctions.h DESTINATION include)
