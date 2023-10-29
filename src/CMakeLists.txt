cmake_minimum_required(VERSION 3.10.0)
project(
    BezierCurve
    VERSION 1.0
    LANGUAGES CXX)

add_subdirectory(glm)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw-3.3.8)
add_subdirectory(glad)

add_executable(BezierCurve 
main.cpp
Grid3D.cpp

CubicBezier.cpp
CubicBezierPatch.cpp

QuadraticBezier.cpp
QuadraticBezierPatch.cpp
)

target_link_libraries(BezierCurve glfw glad)

target_include_directories(BezierCurve PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/glm")
target_include_directories(BezierCurve PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/glad/include")
target_include_directories(BezierCurve PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/glfw-3.3.8/include")