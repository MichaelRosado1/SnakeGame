//
//  main.cpp
//  SnakeGame
//
//  Created by Michael Rosado on 11/5/20.
//

#include <iostream>
#include <vector>

class Snake {
    
};

class Apple {
    
};

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
        
    
        for (int i = 0; i < board_matrix.size(); i++) {
            for (int j = 0; j < board_matrix[i].size(); j++) {
                /*
               (0,0)       (0, width - 1)
                 +---------+
                 |         |
                 |         |
                 +---------+
                 
                 */
                if (i == 0 || i == board_matrix.size() - 1) {
                    board_matrix[i][j] = '*';
                } else if (i != 0 && (j == 0 || j == board_matrix[i].size() - 1)) {
                    board_matrix[i][j] = '*';
                }
                
            }
        }
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
