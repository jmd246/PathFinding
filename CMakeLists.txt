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

set(PROJECT_ROOT_DIR "${CMAKE_SOURCE_DIR}")
configure_file(config.h.in config.h)  # Generates config.h in the build folder
include_directories(${CMAKE_BINARY_DIR})



# Find packages installed with vcpkg
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)



# Executable
add_executable (
    PathFinding
    src/main.cpp
    src/Graph.cpp
    src/GraphDrawer.cpp
    src/GraphGenerator.cpp
    src/GraphFileManager.cpp
    src/PathFinder.cpp
    vendors/ImGuiFileDialog/ImGuiFileDialog.cpp
)

# Link dependencies
target_link_libraries(PathFinding PRIVATE
    glfw
    imgui::imgui
    glad::glad
    nlohmann_json::nlohmann_json
)

 target_include_directories(PathFinding PRIVATE include
         vendors/ImGuiFileDialog
 )
 
# Optional: For MSVC warnings
if (MSVC)
    target_compile_options(PathFinding PRIVATE /W4 /permissive-)
else()
    target_compile_options(PathFinding PRIVATE -Wall -Wextra -Wpedantic)
endif()
