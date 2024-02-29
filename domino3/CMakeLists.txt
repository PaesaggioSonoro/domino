cmake_minimum_required(VERSION 3.27)
project(domino3 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL2_PATH "SDL2/x86_64-w64-mingw32")
set(SDL2_DIR "SDL2_image/x86_64-w64-mingw32")
set(SDL2_TTF_DIR "SDL2_ttf/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Manually specify SDL2_ttf library and include directories
set(SDL2_TTF_LIBRARY "D:/UNI/IAP/domino2/domino3/SDL2_ttf/x86_64-w64-mingw32/lib/libSDL2_ttf.dll.a")
set(SDL2_TTF_INCLUDE_DIRS "${SDL2_TTF_DIR}/include")

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
add_executable(domino3 main.c game.c game.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARY})
