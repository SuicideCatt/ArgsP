include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/ArgsP/Tests")

add_executable(ArgsP-test main.cpp)
set_target_properties(ArgsP-test PROPERTIES
	OUTPUT_NAME "test")

add_executable(ArgsP-new_param add_new_parameter.cpp)
set_target_properties(ArgsP-new_param PROPERTIES
	OUTPUT_NAME "new_param")

add_executable(ArgsP-from_readme_exception from_readme_exception.cpp)
set_target_properties(ArgsP-from_readme_exception PROPERTIES
	OUTPUT_NAME "from_readme_exception")

add_executable(ArgsP-from_readme_no_exception from_readme_no_exception.cpp)
set_target_properties(ArgsP-from_readme_no_exception PROPERTIES
	OUTPUT_NAME "from_readme_no_exception")
