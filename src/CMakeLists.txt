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
        assets/mesh.cpp
        assets/mesh.h
        assets/asset_converter.cpp
        assets/asset_converter.h
        assets/asset_file.cpp
        assets/asset_file.h
)

add_executable(demo
    exes/main.cpp)

target_include_directories(gl_tools PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include)

target_include_directories(demo PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include)

# Libraries from vcpkg or other package manager
find_package(assimp CONFIG REQUIRED)
set(EFSW_LIB "${PROJECT_SOURCE_DIR}/libs/efsw/efsw.lib")
find_package(lz4 CONFIG REQUIRED)
find_package(efsw CONFIG REQUIRED)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(gl_tools PUBLIC glad glm stb_image imgui imGuizmo
        SDL2::SDL2 assimp::assimp efsw::efsw nlohmann_json::nlohmann_json lz4::lz4)

target_link_libraries(demo PUBLIC gl_tools)