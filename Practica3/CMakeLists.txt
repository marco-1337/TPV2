cmake_minimum_required(VERSION 3.15...3.30)

project(TPV2_Practica2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compila con la biblioteca SDL
if (CMAKE_HOST_WIN32)
	# Utiliza las bibliotecas compiladas que van incluidas
	# en el paquete con el proyecto de Visual Studio
	include_directories(
		external/SDL2-2.30.12/include
		external/SDL2_image-2.8.4/include
        external/SDL2_mixer-2.8.0/include
		external/SDL2_ttf-2.24.0/include
	)

	link_directories(
		external/SDL2-2.30.12/lib/x64
		external/SDL2_image-2.8.4/lib/x64
        external/SDL2_mixer-2.8.0/lib/x64
		external/SDL2_ttf-2.24.0/lib/x64
	)
    link_libraries(
		SDL2.lib
		SDL2main.lib
		SDL2_image.lib
		SDL2_ttf.lib
        SDL2_mixer.lib
	)
else()
	# En otros sistemas operativos utiliza find_package
	# para encontrar las bibliotecas instaladas aparte

	find_package(SDL2 REQUIRED)
	find_package(SDL2_image REQUIRED)
    find_package(SDL2_mixer REQUIRED)
	find_package(SDL2_ttf REQUIRED)

	include_directories(${SDL2_INCLUDE_DIRS})
    link_libraries(${SDL2_LIBRARIES})
endif()

# Incluir directorios
include_directories(
	sdlutils
	utils
    json
	game
)


# Crear ejecutable
add_executable(TPV2_Practica3
	
	main.cpp

    sdlutils/SDLUtils.cpp
    sdlutils/SDLUtilsError.cpp
    sdlutils/SoundEffect.cpp
    sdlutils/Texture.cpp
	
	utils/Collisions.cpp
    utils/Vector2D.cpp

    json/json_demo.cpp
    json/JSON.cpp
    json/JSONValue.cpp

	game/Game.cpp
	game/LittleWolf.cpp
)
# Definir directorios de salida
set_target_properties(TPV2_Practica3 PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release
)

set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/resources)

add_custom_command(TARGET TPV2_Practica3 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${RESOURCES_DIR} $<TARGET_FILE_DIR:TPV2_Practica3>/resources
)

if (CMAKE_HOST_WIN32)
    set(DLL_DIR ${CMAKE_SOURCE_DIR}/dlls)

    add_custom_command(TARGET TPV2_Practica3 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${DLL_DIR} $<TARGET_FILE_DIR:TPV2_Practica3>
    )

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")

		set(PDB_DIR ${CMAKE_SOURCE_DIR}/pdbs)

		add_custom_command(TARGET TPV2_Practica3 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${PDB_DIR} $<TARGET_FILE_DIR:TPV2_Practica3>
	)
	endif()

endif()