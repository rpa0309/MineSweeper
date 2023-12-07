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
    sf::Sprite sprite1;
    sf::Sprite sprite2;



    Tile(){
        mine = false;
        minesNext = 0;
        revealed = false;
        flagged = false;
        sprite1.setTexture(TextureManager::getTexture("tile_hidden"));
    }

    void setMine(bool a){
        mine = a;
    }

    void setMinesNext(int a){
        minesNext = a;
    }

    void position(float x, float y){
        sprite1.setPosition(x, y);
        sprite2.setPosition(x, y);
    }

    void flag(bool a){
        flagged = a;
        if(flagged){
            sprite2.setTexture(TextureManager::getTexture("flag"));
        } else{
            sprite2.setTexture(TextureManager::getTexture("tile_hidden"));
        }
    }

    bool reveal(bool a){
        revealed = a;
        if(revealed){
            if(mine){
                sprite1.setTexture(TextureManager::getTexture("tile_revealed"));
                sprite2.setTexture(TextureManager::getTexture("mine"));
                return true;
            } else{
                sprite1.setTexture(TextureManager::getTexture("tile_revealed"));
                if(minesNext == 1){
                    sprite2.setTexture(TextureManager::getTexture("number_1"));
                }
                if(minesNext == 2){
                    sprite2.setTexture(TextureManager::getTexture("number_2"));
                }
                if(minesNext == 3){
                    sprite2.setTexture(TextureManager::getTexture("number_3"));
                }
                if(minesNext == 4){
                    sprite2.setTexture(TextureManager::getTexture("number_4"));
                }
                if(minesNext == 5){
                    sprite2.setTexture(TextureManager::getTexture("number_5"));
                }
                if(minesNext == 6){
                    sprite2.setTexture(TextureManager::getTexture("number_6"));
                }
                if(minesNext == 7){
                    sprite2.setTexture(TextureManager::getTexture("number_7"));
                }
                if(minesNext == 8){
                    sprite2.setTexture(TextureManager::getTexture("number_8"));
                }
                return false;
            }
        } else{
            sprite1.setTexture(TextureManager::getTexture("tile_hidden"));
            sprite2.setTexture(TextureManager::getTexture("tile_hidden"));
            return false;
        }

    }

    sf::Sprite getSprite1(){
        return sprite1;
    }

    sf::Sprite getSprite2(){
        return sprite2;
    }



};


#endif //PROJECT_3_VERSION_2_TILE_H
