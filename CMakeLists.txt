cmake_minimum_required(VERSION 3.20)

project(
	PBR_RENDERER
	VERSION 1.0.0
	LANGUAGES CXX C # SET CPP & C FOR GLAD
)

# SET CPP STANDARD
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}) # Where the output .exe and .dll go
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs) # Where output libs .dll will go
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs) # Where output libs .lib will go

# For multi config generators like Visual Studio
foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
	string(TOUPPER ${CONFIG} CONFIG_UPPER)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${CMAKE_BINARY_DIR})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${CMAKE_SOURCE_DIR}/libs)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${CMAKE_SOURCE_DIR}/libs)
endforeach()

include(FetchContent) # including Fetch Content Module

# Fetch glm header only math library
FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm.git
	GIT_TAG 1.0.1
)

# Fetch SDL3
FetchContent_Declare(
	SDL3
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG release-3.2.24
)

FetchContent_MakeAvailable(glm SDL3)

add_library(glad STATIC ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/external/glad/include)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${CMAKE_SOURCE_DIR}/external/stb)

add_subdirectory(src)