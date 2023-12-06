//
// Created by Robin Anstett on 12/5/23.
//

#ifndef PROJECT_3_VERSION_2_TILE_H
#define PROJECT_3_VERSION_2_TILE_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/BlendMode.hpp>
#include "TextureManager.h"
using namespace std;

class Tile{
public:
    bool mine;
    int minesNext;
    bool revealed;
    bool flagged;
    sf::Texture texture;
    sf::Sprite sprite;



    Tile(){
        mine = false;
        minesNext = 0;
        revealed = false;
        flagged = false;
        sprite.setTexture(TextureManager::getTexture("tile_hidden"));
    }

    void setMine(bool a){
        mine = a;
    }

    void setMinesNext(int a){
        minesNext = a;
    }

    void position(float x, float y){
        sprite.setPosition(x, y);
    }

    void flag(bool a){
        flagged = a;
        if(flagged){
            sprite.setTexture(TextureManager::getTexture("flag"));
        } else{
            sprite.setTexture(TextureManager::getTexture("tile_hidden"));
        }
    }

    bool reveal(bool a){
        revealed = a;
        if(revealed){
            if(mine){
                sprite.setTexture(TextureManager::getTexture("mine"));
                return true;
            } else{
                sprite.setTexture(TextureManager::getTexture("tile_revealed"));
                return false;
            }
        } else{
            sprite.setTexture(TextureManager::getTexture("tile_hidden"));
            return false;
        }

    }

    sf::Sprite getSprite(){
        return sprite;
    }



};


#endif //PROJECT_3_VERSION_2_TILE_H
