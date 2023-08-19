//
//  block.cpp
//  Tetris
//
//  Created by Maria Trotskaya on 2023-05-14.
//
#include <SDL2/SDL.h>
#include "block.hpp"
#include <iostream>

block::block(SHAPES type) :
    shape_type { type } {
    
    std::memcpy(current_block.data(), shapes_arr[type], sizeof(int)*SIZE*SIZE);
    x = SCREEN_WIDTH / 2;
    y = 4;
    x_previous = WIDTH +((SCREEN_WIDTH - WIDTH) / 2)-1;
    y_previous = 6;
    
}

void block::draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer,
                           block_colors[shape_type][0],
                           block_colors[shape_type][1],
                           block_colors[shape_type][2],
                           block_colors[shape_type][3]);
    
    
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            
            if (current_block[i][j] == 0)
                continue;
            
            SDL_Rect r;
            
            r.x = (x+j) * PIXEL_WIDTH;
            r.y = (y+i) * PIXEL_WIDTH;
            r.w = 30;
            r.h = 30;
            SDL_RenderFillRect( renderer, &r );
        }
    }
}

void block::draw_next(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer,
                           block_colors[shape_type][0],
                           block_colors[shape_type][1],
                           block_colors[shape_type][2],
                           block_colors[shape_type][3]);
    
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            
            if (current_block[i][j] == 0)
                continue;
            
            SDL_Rect r;
            
            r.x = (x_previous+j) * PIXEL_WIDTH;
            r.y = (y_previous+i) * PIXEL_WIDTH;
            r.w = 30;
            r.h = 30;
            SDL_RenderFillRect( renderer, &r );
        }
    }
}

void block::move(int move_x, int move_y)
{
    x += move_x;
    y += move_y;
}

void block::rotate()
{
    std::array<std::array<int, SIZE>, SIZE> copy;
    std::memcpy(copy.data(), current_block.data(), sizeof(int)*SIZE*SIZE);
    
    for (int i = 0 ; i <4; i++)
        for (int j = 0;j<4;j++)
            current_block[i][j] = copy[j][4-i-1]; 
}

int block::x_coordinate()
{
    return x;
}

int block::y_coordinate()
{
    return y;
}
