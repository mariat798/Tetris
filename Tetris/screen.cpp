//
//  screen.cpp
//  Tetris
//
//  Created by Maria Trotskaya on 2023-07-08.
//

#include "screen.hpp"
#include "game.hpp"

i_screen::i_screen(game * g):
    g(g)
{ }

title_screen::title_screen(game * g):
    i_screen(g)
{ }

void title_screen::draw()
{
    g->display_text("Tetris",((block::WIDTH*g->PIXEL_WIDTH)/2) + g->PIXEL_WIDTH,100,250,100);
    
    auto const rectangle = SDL_Rect{
        ((block::SCREEN_WIDTH/2)*g->PIXEL_WIDTH)-g->PIXEL_WIDTH,
        ((block::SCREEN_HEIGHT/3))*g->PIXEL_WIDTH,
        70,
        34
    };
    
    SDL_SetRenderDrawColor(g->renderer, 0, 100, 198, 0);
    SDL_RenderDrawRect(g->renderer, &rectangle);
    
    g->display_text("START",(block::SCREEN_WIDTH/2)*g->PIXEL_WIDTH - 24,((block::SCREEN_HEIGHT/3))*g->PIXEL_WIDTH + 6,55,25);
    g->reset();
}

void title_screen::handle_input(SDL_Event event)
{
    if (event.type != SDL_MOUSEBUTTONDOWN)
        return;
    
    auto const rectangle = SDL_Rect{
        ((block::SCREEN_WIDTH/2)*g->PIXEL_WIDTH)-g->PIXEL_WIDTH,
        ((block::SCREEN_HEIGHT/3))*g->PIXEL_WIDTH,
        70,
        34
    };
    
    auto const position = SDL_Point {
        event.motion.x,
        event.motion.y
    };
    
    if (SDL_PointInRect(&position, &rectangle))
        g->screen = std::make_unique<game_screen>(g);
}

game_screen::game_screen(game * g):
i_screen(g)
{
    g->reset();
}

void game_screen::draw()
{
    draw_next_box();
    draw_game();
    draw_text();
}

void game_screen::draw_next_box()
{
    SDL_SetRenderDrawColor(g->renderer, 0, 100, 198, 0);
    SDL_RenderDrawLine(g->renderer,24*g->PIXEL_WIDTH,4*g->PIXEL_WIDTH,30*g->PIXEL_WIDTH,4*g->PIXEL_WIDTH);
    SDL_RenderDrawLine(g->renderer,24*g->PIXEL_WIDTH,10.5*g->PIXEL_WIDTH,30*g->PIXEL_WIDTH,10.5*g->PIXEL_WIDTH);
    SDL_RenderDrawLine(g->renderer,24*g->PIXEL_WIDTH,4*g->PIXEL_WIDTH,24*g->PIXEL_WIDTH,10.5*g->PIXEL_WIDTH);
    SDL_RenderDrawLine(g->renderer,30*g->PIXEL_WIDTH,4*g->PIXEL_WIDTH,30*g->PIXEL_WIDTH,10.5*g->PIXEL_WIDTH);
}
void game_screen::draw_game()
{
    for (int i = 4; i < block::HEIGHT; i++) {
        for (int j = 0; j < block::WIDTH; j++) {
            if (j < g->x_width)
                continue;
     
            auto const r = SDL_Rect{
                (j) * g->PIXEL_WIDTH,
                (i) * g->PIXEL_WIDTH,
                g->PIXEL_WIDTH,
                g->PIXEL_WIDTH
            };
            SDL_SetRenderDrawColor(g->renderer, 0, 74, 137, 0);
            SDL_RenderDrawRect( g->renderer, &r );
        }
    }
    
    SDL_SetRenderDrawColor(g->renderer, 0, 100, 198, 0);
    SDL_RenderDrawLine(g->renderer,block::WIDTH*g->PIXEL_WIDTH,4*g->PIXEL_WIDTH,block::WIDTH*g->PIXEL_WIDTH,block::HEIGHT*g->PIXEL_WIDTH);
    SDL_RenderDrawLine(g->renderer,g->x_width*g->PIXEL_WIDTH,4*g->PIXEL_WIDTH,g->x_width*g->PIXEL_WIDTH,block::HEIGHT*g->PIXEL_WIDTH);
    SDL_RenderDrawLine(g->renderer,g->x_width*g->PIXEL_WIDTH,4*g->PIXEL_WIDTH,block::WIDTH*g->PIXEL_WIDTH,4*g->PIXEL_WIDTH);
    g->tetromino.draw(g->renderer);
    g->next.draw_next(g->renderer);
    g->clear_row();
}
void game_screen::draw_text()
{
    auto score_text = "score: " + std::to_string(g->score);
    auto lines_text = "lines: " + std::to_string(g->lines);
    g->display_text(score_text.c_str(),24*g->PIXEL_WIDTH,11.5*g->PIXEL_WIDTH,60,30);
    g->display_text(lines_text.c_str(),24*g->PIXEL_WIDTH,12.5*g->PIXEL_WIDTH,55,30);
    g->display_text("NEXT:",24.5*g->PIXEL_WIDTH,4.5*g->PIXEL_WIDTH,40,30);
    g->display_text("TETRIS",g->x_width*g->PIXEL_WIDTH, 0,375,120);
    g->display_text("BACK",1.5*g->PIXEL_WIDTH,1.3*g->PIXEL_WIDTH,38,25);
    g->draw_board();
}
void game_screen::handle_input(SDL_Event event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        auto const position = SDL_Point{
            event.motion.x,
            event.motion.y
        };
        
        auto const rectangle = SDL_Rect{
            (1) * g->PIXEL_WIDTH,
            (1) * g->PIXEL_WIDTH,
            68,
            34
        };
        
        if (SDL_PointInRect(&position, &rectangle)) {
            
            g->reset();
            g->screen = std::make_unique<title_screen>(g);
            
        }
    }
    
    else if (event.type == SDL_KEYDOWN)
        switch( event.key.keysym.sym )
        {
            case SDLK_LEFT:
                g->move_left();
                break;
            case SDLK_RIGHT:
                g->move_right();
                break;
            case SDLK_UP:
            {
                auto copy = g->tetromino;
                
                copy.rotate();
                if (!g->is_occluded(copy))
                    g->tetromino.rotate();
            }
                break;
            case SDLK_DOWN:
                g->slow_drop();
                break;
                
            case SDLK_SPACE:
                g->drop();
                break;
        }
            
}

end_game_screen::end_game_screen(game * g):
    i_screen(g)
{
    g->reset();
}

void end_game_screen::draw()
{
    SDL_SetRenderDrawColor(g->renderer, 0, 48, 96, 0 );
    g->display_text("GAME OVER",((block::WIDTH*g->PIXEL_WIDTH)/2) + g->PIXEL_WIDTH,100,275,100);
    
    auto const rectangle = SDL_Rect{
        ((block::SCREEN_WIDTH/2)*g->PIXEL_WIDTH)-g->PIXEL_WIDTH,
        ((block::SCREEN_HEIGHT/3))*g->PIXEL_WIDTH,
        70,
        34
    };
    SDL_SetRenderDrawColor(g->renderer, 0, 100, 198, 0);
    SDL_RenderDrawRect(g->renderer, &rectangle);
    g->display_text("EXIT",(block::SCREEN_WIDTH/2)*g->PIXEL_WIDTH - 16,((block::SCREEN_HEIGHT/3))*g->PIXEL_WIDTH + 6,38,25);
}

void end_game_screen::handle_input(SDL_Event event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        auto const position = SDL_Point{
            event.motion.x,
            event.motion.y
        };
        
        auto const rectangle = SDL_Rect{
            ((block::SCREEN_WIDTH/2)*g->PIXEL_WIDTH)-g->PIXEL_WIDTH,
            ((block::SCREEN_HEIGHT/3))*g->PIXEL_WIDTH,
            70,
            34
        };
    
        if (SDL_PointInRect(&position, &rectangle)) {
            
            g->screen = std::make_unique<title_screen>(g);
        }
    }
    
}
