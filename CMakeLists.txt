cmake_minimum_required(VERSION 3.00)

project(ArgumentsParser VERSION 0.0.1)

include(GNUInstallDirs)

option(SCT_NO_BUILD "Don't compile libraries" OFF)

set(CMAKE_CXX_STANDARD 20)

function(list_dir currdir extension result)
	file(GLOB_RECURSE children
		 LIST_DIRECTORIES true
		 RELATIVE ${currdir} ${currdir}/*.${extension})

	set(res "")
	foreach(child ${children})
		if(NOT IS_DIRECTORY ${currdir}/${child})
#		else()
			list(APPEND res "${currdir}/${child}")
		endif()
	endforeach()

	set(${result} ${res} PARENT_SCOPE)
endfunction()

list_dir("${CMAKE_CURRENT_SOURCE_DIR}/src" cpp SRC)

if(NOT SCT_NO_BUILD)
	set(CMAKE_POSITION_INDEPENDENT_CODE ON)
	add_library(${PROJECT_NAME}_obj OBJECT ${SRC})
	target_include_directories(${PROJECT_NAME}_obj PUBLIC
							   "${CMAKE_CURRENT_SOURCE_DIR}/include")

	add_library(${PROJECT_NAME} SHARED $<TARGET_OBJECTS:${PROJECT_NAME}_obj>)
	add_library(${PROJECT_NAME}_static
				STATIC $<TARGET_OBJECTS:${PROJECT_NAME}_obj>)
endif()

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
	    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/SCT/${PROJECT_NAME})
if(NOT SCT_NO_BUILD)
	install(TARGETS ${PROJECT_NAME}
			DESTINATION ${CMAKE_INSTALL_LIBDIR}/SCT)
	install(TARGETS ${PROJECT_NAME}_static
			DESTINATION ${CMAKE_INSTALL_LIBDIR}/SCT)
endif()
