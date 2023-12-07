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
#include <cmath>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <random>
#include <SFML/System/Clock.hpp>
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

//void checkIfLeader(int &timeRunning, string &username){
//    vector<int> leaders;
//    vector<string> entries;
//    ifstream file("leaderboard.txt");
//    if(file.is_open()) {
//        string entry;
//        while (!file.eof()) {
//            int leaderTime;
//            getline(file, entry);
//            entries.push_back(entry);
//            entry = entry.substr(entry.find(","));
//            leaderTime += stoi(entry.substr(0, entry.find(":"))) * 60;
//            leaderTime += stoi(entry.substr(entry.find(":"), entry.find(",")));
//            entry = entry.substr(entry.find(",") + 1);
//            leaders.push_back(leaderTime);
//        }
//        file.close();
//    }
//    int position = 6;
//    for(int i = 0; i < 5; i++){
//        if(leaders[i] > timeRunning){
//            position = i;
//        }
//    }
//    if(position < 6){
//        string entry = "";
//        int timeMins = timeRunning/60;
//        int timeSecs = timeRunning%60;
//        stringstream ss;
//        ss << timeMins;
//        entry += ss.str() + ":";
//        stringstream ss2;
//        ss2 << timeSecs;
//        entry += ss2.str() + "," + username.substr(0, username.find("|")) + "*";
//        entries.push_back(entry);
////        ofstream file2("leaderboard.txt");
////        if(file2.is_open()) {
////            string entry;
////            for(int i = 0; i < 5; i++){
////                if(i == position){
////                    file2 << entries[entries.size()-1] << endl;
////                } else{
////                    file2 << entries[i] << endl;
////                }
////            }
////            file2.close();
////        }
//
//    }
//}

void updateMinesNext(vector<vector<Tile>> &board){
    for(int i = 0; i < board.size(); i++){
        for(int j = 0; j < board[i].size(); j++){
            int count = 0;
            if(!board[i][j].mine){
                if(i-1>=0 && i+1<board.size() && j-1>=0 && j+1<board[0].size()){
                    if(board[i-1][j-1].mine){
                        count++;
                    }
                    if(board[i][j-1].mine){
                        count++;
                    }
                    if(board[i+1][j-1].mine){
                        count++;
                    }
                    if(board[i-1][j].mine){
                        count++;
                    }
                    if(board[i+1][j].mine){
                        count++;
                    }
                    if(board[i-1][j+1].mine){
                        count++;
                    }
                    if(board[i][j+1].mine){
                        count++;
                    }
                    if(board[i+1][j+1].mine) {
                        count++;
                    }
                }
                if(i == 0 && j-1>=0 && j+1<board[0].size()){
                    if(board[i][j-1].mine){
                        count++;
                    }
                    if(board[i+1][j-1].mine){
                        count++;
                    }
                    if(board[i+1][j].mine){
                        count++;
                    }
                    if(board[i][j+1].mine){
                        count++;
                    }
                    if(board[i+1][j+1].mine) {
                        count++;
                    }
                }
                if(i == board.size()-1 && j-1>=0 && j+1<board[0].size()){
                    if(board[i][j-1].mine){
                        count++;
                    }
                    if(board[i-1][j-1].mine){
                        count++;
                    }
                    if(board[i-1][j].mine){
                        count++;
                    }
                    if(board[i][j+1].mine){
                        count++;
                    }
                    if(board[i-1][j+1].mine) {
                        count++;
                    }
                }
                if(i-1>=0 && i+1<board.size() && j == 0){
                    if(board[i-1][j].mine){
                        count++;
                    }
                    if(board[i+1][j].mine){
                        count++;
                    }
                    if(board[i-1][j+1].mine){
                        count++;
                    }
                    if(board[i][j+1].mine){
                        count++;
                    }
                    if(board[i+1][j+1].mine) {
                        count++;
                    }
                }
                if(i-1>=0 && i+1<board.size() && j == board[0].size()-1){
                    if(board[i-1][j].mine){
                        count++;
                    }
                    if(board[i+1][j].mine){
                        count++;
                    }
                    if(board[i-1][j-1].mine){
                        count++;
                    }
                    if(board[i][j-1].mine){
                        count++;
                    }
                    if(board[i+1][j-1].mine) {
                        count++;
                    }
                }
                if(i==0 && j == 0){
                    if(board[i+1][j].mine){
                        count++;
                    }
                    if(board[i][j+1].mine){
                        count++;
                    }
                    if(board[i+1][j+1].mine) {
                        count++;
                    }
                }
                if(i==0 && j == board[0].size()-1){
                    if(board[i][j-1].mine){
                        count++;
                    }
                    if(board[i+1][j-1].mine){
                        count++;
                    }
                    if(board[i+1][j].mine){
                        count++;
                    }
                }
                if(i == board.size()-1 && j == 0){
                    if(board[i-1][j].mine){
                        count++;
                    }
                    if(board[i-1][j+1].mine){
                        count++;
                    }
                    if(board[i][j+1].mine){
                        count++;
                    }
                }
                if(i == board.size()-1 && j == board[0].size()){
                    if(board[i-1][j-1].mine){
                        count++;
                    }
                    if(board[i][j-1].mine){
                        count++;
                    }

                    if(board[i-1][j].mine){
                        count++;
                    }
                }
                board[i][j].setMinesNext(count);
            }
        }
    }
}

void revealAll(vector<vector<Tile>> &board){
    for(int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            board[i][j].sprite2.setTexture(TextureManager::getTexture("tile_revealed"));
        }
    }
}

vector<vector<Tile>> recoverBoard(vector<vector<Tile>> &board){
    return board;
}

void revealAllMines(vector<vector<Tile>> &board){
    for(int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if(board[i][j].mine){
                bool a = board[i][j].reveal(!board[i][j].revealed);
            }
        }
    }
}

void setMines(vector<vector<Tile>> &board){
    for(int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if(board[i][j].mine){
                bool a = board[i][j].reveal(true);
            }
        }
    }
}

void flagAllMines(vector<vector<Tile>> &board){
    for(int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if(board[i][j].mine){
                board[i][j].flag(true);
            }
        }
    }
}

int numFlags(vector<vector<Tile>> &board){
    int count = 0;
    for(int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if(board[i][j].flagged){
                count++;
            }
        }
    }
    return count;
}

bool isGameOver(vector<vector<Tile>> &board){
    for(int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if(!board[i][j].mine){
                if(board[i][j].revealed == false)
                    return false;
            }
        }
    }
    return true;
}

void revealTiles(vector<vector<Tile>> &board, int i, int j){
    try{
        if(!board[i][j].flagged){
            bool a = board[i][j].reveal(true);
            if(!a && board[i][j].minesNext == 0 && i-1>=0 && i+1<board.size() && j-1>0 && j+1<board[0].size()){
                revealTiles(board, i+1, j);
                revealTiles(board, i, j-1);
            }
        }
    }
    catch(out_of_range){
        cout << "catch" << endl;
    }
}

void createBoard(int &numCols, int &numRows, int &numMines, vector<vector<Tile>> &board){
    if(board.size() != 0){
        board.clear();
    }

    mt19937 gen(time(NULL));
    uniform_int_distribution<int> distribution(0, 10);
    int count = 0;

    for(int i = 0; i < numCols; i++){
        vector<Tile> bRow;
        for(int j = 0; j < numRows; j++){
            Tile temp;
            int random_number = distribution(gen);
            if(random_number == 0 && count < numMines){
                count++;
                temp.setMine(true);
            }
            temp.position(i*32,j*32);
            bRow.push_back(temp);
        }
        board.push_back(bRow);
    }
    while(count < numMines){
        for(int i = 0; i < numCols; i++){
            for(int j = 0; j < numRows; j++){
                int random_number = distribution(gen);
                if(random_number == 0 && count < numMines){
                    count++;
                    board[i][j].setMine(true);
                }
            }
        }
    }

    updateMinesNext(board);
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

    //clock setup
    sf::Clock clock;
    int timeSaved = 0;
    int timeRunning = 0;

    //game control setup
    bool gameOver = false;
    bool gameWon = false;
    bool gamePaused = false;
    bool saveState = false;
    bool leaderboardBo = false;
    int timesPaused = 0;
    vector<vector<Tile>> board;
    vector<vector<Tile>> boardSave;
    createBoard(numCols, numRows, numMines, board);

    while (gameWindow.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event gameEvent;
        while (gameWindow.pollEvent(gameEvent)) {
            if (gameEvent.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mPos = sf::Mouse::getPosition(gameWindow);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    if (lb.contains(mPos.x, mPos.y)) {
                        timeSaved += clock.getElapsedTime().asSeconds() + .5f;
                        if(!gamePaused){
                            boardSave = recoverBoard(board);
                            revealAll(board);
                        }
                        leaderboardBo = true;
                        clock.restart();
                    }
                    if (face.contains(mPos.x, mPos.y)) {
                        createBoard(numCols, numRows, numMines, board);
                        gameOver = false;
                        gameWon = false;
                        gamePaused = false;
                        timeRunning = 0;
                        timeSaved = 0;
                        timesPaused = 0;
                        clock.restart();
                    }
                    if (play_pause.contains(mPos.x, mPos.y) && !gameOver) {
                        gamePaused = !gamePaused;
                        if(gamePaused){
                            timesPaused++;
                            boardSave = recoverBoard(board);
                            revealAll(board);
                            timeSaved += clock.getElapsedTime().asSeconds() + .5f;
                        } else{
                            board = recoverBoard(boardSave);
                            clock.restart();
                        }
                    }
                    if (db.contains(mPos.x, mPos.y)) {
                        revealAllMines(board);
                    }
                    if(mPos.y < 32 * (numRows + 0.5) && !gameOver && !gamePaused){
                        int a = floor(mPos.x/32);
                        int b = floor(mPos.y/32);
                        if(!board[a][b].revealed && !board[a][b].flagged){
                            if(board[a][b].reveal(true)){
                                gameOver=true;
                                gameWon=false;
                            }
                            if(isGameOver(board)){
                                gameOver = true;
                                gameWon = true;
                            }
                            revealTiles(board, a, b);
                        }
                    }
                } else if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && !gameOver && !gamePaused){
                    if(mPos.y < 32 * (numRows + 0.5)){
                        int a = floor(mPos.x/32);
                        int b = floor(mPos.y/32);
                        if(!board[a][b].revealed){
                            board[a][b].flag(!board[a][b].flagged);
                        }
                    }
                }
            }
            if (gameEvent.type == sf::Event::Closed)
                gameWindow.close();
        }
        gameWindow.clear(sf::Color::White);
        for(int i = 0; i < numCols; i++){
            for(int j = 0; j < numRows; j++){
                gameWindow.draw(board[i][j].sprite1);
                gameWindow.draw(board[i][j].sprite2);
            }
        }
        gameWindow.draw(debug);
        gameWindow.draw(leaderboard);
        if (!gameOver) {
            gameWindow.draw(happyFace);
            if (!gamePaused) {
                gameWindow.draw(pause);
                timeRunning = clock.getElapsedTime().asSeconds() + timeSaved;
            } else {
                clock.restart();
                gameWindow.draw(play);
            }
        } else {
            if (!gamePaused) {
                gameWindow.draw(pause);
            } else {
                gameWindow.draw(play);
            }
            if (gameWon) {
                flagAllMines(board);
                gameWindow.draw(winFace);
                boardSave = recoverBoard(board);
                timesPaused++;
                //checkIfLeader(timeRunning, username);
                leaderboardBo = true;
            } else {
                setMines(board);
                gameWindow.draw(loseFace);
            }
        }
        sf::Sprite timerMin1(TextureManager::getTexture("digits"), sf::IntRect(timeRunning/60/10*21, 0,21,32));
        timerMin1.setPosition((numCols) * 32 - 97, 32 * (numRows + 0.5)+16);
        sf::Sprite timerMin2(TextureManager::getTexture("digits"), sf::IntRect(timeRunning/60%10*21, 0,21,32));
        timerMin2.setPosition((numCols) * 32 - 76, 32 * (numRows + 0.5)+16);

        sf::Sprite timerSec1(TextureManager::getTexture("digits"), sf::IntRect(timeRunning%60%10*21, 0,21,32));
        timerSec1.setPosition((numCols) * 32 - 33, 32 * (numRows + 0.5)+16);
        sf::Sprite timerSec2(TextureManager::getTexture("digits"), sf::IntRect(timeRunning%60/10*21, 0,21,32));
        timerSec2.setPosition((numCols) * 32 - 54, 32 * (numRows + 0.5)+16);

        if(numMines-numFlags(board) >= 0){
            sf::Sprite counter1(TextureManager::getTexture("digits"), sf::IntRect((numMines-numFlags(board))/10*21, 0,21,32));
            counter1.setPosition(33, 32 * (numRows + 0.5)+16);
            sf::Sprite counter2(TextureManager::getTexture("digits"), sf::IntRect((numMines-numFlags(board))%10*21, 0,21,32));
            counter2.setPosition(54, 32 * (numRows + 0.5)+16);
            gameWindow.draw(counter1);
            gameWindow.draw(counter2);
        } else{
            sf::Sprite counter1(TextureManager::getTexture("digits"), sf::IntRect(-1*(numMines-numFlags(board))/10*21, 0,21,32));
            counter1.setPosition(33, 32 * (numRows + 0.5)+16);
            sf::Sprite counter2(TextureManager::getTexture("digits"), sf::IntRect(-1*(numMines-numFlags(board))%10*21, 0,21,32));
            counter2.setPosition(54, 32 * (numRows + 0.5)+16);
            sf::Sprite counterNeg(TextureManager::getTexture("digits"), sf::IntRect(10*21, 0,21,32));
            counterNeg.setPosition(12, 32 * (numRows + 0.5)+16);
            gameWindow.draw(counter1);
            gameWindow.draw(counter2);
            gameWindow.draw(counterNeg);
        }


        gameWindow.draw(timerMin1);
        gameWindow.draw(timerMin2);
        gameWindow.draw(timerSec1);
        gameWindow.draw(timerSec2);

        gameWindow.display();
        if(leaderboardBo){
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
                    if (lbEvent.type == sf::Event::Closed){
                        lbWindow.close();
                        leaderboardBo = false;
                        if(timesPaused == 0) {
                            board = recoverBoard(boardSave);
                        }
                    }

                }
                lbWindow.clear(sf::Color::Blue);
                lbWindow.draw(leaderTitle);
                lbWindow.draw(leaders);
                lbWindow.display();
            }
            clock.restart();
        }

    }
    return 0;
}
