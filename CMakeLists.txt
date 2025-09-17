cmake_minimum_required(VERSION 3.12)

project(ArgsP VERSION 0.3.2)

option(TESTS "Enable tests" OFF)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(TESTS)
	add_subdirectory(tests)
endif()

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
	    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/SCT/${PROJECT_NAME})
install(FILES LICENSE
		DESTINATION ${CMAKE_INSTALL_PREFIX}/share/licenses/SCT/${PROJECT_NAME})
