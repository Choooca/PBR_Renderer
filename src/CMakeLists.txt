set(PROJECT_SOURCES "")

add_subdirectory(renderer)
add_subdirectory(input_handler)
add_subdirectory(behaviour_objects)

list(APPEND PROJECT_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/application.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE
							PROJECT_ROOT="${CMAKE_SOURCE_DIR}"
							ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets"
							SHADERS_PATH="${CMAKE_SOURCE_DIR}/assets/shaders"
							TEXTURES_PATH="${CMAKE_SOURCE_DIR}/assets/textures")

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} PRIVATE glad glm::glm SDL3::SDL3 stb)

if(WIN32)
	set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE $<CONFIG:Release>)

	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_FILE:SDL3::SDL3>
		$<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()
