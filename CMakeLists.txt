cmake_minimum_required(VERSION 3.9)
project(gamecpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)
include(FindPkgConfig)
pkg_search_module(SDL2_Image REQUIRED SDL2_image>=2.0.0)

add_executable(gamecpp
    src/main.cpp
    src/Game.cpp
    src/Actor.cpp
    src/Component.cpp
    src/SpriteComponent.cpp
    src/AnimSpriteComponent.cpp
    src/BGSpriteComponent.cpp

    src/Ship.cpp
)

target_include_directories(gamecpp
    PRIVATE
        include/
        ${SDL2_Image_INCLUDE_DIRS}
)

target_link_libraries(gamecpp
    PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        ${SDL2_Image_LIBRARIES}
)

add_custom_command(
    TARGET gamecpp
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:gamecpp>/Assets
)
