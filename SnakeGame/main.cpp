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
    
    
    Snake(std::tuple<int, int> startDirection) {
        std::vector<std::tuple<int, int>> initialPosition;
        std::tuple<int, int> begin {5,0};
        initialPosition.push_back(begin);
        this->body =initialPosition;
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
//        return body.front();
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

Game *game;
Snake *snake;

void startGame() {
    game = new Game(20,20);
    snake = new Snake(UP);
    game->render();
}

std::tuple<int, int> getUserInput() {
    char input;
    std::cin>>input;
    if (input == 'w') {
        return UP;
    } else if (input == 'a') {
        return LEFT;
    } else if (input == 's') {
        return DOWN;
    } else if (input == 'd') {
        return RIGHT;
    } else {
        std::cout<<"enter in terms of wasd\n";
        return getUserInput();
    }
    
}
void updateSnake(std::tuple<int, int> input) {
    
}
int main() {
/*
 startGame();
 while (gameNotOver) {
    getInput()
    updateGame();
    updateScore();
 */
    bool gameNotOver = true;
    startGame();
    while(gameNotOver) {
        std::tuple<int, int> input = getUserInput();
        updateSnake(input);
        game->render();
    }
    
    
    
    //getInput()
    //updateGame()
    
    
}
