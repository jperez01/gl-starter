add_library(gl_tools STATIC
    core/application.cpp

    renderer/base_renderer.cpp
    renderer/gl_renderer.cpp

    ui/editor.cpp
    ui/ui.cpp

    utils/functions.cpp
    utils/camera.cpp
    utils/types.cpp
    utils/common_primitives.cpp

    assets/model.cpp

    shader/shader.cpp
    shader/update_listener.cpp
        renderer/base_renderer.h
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
set(EFSW_LIB "${PROJECT_SOURCE_DIR}/libs/efsw/efsw.lib")

target_link_libraries(gl_tools PUBLIC glad glm stb_image imgui imGuizmo SDL2::SDL2 assimp::assimp ${EFSW_LIB})

target_link_libraries(demo PUBLIC gl_tools)