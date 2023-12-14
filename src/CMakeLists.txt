add_library(gl_tools
    core/application.cpp

    engine/base_engine.cpp
    engine/gl_engine.cpp

    ui/editor.cpp
    ui/ui.cpp

    utils/functions.cpp
    utils/camera.cpp
    utils/model.cpp
        shader/shader.cpp
    utils/types.cpp
        shader/compute.cpp
    utils/common_primitives.cpp
        shader/update_listener.cpp
        shader/update_listener.h
)

add_executable(demo
    exes/main.cpp)

target_include_directories(gl_tools PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include)

target_include_directories(demo PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include)

# Assimp from vcpkg or other package manager
find_package(assimp CONFIG REQUIRED)
find_package(SDL2 REQUIRED COMPONENTS SDL2)

set(EFSW_LIB "${PROJECT_SOURCE_DIR}/libs/efsw/efsw.lib")

target_link_libraries(gl_tools glad glm stb_image imgui imGuizmo SDL2::SDL2 assimp::assimp ${EFSW_LIB})

target_link_libraries(demo gl_tools)