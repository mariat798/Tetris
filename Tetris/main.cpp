//
//  main.cpp
//  Tetris
//
//  Created by Maria Trotskaya on 2023-05-06.
//
//#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "game.hpp"

int main(int argc, const char * argv[]) {
    game Game;
    //while(Game.screen());
    while(Game.play());
    return 0;
}
