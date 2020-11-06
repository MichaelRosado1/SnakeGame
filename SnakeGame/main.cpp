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
    int height = 1;
    int width = 1;
    
    Game(int height, int width) {
        this->height = height;
        this->width = width;
        
    }
    
    void board_Layout() {
      
        char board_matrix[height][width];
        
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
               //TODO: fill in game board with spaces or '+','|', or '-' characters
            }
        }
        
        
        
        
        
    }
    
    void render() {
        std::cout<<"Height is: "<<height<<std::endl;
        std::cout<<"width is: "<<width<<std::endl;
    }
};

int main() {
    
    Game* game = new Game(10,20);
    game->board_Layout();
    
}
