set(GCC_EXPECTED_VERSION 4.7.1)

if(CMAKE_C_COMPILER_VERSION VERSION_LESS GCC_EXPECTED_VERSION)
	message(FATAL_ERROR "GCC: Project requires version ${GCC_EXPECTED_VERSION} to build but found ${CMAKE_C_COMPILER_VERSION}")
endif()

message(STATUS "Found GCC ${CMAKE_CXX_COMPILER_VERSION}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic -Wall -Wcast-align -Wcast-qual -Wconversion -Wdisabled-optimization -Wdouble-promotion -Wextra -Wfloat-equal -Wformat -Winit-self -Winvalid-pch -Wlogical-op -Wmain -Wmissing-declarations -Wmissing-include-dirs -Wpointer-arith -Wredundant-decls -Wshadow -Wswitch-default -Wswitch-enum -Wundef -Wuninitialized -Wunreachable-code -Wwrite-strings")
message(STATUS "GCC: Enabled warnings")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og -DDEBUG")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s -Os")
