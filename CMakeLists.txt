cmake_minimum_required(VERSION 3.5)

project(ConsoleControl)
enable_language(C)
enable_testing()

include(common.cmake)

set(CMAKE_DEBUG_POSTFIX _d)

# By default build in Release mode
if( NOT CMAKE_BUILD_TYPE )
	set(CMAKE_BUILD_TYPE "Release")
endif()

get_filename_component(root_dir             ${CMAKE_SOURCE_DIR}          REALPATH)
get_filename_component(ConsoleControl_dir   ${root_dir}/ConsoleControl   REALPATH)
get_filename_component(Logger_dir           ${root_dir}/Logger           REALPATH)
get_filename_component(Examples_dir         ${root_dir}/Examples         REALPATH)

### ConsoleControl
get_files(
	files "${ConsoleControl_dir}" "${Logger_dir}"
	OPTIONS recurse
)
make_target(
	ConsoleControl "ConsoleControl" ${files}
	INCLUDES "${ConsoleControl_dir}/include/" "${Logger_dir}/include/"
	OPTIONS c static_runtime
)
target_link_libraries(
	ConsoleControl
	PRIVATE m
)
set_property(TARGET ConsoleControl PROPERTY C_STANDARD 11)

### Examples
get_files(
	files "${Examples_dir}" "${Logger_dir}"
	OPTIONS recurse
)
make_target(
	Examples "ConsoleControl" ${files}
	INCLUDES "${Examples_dir}/include/" "${ConsoleControl_dir}/include/" "${Logger_dir}/include/"
	OPTIONS c executable static_runtime
)
target_link_libraries(
	Examples
	PRIVATE ConsoleControl
)
set_property(TARGET Examples PROPERTY C_STANDARD 11)
target_compile_definitions(Examples PRIVATE "$<$<CONFIG:Debug>:LOGGER_ENABLED>")
