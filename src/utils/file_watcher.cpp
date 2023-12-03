//
// Created by jpabl on 12/2/2023.
//

#include "file_watcher.h"

#include <iostream>

void UpdateListener::handleFileAction(efsw::WatchID watchid, const std::string& dir, const std::string& filename, efsw::Action action, std::string oldFilename) {
    std::string fullPath = dir.substr(0, dir.size() - 1) + "/" + filename;

    switch ( action ) {
        case efsw::Actions::Add:
            std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Added"
                      << std::endl;
        break;
        case efsw::Actions::Delete:
            std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Delete"
                      << std::endl;
        break;
        case efsw::Actions::Modified: {
            auto it = shaderPathToProgramMap.find(fullPath);
            if (it != shaderPathToProgramMap.end()) {
                Shader& foundShaderProgram = it->second.second;
                GLenum shaderType = it->second.first;
                string shaderCode;

                try {
                    ifstream shaderFile;
                    shaderFile.exceptions(ifstream::failbit | ifstream::badbit);

                    shaderFile.open(fullPath.c_str());
                    stringstream shaderStream;
                    shaderStream << shaderFile.rdbuf();
                    shaderFile.close();

                    shaderCode = shaderStream.str();

                    if (!shaderCode.empty()) {
                        shadersToUpdate.push_back({shaderStream.str(), shaderType, foundShaderProgram});
                    }
                } catch (ifstream::failure& e) {
                    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ " << e.what() << std::endl;
                }
            } else {
                std::cout << "Program not found with path: " << fullPath << "\n";
            }
            break;
        }
        case efsw::Actions::Moved:
            std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Moved from ("
                      << oldFilename << ")" << std::endl;
        break;
        default:
            std::cout << "Should never happen!" << std::endl;
    }
}

void UpdateListener::subscribe(Shader&shaderProgram) {
    auto& typesAndPaths = shaderProgram.shaderTypesAndPaths;

    for (auto& typeAndPath : typesAndPaths) {
        shaderPathToProgramMap.insert({typeAndPath.second, {typeAndPath.first, shaderProgram}});
    }
}

void UpdateListener::handleUpdates() {
    for (auto& info : shadersToUpdate) {
        info.shaderProgram.reloadShader(info.shaderCodeBuffer.c_str(), info.shaderType);
    }

    shadersToUpdate.clear();
}
