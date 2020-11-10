//
//  main.cpp
//  SnakeGame
//
//  Created by Michael Rosado on 11/5/20.
//

#include <iostream>
#include <vector>
#include <tuple>
#include <exception>

const std::tuple<int, int> UP {-1,0};
const std::tuple<int, int>DOWN {1,0};
const std::tuple<int, int>LEFT {0,-1};
const std::tuple<int, int> RIGHT {0,1};


class Snake {
    
public:
    std::vector<std::tuple<int, int>> body;
    std::tuple<int, int> direction;
    
    
    Snake(std::tuple<int, int> startDirection) {
        std::tuple<int, int> head {10,5};
        std::tuple<int, int> bodyBegin {11,5};
        body.push_back(head);
        body.push_back(bodyBegin);
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
        return body[0];
    }
};

class Apple {
    
};

Snake *snake;
class Game {
public:
    int height = 0;
    int width = 0;
    Game(int height, int width) {
        this->height = height;
        this->width = width;
        
    }
    
    std::vector<std::vector<char>> board_Layout() {
      
        std::vector<std::vector<char>> board_matrix(width, std::vector<char>(height, ' '));
        
        std::tuple<int, int> headPosition = snake->head();
        
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
        std::vector<std::vector<char>> gameBoard = this->board_Layout();
        for (int i = 0; i < gameBoard.size(); i++) {
            for (int j = 0; j < gameBoard[i].size(); j++) {
                std::cout<<gameBoard[i][j];
            }
            std::cout<<std::endl;
        }
        
    }
};

Game *game;

void startGame() {
    game = new Game(20,20);
    snake = new Snake(UP);
    game->render();
}

std::tuple<int, int> getUserInput() {
    char input;
    std::cin>>input;
    if (sizeof(input) > 1) {
        std::string error = "input too long";
        std::cout<<"Only 1 letter at a time\n";
        getUserInput();
    } else {
        switch (input) {
            case 'w':
                return UP;
                break;
                
            case 'a':
                return LEFT;
                break;
            case 's':
                return DOWN;
                break;
            case 'd':
                return RIGHT;
                break;
            default:
                return getUserInput();
                
        }
    }
}

void updateSnake(std::tuple<int, int> input) {
    snake->direction = input;
    int x = get<0>(input);
    int y = get<1>(input);
    
    int stepX = get<0>(snake->body[0]) + x;
    int stepY = get<1>(snake->body[1]) +y;
    
    //std::tuple<int, int> nextStep {{get<0>(snake->body[0]) += x,get<1>(snake->body[0]) += y}};
    
    std::tuple<int, int> nextStep {stepX, stepY};
    snake->take_step(nextStep);
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
