//
//  main.cpp
//  SnakeGame
//
//  Created by Michael Rosado on 11/5/20.
//

#include <iostream>
#include <vector>
#include <tuple>

const std::tuple<int, int> UP {1,0};
const std::tuple<int, int>DOWN {0,-1};
const std::tuple<int, int>LEFT {-1,0};
const std::tuple<int, int> RIGHT {1,0};

class Snake {
    
public:
    std::vector<std::tuple<int, int>> body;
    std::tuple<int, int> direction;
    
    
    Snake(std::vector<std::tuple<int, int>> bodyPos, std::tuple<int, int> startDirection) {
        this->body = bodyPos;
        this->direction = startDirection;
    }
    
    void take_step(std::tuple<int, int> position) {
        body.insert(body.begin(), position);
        body.pop_back();
    }
    void set_direction(std::tuple<int, int> direction) {
        this->direction = direction;
    }
    
    std::tuple<int,int> head() {
        return this->body.at(0);
    }
    
};

class Apple {
    
};

class Game {
public:
    int height = 0;
    int width = 0;
    Snake *snake;
    Game(int height, int width) {
        this->height = height;
        this->width = width;
        std::vector<std::tuple<int,int>> startingSnake{};
        snake = new Snake(startingSnake, UP);
        
    }
    
        std::vector<std::vector<char>> board_Layout() {
      
        std::vector<std::vector<char>> board_matrix(width, std::vector<char>(height, ' '));
        
        std::tuple<int,int> headPosition = snake->head();
        
        std::vector<std::tuple<int, int>> bodyPositions = snake->body;
    
        for (int i = 0; i < board_matrix.size(); i++) {
            for (int j = 0; j < board_matrix[i].size(); j++) {
                if (i == 0 || i == board_matrix.size() - 1) {
                    board_matrix[i][j] = '*';
                } else if (i != 0 && (j == 0 || j == board_matrix[i].size() - 1)) {
                    board_matrix[i][j] = '*';
                }
                
            }
        }
            for (int i = 0; i <bodyPositions.size(); i++) {
                board_matrix[get<0>(bodyPositions[i])][get<1>(bodyPositions[i])] = 'O';
            }
            board_matrix[get<0>(headPosition)][get<1>(headPosition)] = 'X';
        
    return board_matrix;
        
    }
    
    void render() {
        std::vector<std::vector<char>> gameBoard = Game::board_Layout();
        for (int i = 0; i < gameBoard.size(); i++) {
            for (int j = 0; j < gameBoard[i].size(); j++) {
                std::cout<<gameBoard[i][j];
            }
            std::cout<<std::endl;
        }
        
    }
};

int main() {
    
    Game* game = new Game(20,20);
    game->render();
    
}
