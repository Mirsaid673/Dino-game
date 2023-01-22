cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME openGL)
project(${PROJECT_NAME})

set(EXECUTABLE out)
set(CXX_STANDARD 17)
set(LIBRARIES GL GLEW glfw)
file(GLOB SOURCES "Engine/*/*.cpp" "Engine/*/*/*.cpp" "Engine/*/*.h" "Engine/*/*/*.h")
set(SOURCES ${SOURCES} main.cpp dino/ground.h dino/game.h dino/dino.h dino/physics.h dino/physics.cpp dino/enemy.h)
file(GLOB INCLUDE_DIR "Engine/Vendor/*" "Engine/*/" ${CMAKE_SOURCE_DIR}/Engine)
file(GLOB LIBS_INCLUDE_DIRECTORY "Engine/Vendor/*")

find_package(spdlog REQUIRED)


include_directories(${LIBS_INCLUDE_DIRECTORY})
add_subdirectory(Engine/Vendor/box2d/src)
add_executable(${EXECUTABLE} ${SOURCES})
set_target_properties(${EXECUTABLE} PROPERTIES CXX_STANDARD ${CXX_STANDARD})
target_link_libraries(${EXECUTABLE} ${LIBRARIES} spdlog::spdlog box2d)
target_include_directories(${EXECUTABLE} PUBLIC ${INCLUDE_DIR})