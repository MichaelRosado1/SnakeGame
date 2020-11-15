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
#include <random>
//Constants for snake movement
const std::tuple<int, int> UP {-1,0};
const std::tuple<int, int>DOWN {1,0};
const std::tuple<int, int>LEFT {0,-1};
const std::tuple<int, int> RIGHT {0,1};
class Snake;
class Apple;
class Game;
//copy of the gameboard to compare position to bounds
std::vector<std::vector<char>> gameBoardCopy;
//bool value to let us know when the game is finished
bool gameNotOver = true;
std::string previousChoice = "w";
bool snakeAteApple = false;
bool gameStart = true;
/*
 Snake class contains:
    constructor
    step/movement function
    which direction the player is moving
    head and body position
 
 */


class Snake {
public:
    //stores the positions of the 'O' char's or body positions
    std::vector<std::tuple<int, int>> body;
    //Helps determine which way the snake should move
    std::tuple<int, int> direction;
    
    
    Snake(std::tuple<int, int> startDirection) {
        std::tuple<int, int> head {10,10};
        std::tuple<int, int> bodyBegin {11,10};
        body.push_back(head);
        body.push_back(bodyBegin);
        this->direction = startDirection;
    }
    void addToBody(std::tuple<int, int> addOn) {
        body.push_back(addOn);
    }
    //checks if next step goes out of bounds, and if not, updates the snake body and head to shift in the direction desired
    void take_step(std::tuple<int, int> position) {
        int xCord = get<0>(position);
        int yCord = get<1>(position);
        if (gameBoardCopy[xCord][yCord] == '*') {
            std::cout<<"game over, you hit a boundry";
            gameNotOver = false;
            return;
        }
        if(gameBoardCopy[xCord][yCord] == '@') {
            snakeAteApple = true;
            std::tuple<int, int> bodyAddOn {get<0>(body[body.size() - 1]) + get<0>(direction),get<1>(body[body.size() - 1]) + get<1>(direction)};
            addToBody(bodyAddOn);
        } else {
            snakeAteApple = false;
        }
            body.insert(body.begin(), position);
            body.pop_back();
    }
    //Lets us know what direction to move
    void set_direction(std::tuple<int, int> direction) {
        this->direction = direction;
    }
    //Helps with bound detection and positioning
    std::tuple<int,int> head() {
        return body[0];
    }
};


//Snake pointer used at the start of the game
Snake *snake;

/*
 game class handles all of the rendering and placing of the snake on the board
    will eventually keep track of score and maybe different game modes
 */
class Apple {
public:
    int xCord;
    int yCord;
    std::vector<std::tuple<int, int>> applePositions;
    Apple() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(2, 18);
        xCord = distr(gen);
        yCord = distr(gen);
        std::tuple<int, int> apple = {xCord, yCord};
        applePositions.push_back(apple);
        this->applePositions.push_back(apple);
    }
    
    void generateNewApple() {
        xCord = 10;
        yCord = 10;
        
    }
    
    void deletePreviousApple() {
        
    }
    int getXcord() {
        return this->xCord;
        
    }
    int getYcord() {
        return this->yCord;
    }
};
Apple *apple = new Apple();
class Game {
public:
    int height = 0;
    int width = 0;
    
    Game(int height, int width) {
        this->height = height;
        this->width = width;
    }
   

    //board layout sets each element of the board, creating bounds for the player
    std::vector<std::vector<char>> board_Layout() {
        
        std::vector<std::vector<char>> board_matrix(width, std::vector<char>(height, ' '));
        
        //creates empty height X width board
//        std::vector<std::vector<char>> board_matrix(width, std::vector<char>(height, ' '));

        //tuple stores the x and y coordinate of the snakes head
        
        //vector of tuples to store all of the x and y values of every 'O' in the snakes body
        
    //loops through board and sets the bounds using '*'
        for (int i = 0; i < board_matrix.size(); i++) {
            for (int j = 0; j < board_matrix[i].size(); j++) {
                if (i == 0 || i == board_matrix.size() - 1) {
                    board_matrix[i][j] = '*';
                } else if (i != 0 && (j == 0 || j == board_matrix[i].size() - 1)) {
                    board_matrix[i][j] = '*';
                }
                
            }
        }
        
        board_matrix[get<0>(apple->applePositions[0])][get<1>(apple->applePositions[0])] = '@';
        
        std::vector<std::vector<char>> &boardRef = board_matrix;
        placeSnakeOnBoard(boardRef);
        gameBoardCopy = board_matrix;
        
        return board_matrix;
        
    }
    void placeSnakeOnBoard(std::vector<std::vector<char>> &board_matrix) {
        std::tuple<int, int> headPosition = snake->head();
        std::vector<std::tuple<int, int>> bodyPositions = snake->body;
        //loops through bodyPositions vector to place the body parts of the snake on the board
        for (int i = 0; i <bodyPositions.size(); i++) {
            board_matrix[get<0>(bodyPositions[i])][get<1>(bodyPositions[i])] = 'O';
        }
        
        //sets the snakes head coordinates(tuple) on the board
        
        
        board_matrix[get<0>(headPosition)][get<1>(headPosition)] = 'X';
        
    }
    //loops through the updated board and prints it to the console
    void render() {
        std::vector<std::vector<char>> gameBoard = board_Layout();
        for (int i = 0; i < gameBoard.size(); i++) {
            for (int j = 0; j < gameBoard[i].size(); j++) {
                std::cout<<gameBoard[i][j];
            }
            std::cout<<std::endl;
        }
        
    }
};
Game *game;



//creates a new game and snake. Also renders board
void startGame() {
    game = new Game(20,20);
    snake = new Snake(UP);
    game->render();
}
//Gets the users input(w,a,s,d for up down left right)
std::tuple<int, int> getUserInput() {
    
    std::string input;
    std::cin>>input;
    
    if (input.size() == 1) {
        //checks if the input is w and the previous choice is NOT w
        //so the player can't turn into themeselves
        if (!input.compare("w") && previousChoice.compare("s")) {
            previousChoice = "w";
            return UP;
        } else if (!input.compare("a") && previousChoice.compare("d") ) {
            previousChoice = "a";
            return LEFT;
        } else if (!input.compare("s") && previousChoice.compare("w")) {
            previousChoice = "s";
            return DOWN;
        } else if (!input.compare("d") && previousChoice.compare("a")) {
            previousChoice = "d";
            return RIGHT;
        }
    }
    std::cout<<"ENTER 1 LETTER Or a different letter\n";
    
    return getUserInput();
    
}
//When there is a step taken, the snakes parts need to be updated to move in the desired direction
void updateSnake(std::tuple<int, int> input) {
    snake->direction = input;
    int x = get<0>(input);
    int y = get<1>(input);
    
    int stepX = get<0>(snake->body[0]) + x;
    int stepY = get<1>(snake->body[0]) +y;
    
    //std::tuple<int, int> nextStep {{get<0>(snake->body[0]) += x,get<1>(snake->body[0]) += y}};
    
    std::tuple<int, int> nextStep {stepX, stepY};
    snake->take_step(nextStep);
}

int main() {
    startGame();
    while(gameNotOver) {
        std::tuple<int, int> input = getUserInput();
        updateSnake(input);
        if (gameNotOver) {
            game->render();
        }
    }
}
