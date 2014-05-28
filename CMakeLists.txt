cmake_minimum_required(VERSION 2.6)
project(GAME)

if(CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE Debug)
endif()

set(GAME_VERSION_MAJOR 1)
set(GAME_VERSION_MINOR 0)

configure_file(
	"${PROJECT_SOURCE_DIR}/build/config.h.in"
	"${PROJECT_BINARY_DIR}/build/config.h"
)
include_directories("${PROJECT_BINARY_DIR}")

set(EXECUTABLE_NAME "GAME")

set(HEADERS
	Config.hpp
	Cell.hpp
	Systems/BaseSystem.hpp
	Systems/RenderSystem.hpp
	Systems/RuleSystem.hpp
)

add_executable(${EXECUTABLE_NAME} ${HEADERS} Systems/RuleSystem.cpp Neighborhoods/Moore.cpp World.cpp Game.cpp main.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED system window graphics)

if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/build/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${GAME_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${GAME_VERSION_MINOR}")
include(CPack)
