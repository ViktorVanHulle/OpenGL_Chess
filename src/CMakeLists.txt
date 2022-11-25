# executable file creation
add_executable(
	Chess
	main.cpp
	window.cpp
	board.cpp
	selector.cpp
 "board.h" "Shaders.h" "selector.h" "units.h" "units.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE TCLAP)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)
target_link_libraries(${PROJECT_NAME} PRIVATE stb)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_definitions(${PROJECT_NAME} PRIVATE TEXTURE_DIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/")
target_compile_definitions(${PROJECT_NAME} PRIVATE STB_IMAGE_IMPLEMENTATION)