//
// Created by Robin Anstett on 12/5/23.
//

#ifndef PROJECT_3_VERSION_2_TEXTUREMANAGER_H
#define PROJECT_3_VERSION_2_TEXTUREMANAGER_H
#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
using namespace std;

class TextureManager {
    static unordered_map<string, sf::Texture> textures;
public:
    static sf::Texture& getTexture(string textureName);
};


#endif //PROJECT_3_VERSION_2_TEXTUREMANAGER_H
