# GL Starter
Starter code for OpenGL projects in C++. I constantly had small demos that I wanted to make, but I wanted a framework to work off of instead of starting from scratch.

![Windows Workflow](https://github.com/jperez01/gl-starter/tree/main/.github/workflows/windows.yaml/badge.svg)

## Features
* Abstractions for basic graphics primitives like texture, framebuffer, mesh, etc.
* Guizmo tool for transforming objects in a scene.
* Shader hot reload.
* Asset loading from compressed files.

## Getting Started

### Prerequisites
This project uses [Cmake](https://cmake.org/) as the build system. It also uses the following external libraries:
* [Assimp](https://github.com/assimp/assimp) - Asset Importer
* SDL2 - Window Management
* [LZ4](https://github.com/lz4/lz4) - Compression and Decompression
* [EFSW](https://github.com/SpartanJ/efsw) - File Watcher Library (for shader hot reload)
* [Nlohmann's Json Library](https://github.com/nlohmann/json) - JSON library for C++

Some libraries are in the third_party folder and built along with the app:
* [GLM](http://www.dropwizard.io/1.0.2/docs/) - Math Library
* [GLAD](https://github.com/Dav1dde/glad) - OpenGL function linker
* [ImGui](https://github.com/ocornut/imgui) - editor UI
* [ImGuizmo](https://github.com/CedricGuillemet/ImGuizmo) - Guizmo extension to ImGui

To get the necessary libraries, I recommend using [vcpkg](https://vcpkg.io/en/):
#### Windows
```
git clone https://github.com/microsoft/vcpkg
./vcpkg/bootstrap-vcpkg.bat
vcpkg install efsw
vcpkg install lz4
vcpkg install assimp
vcpkg install sdl2
vcpkg integrate install (used for Visual Studio)
```
#### Linux
```
git clone https://github.com/microsoft/vcpkg
./vcpkg/bootstrap-vcpkg.sh
./vcpkg/vcpkg install efsw
./vcpkg/vcpkg install lz4
./vcpkg/vcpkg install assimp
./vcpkg/vcpkg install sdl2
```
I ran into trouble long ago where the assimp library in vcpkg had a dependency that wouldn't work, so I had to install it from the linux package manager:
```
sudo apt update
sudo apt-get update
sudo apt-get install libassimp-dev
```

### Build
When building, you need to tell cmake to use vcpkg by passing in an environment variable that shows where vcpkg is installed:
#### Windows
```
-DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
```
#### Linux
```
-DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
```
The place where you installed vcpkg may be different, so change accordingly. This is just a default value.
Once this is done, it should build and compile in whatever IDE you use.

## Acknowledgments

* [LearnOpenGL](https://learnopengl.com/)
* [Real Time Rendering](https://www.realtimerendering.com/)
