cmake_minimum_required(VERSION 3.6)
project(GeneticGladiatorSimulator)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp SimulationFramework/SOIL.h SimulationFramework/Simulator.cpp SimulationFramework/Simulator.h SimulationFramework/Shader.cpp
        SimulationFramework/Shader.h SimulationFramework/Texture.cpp SimulationFramework/Texture.h SimulationFramework/ResourceManager.cpp
        SimulationFramework/ResourceManager.h SimulationFramework/SpriteRenderer.cpp SimulationFramework/SpriteRenderer.h Simulation/GameObject.cpp
        Simulation/GameObject.h Simulation/SimulationManager.cpp Simulation/SimulationManager.h DataStructures/QueueNode.h DataStructures/Queue.h
        SimulationFramework/TextRenderer.cpp SimulationFramework/TextRenderer.h DataStructures/Stack.h DataStructures/SimulationMatrix.cpp DataStructures/SimulationMatrix.h)

# Find glfw header
find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h ${HEADER_SEARCH_PATH})


# Find glfw library
find_library(GLFW_LIBRARIES glfw3 ${LIBRARY_SEARCH_PATH})


# Find GLEW, the OpenGL Extension Wrangler
find_path(GLEW_INCLUDE_DIR GL/glew.h
        ${HEADER_SEARCH_PATH}
        )

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})


# Set additional libs
set( ADDITIONAL_LIBS
        -lGLEW
        -lGLU
        -lGL
        -lglfw3
        -pthread
        -lrt
        -lX11
        -lXi
        -lXrandr
        -lXxf86vm
        -lXinerama
        -lXcursor
        -ldl
        -lSOIL
        )

# Include directories for this project
set(INCLUDE_PATH
        ${OPENGL_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR}
        ${FREETYPE_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIR}
        )


# Libraries needed on all platforms for this project
set(LIBRARIES
        ${OPENGL_LIBRARIES}
        ${GLFW_LIBRARIES}
        ${GLEW_INCLUDE_DIR}
        ${X11_LIBRARIES}
        ${ADDITIONAL_LIBS}
        )


set(CMAKE_CXX_FLAGS "-O0 -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "-v")

# Add a target executable
add_executable(GeneticGladiatorSimulator ${SOURCE_FILES})


# Libraries to be linked
target_link_libraries(GeneticGladiatorSimulator
        ${LIBRARIES}
        ${FREETYPE_LIBRARIES}
        )

