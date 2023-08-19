//
//  block.hpp
//  Tetris
//
//  Created by Maria Trotskaya on 2023-05-14.
//

#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>


/* block_hpp */

class block
{
public:
    
    enum SHAPES {
        BLOCK_NONE,
        BLOCK_L,
        BLOCK_S,
        BLOCK_Z,
        BLOCK_T,
        BLOCK_I,
        BLOCK_J,
        BLOCK_O,
        BLOCK_MAX
    };
    
    static constexpr std::array<std::uint32_t, 4> block_colors[BLOCK_MAX] {
        {},
        {0, 240, 240, 0},
        {0, 0, 240, 0},
        {240, 160, 0, 0},
        {250, 250, 0, 0},
        {0, 240, 0, 0},
        {160, 0, 240, 0},
        {240, 0, 0, 0}
    };
    
    constexpr static auto SIZE = 4;
    constexpr static auto LENGTH = 30; // pixels
    constexpr static auto BORDER = 1; // pixels
    constexpr static auto PIXEL_WIDTH = 32;
    constexpr static int shapes_arr[BLOCK_MAX][SIZE][SIZE]
    {
        {},
        {{1,0,0,0},
         {1,0,0,0},
         {1,1,0,0},
         {0,0,0,0}},
        
        {{0,1,1,0},
         {1,1,0,0},
         {0,0,0,0},
         {0,0,0,0}},
        
        {{1,1,0,0},
         {0,1,1,0},
         {0,0,0,0},
         {0,0,0,0}},
        
        {{1,1,1,0},
         {0,1,0,0},
         {0,0,0,0},
         {0,0,0,0}},
        
        {{0,1,0,0},
         {0,1,0,0},
         {0,1,0,0},
         {0,1,0,0}},
        
        {{0,1,0,0},
         {0,1,0,0},
         {1,1,0,0},
         {0,0,0,0}},
        
        {{0,0,0,0},
         {0,1,1,0},
         {0,1,1,0},
         {0,0,0,0}}
    };
    constexpr static auto WIDTH = 22;
    constexpr static auto HEIGHT = 24;
    
    constexpr static auto SCREEN_WIDTH = 32;
    constexpr static auto SCREEN_HEIGHT = 24;
protected:
    
    int x;
    int y;
    int x_previous;
    int y_previous;
    std::array<std::array<int, SIZE>, SIZE> current_block;
    SHAPES shape_type;
    
public:
    
    block() = default;
    block(SHAPES type);
    
    void draw(SDL_Renderer* renderer);
    void draw_next(SDL_Renderer* renderer);
    void move(int x, int y);
    void rotate();
  
    int x_coordinate();
    int y_coordinate();
    
    friend class game;
};

