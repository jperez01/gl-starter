//
// Created by jpabl on 12/26/2023.
//

#ifndef PATHS_H
#define PATHS_H
#include <string>

const std::string SHADER_PATH = "../../shaders/";
const std::string OBJECT_PATH = "../../resources/objects/";
const std::string TEXTURE_PATH = "../../resources/textures/";
const std::string ASSET_PATH = "../../resources/assets/";

inline std::string convertToAssetPath(const std::string& path) {
    return ASSET_PATH + path + ".object";
}

#endif //PATHS_H
