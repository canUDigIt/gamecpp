cmake_minimum_required(VERSION 3.9)
project(gamecpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_Image REQUIRED sdl2_image)

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
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_Image_INCLUDE_DIRS}
)

target_link_libraries(gamecpp
    PRIVATE
        ${SDL2_LIBRARIES}
        ${SDL2_Image_LINK_LIBRARIES}
)

target_compile_features(gamecpp PUBLIC cxx_std_17)

add_custom_command(
    TARGET gamecpp
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:gamecpp>/Assets
)
