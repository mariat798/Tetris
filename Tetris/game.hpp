//
//  game.hpp
//  Tetris
//
//  Created by Maria Trotskaya on 2023-05-09.
//

#pragma once

#include <SDL2/SDL.h>
#include "block.hpp"
#include "screen.hpp"

#include <stdio.h>
#include <thread>
#include <chrono>

class game
{
private:
    
    constexpr static auto WIDTH = 22;
    constexpr static auto HEIGHT = 24;
    
    constexpr static auto SCREEN_WIDTH = 32;
    constexpr static auto SCREEN_HEIGHT = 24;
    constexpr static auto PIXEL_WIDTH = 32;
    const int x_width = 10;
    SDL_Window *window;
    SDL_Renderer* renderer;
    std::unique_ptr<i_screen> screen = nullptr;
    block tetromino;
    block next;
    std::array<std::array<block::SHAPES, WIDTH>, HEIGHT> game_board {};
    
    void reset();
    void new_block();
    void cement_block();
    bool obstructed_down();
    bool is_occluded(block & b);
    bool obstructed_left();
    void move_left();
    bool obstructed_right();
    void move_right();
    void draw_board();
    void clear_row();
    void move_down();
    void shift_down(auto start_y);
    bool full_board();
    void drop();
    void display_text(const char * text, int x, int y, int width, int height);
    void next_block();
    void handle_events(SDL_Event &event, bool &quit);
    void slow_drop();
    block::SHAPES shape_type;
    int score = 0;
    int lines = 0;
    Uint32 move_time;
    Uint32 drop_move_time;
public:
   
    game();
    ~game();
    bool play();
    
    friend class title_screen;
    friend class game_screen;
    friend class end_game_screen;
};
