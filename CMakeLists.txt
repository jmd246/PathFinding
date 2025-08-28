cmake_minimum_required(VERSION 3.18)
project(PathFinding LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(/std:c++latest)


# Force CMake to use your specific vcpkg installation
set(CMAKE_TOOLCHAIN_FILE
    "C:/Users/Owner/OneDrive/Desktop/SDLIntro/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file"
)



# Find packages installed with vcpkg
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)


# Executable
add_executable(PathFinding
    src/main.cpp
    src/Graph.cpp
    src/GraphDrawer.cpp
)

# Link dependencies
target_link_libraries(PathFinding PRIVATE
    glfw
    imgui::imgui
    glad::glad
)

 target_include_directories(PathFinding PRIVATE include)
 
# Optional: For MSVC warnings
if (MSVC)
    target_compile_options(PathFinding PRIVATE /W4 /permissive-)
else()
    target_compile_options(PathFinding PRIVATE -Wall -Wextra -Wpedantic)
endif()
