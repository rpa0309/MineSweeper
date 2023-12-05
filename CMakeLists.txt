cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Project_3_Version_2)

set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

add_executable(Project_3_Version_2 main.cpp
        Tile.cpp
        Tile.h
        TextureManager.cpp
        TextureManager.h
)
target_link_libraries(Project_3_Version_2 sfml-system sfml-window sfml-graphics sfml-audio)



