cmake_minimum_required(VERSION 4.0.0)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(First-OpenGL-Project) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# --- GLFW (ZIP DOWNLOAD) ---
FetchContent_Declare(
  glfw
  URL https://github.com/glfw/glfw/archive/refs/tags/3.3.8.zip
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# --- GLM (ZIP DOWNLOAD + VERSION BYPASS) ---
FetchContent_Declare(
  glm
  URL https://github.com/g-truc/glm/archive/refs/tags/0.9.9.8.zip
)

FetchContent_MakeAvailable(glm)

add_executable(${PROJECT_NAME} src/main.cpp)
add_library(GLAD src/glad.c)
target_include_directories(GLAD PUBLIC src/includes)
target_include_directories(${PROJECT_NAME} PRIVATE assets)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    glfw 
    glm::glm
    GLAD
    OpenGL::GL
    ${CMAKE_DL_LIBS} # Required for some Linux builds
)



target_include_directories(${PROJECT_NAME} PUBLIC assets)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})