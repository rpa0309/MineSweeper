//
// Created by Robin Anstett on 12/5/23.
//

#include "TextureManager.h"
#include <unordered_map>
#include <SFML/Graphics.hpp>
using namespace std;

unordered_map<string, sf::Texture> TextureManager::textures;

sf::Texture& TextureManager::getTexture(string textureName){
    auto result = textures.find(textureName);
    if(result == textures.end()){
        sf::Texture newTexture;
        newTexture.loadFromFile("images/" + textureName + ".png");
        textures[textureName] = newTexture;
        return textures[textureName];
    } else{
        return result -> second;
    }
}