//
//  screen.hpp
//  Tetris
//
//  Created by Maria Trotskaya on 2023-07-08.
//

#pragma once

#include <SDL2/SDL.h>

class game;

class i_screen
{
public:
        
    game * g;
    
    i_screen(game * g);
    virtual ~i_screen() = default;
    
    virtual void draw() = 0;
    virtual void handle_input(SDL_Event event) = 0;
};

class title_screen: public i_screen
{
public:
    
    title_screen(game * g);
    
    void draw() override;
    void handle_input(SDL_Event event) override;
};

class game_screen: public i_screen
{
public:
    
    game_screen(game * g);
    
    void draw() override;
    void handle_input(SDL_Event event) override;
    void draw_next_box();
    void draw_game();
    void draw_text();
};

class end_game_screen: public i_screen
{
public:
    
    end_game_screen(game * g);
    
    void draw() override;
    void handle_input(SDL_Event event) override;
};
