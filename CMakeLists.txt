cmake_minimum_required(VERSION 3.10)
project(DinoGame)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(DinoGame ${SOURCE_FILES})

# Correct Linking: Use the plain names, NOT the targets.
target_link_libraries(DinoGame
    SDL2main  #  SDL2main FIRST, and use the plain name, not SDL2::SDL2main
    ${SDL2_LIBRARIES}  # This will include libSDL2.dll.a (or libSDL2.a)
    ${SDL2_IMAGE_LIBRARIES} # This will include libSDL2_image.dll.a
    -lSDL2_image
)