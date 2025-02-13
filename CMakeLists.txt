cmake_minimum_required(VERSION 3.10)
project(DinoGame)

set(CMAKE_CXX_STANDARD 17)  # Use C++17 standard

# Find SDL2 and SDL2_image
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)  # Include SDL2_image package
find_package(SDL2_ttf REQUIRED)  # If you're using fonts
# find_package(SDL2_mixer REQUIRED)  # Uncomment if you're using sound

# Include directories for SDL2
include_directories(${CMAKE_SOURCE_DIR}/include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

# Source files
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# Create executable
add_executable(DinoGame ${SOURCE_FILES})

# Link SDL2 and SDL2_image libraries
target_link_libraries(DinoGame 
    ${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES} 
    ${SDL2_TTF_LIBRARIES} 
)

# If you're using sound, uncomment the line below
# target_link_libraries(DinoGame ${SDL2_MIXER_LIBRARIES})
