#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>
#include "Tile.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <random>
using namespace std;

void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void setName(sf::Text &userType, string &username, char letter, int &numCols, int &numRows){
    if(username.length() <= 10){
        if(username.length() == 1){
            username = toupper(letter);
        } else{
            username = username.substr(0, username.length()-1);
            username += tolower(letter);
        }
        username += "|";
        userType.setString(username);
        setText(userType, numCols*16, (numRows*32+100)/2-45);
    }

}

void createLeader(int &numCols, int &numRows, sf::Font &font){
    sf::RenderWindow lbWindow(sf::VideoMode(numCols*16, numRows*16+100), "Minesweeper", sf::Style::Close);

    sf::Text leaderTitle;
    leaderTitle.setFont(font);
    leaderTitle.setString("LEADERBOARD");
    leaderTitle.setCharacterSize(20); // in pixels, not points!
    leaderTitle.setFillColor(sf::Color::White);
    leaderTitle.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(leaderTitle, numCols*8, (numRows*16+100)/2-120);

    string leaderText = "";
    int count = 1;
    ifstream file("leaderboard.txt");
    if(file.is_open()){
        string entry;
        while(!file.eof()){
            stringstream ss;
            ss << count;
            leaderText += ss.str() + ".\t";

            getline(file, entry);
            leaderText += entry.substr(0, entry.find(",")) + "\t";

            entry = entry.substr(entry.find(",")+1);
            leaderText += entry.substr(0, entry.find(",")) + "\n\n";
            count++;
        }
        file.close();
    }

    sf::Text leaders;
    leaders.setFont(font);
    leaders.setString(leaderText);
    leaders.setCharacterSize(18); // in pixels, not points!
    leaders.setFillColor(sf::Color::White);
    leaders.setStyle(sf::Text::Bold);
    setText(leaders, numCols*8, (numRows*16+100)/2+20);

    while(lbWindow.isOpen()){
        sf::Event lbEvent;
        while (lbWindow.pollEvent(lbEvent)){
            if (lbEvent.type == sf::Event::Closed)
                lbWindow.close();
        }
        lbWindow.clear(sf::Color::Blue);
        lbWindow.draw(leaderTitle);
        lbWindow.draw(leaders);
        lbWindow.display();
    }
}

void createBoard(int &numCols, int &numRows, int &numMines, vector<vector<Tile>> &board){
    random_device rd;
    mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 1);
    int count = 0;

    for(int i = 0; i < numRows; i++){
        vector<Tile> bRow;
        for(int j = 0; j < numCols; j++){
            Tile temp;
            int random_number = distribution(gen);
            if(random_number == 1 && count < numMines){
                count++;
                temp.setMine(true);
            }
            temp.position(i*32,j*32);
            bRow.push_back(temp);
        }
        board.push_back(bRow);
    }
}

void updateLeader(){
    //update after game win
}

int main() {
    int numCols;
    int numRows;
    int numMines;
    ifstream in_file("config.cfg");
    if (in_file.is_open()) {
        string entry;
        getline(in_file, entry);
        numCols = stoi(entry);
        getline(in_file, entry);
        numRows = stoi(entry);
        getline(in_file, entry);
        numMines = stoi(entry);
    } else{
        numCols = 0;
        numRows = 0;
        numMines = 0;
    }

    sf::RenderWindow window(sf::VideoMode(numCols * 32, numRows * 32 + 100), "Minesweeper", sf::Style::Close);
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        cout << "error" << endl;
    }
    sf::Text welcome;
    welcome.setFont(font);
    welcome.setString("WELCOME TO MINESWEEPER!");
    welcome.setCharacterSize(24); // in pixels, not points!
    welcome.setFillColor(sf::Color::White);
    welcome.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(welcome, numCols * 16, (numRows * 32 + 100) / 2 - 150);

    sf::Text enterName;
    enterName.setFont(font);
    enterName.setString("Enter your name:");
    enterName.setCharacterSize(20); // in pixels, not points!
    enterName.setFillColor(sf::Color::White);
    setText(enterName, numCols * 16, (numRows * 32 + 100) / 2 - 75);

    sf::Text userType;
    string username = "|";
    userType.setString(username);
    userType.setFont(font);
    userType.setCharacterSize(18); // in pixels, not points!
    userType.setFillColor(sf::Color::Yellow);
    setText(userType, numCols * 16, (numRows * 32 + 100) / 2 - 45);

    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    setName(userType, username, 'A', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
                    setName(userType, username, 'B', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
                    setName(userType, username, 'C', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    setName(userType, username, 'D', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                    setName(userType, username, 'E', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                    setName(userType, username, 'F', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                    setName(userType, username, 'G', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
                    setName(userType, username, 'H', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                    setName(userType, username, 'I', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
                    setName(userType, username, 'J', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
                    setName(userType, username, 'K', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                    setName(userType, username, 'L', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
                    setName(userType, username, 'M', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
                    setName(userType, username, 'N', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
                    setName(userType, username, 'O', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                    setName(userType, username, 'P', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                    setName(userType, username, 'Q', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                    setName(userType, username, 'R', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    setName(userType, username, 'S', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
                    setName(userType, username, 'T', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
                    setName(userType, username, 'U', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
                    setName(userType, username, 'V', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    setName(userType, username, 'W', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
                    setName(userType, username, 'X', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
                    setName(userType, username, 'Y', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                    setName(userType, username, 'Z', numCols, numRows);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                    if (username.length() == 1 || username.length() == 2) {
                        username = "";
                    }
                    if (username.length() > 2) {
                        username = username.substr(0, username.length() - 2);
                    }
                    username += "|";
                    userType.setString(username);
                    setText(userType, numCols * 16, (numRows * 32 + 100) / 2 - 45);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    if (username.length() > 1) {
                        window.close();
                    }
                }

            }
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }

        }
        window.clear(sf::Color::Blue);

        window.draw(welcome);
        window.draw(enterName);
        window.draw(userType);

        window.display();
    }

    sf::RenderWindow gameWindow(sf::VideoMode(numCols * 32, numRows * 32 + 100), "Minesweeper", sf::Style::Close);

    //button sprite setup
    sf::Sprite happyFace;
    happyFace.setTexture(TextureManager::getTexture("face_happy"));
    happyFace.setPosition((numCols / 2.0) * 32 - 32, 32 * (numRows + 0.5));

    sf::Sprite winFace;
    winFace.setTexture(TextureManager::getTexture("face_win"));
    winFace.setPosition((numCols / 2.0) * 32 - 32, 32 * (numRows + 0.5));

    sf::Sprite loseFace;
    loseFace.setTexture(TextureManager::getTexture("face_lose"));
    loseFace.setPosition((numCols / 2.0) * 32 - 32, 32 * (numRows + 0.5));

    sf::Sprite debug;
    debug.setTexture(TextureManager::getTexture("debug"));
    debug.setPosition((numCols) * 32 - 304, 32 * (numRows + 0.5));

    sf::Sprite pause;
    pause.setTexture(TextureManager::getTexture("pause"));
    pause.setPosition((numCols) * 32 - 240, 32 * (numRows + 0.5));

    sf::Sprite play;
    play.setTexture(TextureManager::getTexture("play"));
    play.setPosition((numCols) * 32 - 240, 32 * (numRows + 0.5));

    sf::Sprite leaderboard;
    leaderboard.setTexture(TextureManager::getTexture("leaderboard"));
    leaderboard.setPosition((numCols) * 32 - 176, 32 * (numRows + 0.5));

    sf::FloatRect lb = leaderboard.getGlobalBounds();
    sf::FloatRect face = happyFace.getGlobalBounds();
    sf::FloatRect play_pause = pause.getGlobalBounds();
    sf::FloatRect db = debug.getGlobalBounds();

    //game control setup
    bool gameOver = false;
    bool gameWon = false;
    bool gamePaused = false;
    vector<vector<Tile>> board;
    createBoard(numCols, numRows, numMines, board);

    while (gameWindow.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event gameEvent;
        while (gameWindow.pollEvent(gameEvent)) {
            if (gameEvent.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mPos = sf::Mouse::getPosition(gameWindow);
                if (lb.contains(mPos.x, mPos.y)) {
                    createLeader(numCols, numRows, font);
                }
                if (face.contains(mPos.x, mPos.y)) {
                    cout << "reset" << endl;
                }
                if (play_pause.contains(mPos.x, mPos.y)) {
                    gamePaused = !gamePaused;
                }
                if (db.contains(mPos.x, mPos.y)) {
                    cout << "toggle mine visibility" << endl;
                }
            }
            if (gameEvent.type == sf::Event::Closed)
                gameWindow.close();
        }
        gameWindow.clear(sf::Color::White);
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[0].size(); j++){
                gameWindow.draw(board[i][j].getSprite());
            }
        }
        gameWindow.draw(board[0][0].getSprite());
        gameWindow.draw(board[1][0].getSprite());
        gameWindow.draw(board[2][2].getSprite());
        gameWindow.draw(debug);
        gameWindow.draw(leaderboard);
        if (!gameOver) {
            gameWindow.draw(happyFace);
        } else {
            if (gameWon) {
                gameWindow.draw(winFace);
            } else {
                gameWindow.draw(loseFace);
            }
        }
        if (!gamePaused) {
            gameWindow.draw(pause);
        } else {
            gameWindow.draw(play);
        }
        gameWindow.display();

    }
    return 0;
}
