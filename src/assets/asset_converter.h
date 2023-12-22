//
// Created by jpabl on 12/21/2023.
//

#ifndef ASSET_CONVERTER_H
#define ASSET_CONVERTER_H
#include "asset_file.h"
#include "mesh.h"


class AssetConverter {
public:
    assets::AssetFile convertMeshToBinary(Mesh& mesh);
    Mesh convertBinaryToMesh(const std::string& path);

    assets::AssetFile convertTextureToBinary(Texture& texture);
    Texture convertBinaryToTexture(const std::string& path);
private:
    void unpackMeshData();
};



#endif //ASSET_CONVERTER_H
