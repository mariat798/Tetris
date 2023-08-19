//
//  game.cpp
//  Tetris
//
//  Created by Maria Trotskaya on 2023-05-09.
//
#include "block.hpp"
#include "game.hpp"
#include "utils.hpp"
#include <SDL2_ttf/SDL_ttf.h>

void game::reset()
{
    for ( int i = 0;i<HEIGHT;i++){
        for (int j=0;j<WIDTH;j++){
            game_board[i][j] = block::BLOCK_NONE;
        }
    }
    new_block();
    next_block();
    
}

void game::drop()
{
    while(!obstructed_down())
        tetromino.move(0,1);
    
    cement_block();
    score += 5;
}

bool game::full_board()
{
    int y = 4;
    for (int x = 0;x<WIDTH-1;x++){
        if(game_board[y][x]!=block::BLOCK_NONE){
            return true;
        }
    }
    return false;
}

void game::shift_down(auto start_y)
{
    for (int y = start_y; y>=0;y--){
        for (int x = 0; x<WIDTH-1;x++){
            game_board[y+1][x]=game_board[y][x];
        }
    }
    
}

void game::clear_row()
{
    for (int y = HEIGHT-1;y>=0;y--){
        
        bool row_filled = true;
        
        for (int x = WIDTH-1; x>=x_width;x--){
            
            if (game_board[y][x] == block::BLOCK_NONE)
                row_filled = false;
        }
        if (row_filled){
            for (int x = WIDTH-1; x>=0;x--){
                game_board[y][x] = block::BLOCK_NONE;

            }
            SDL_Delay(500);
            shift_down(y-1);
            score += 100;
            lines += 1;
        }
    }
}

bool game::obstructed_left()
{
    for (int i=0; i< block::SIZE; i++){
        for (int j=0; j< block::SIZE; j++) {
            if (tetromino.current_block[j][i] == 0)
                continue;

            if (tetromino.x + i == x_width)
                return true;
            
            if (game_board[tetromino.y+j][tetromino.x+i-1] != block::BLOCK_NONE)
                return true;
            
        }
    }
    return false;
}

bool game::is_occluded(block & b)
{
    for (int i=0; i< block::SIZE; i++){
        for (int j=0; j< block::SIZE; j++) {
            if (b.current_block[j][i] == 0)
                continue;
            
            if (b.x + i> WIDTH-1)
                return true;
            
            if (b.y + j > HEIGHT-1)
                return true;
            
            if (game_board[b.y+j][b.x+i] != block::BLOCK_NONE)
                return true;
            
            if (b.x + i < x_width)
                return true;
            
            if (b.y + j <0)
                return true;
            
        }
    }
    
    return false;
}
    
void game::move_left()
{
    if (obstructed_left())
        return;

    tetromino.move(-1,0);
}

bool game::obstructed_right()
{
    for (int i=0; i< block::SIZE; i++){
        for (int j=0; j< block::SIZE; j++) {
            if (tetromino.current_block[j][i] == 0)
                continue;
            
            if (tetromino.x + i == WIDTH - 1)
                return true;
            
            if (game_board[tetromino.y+j][tetromino.x+i+1] != block::BLOCK_NONE)
                return true;
            
        }
    }
    return false;
}

void game::move_right()
{
    if (obstructed_right())
        return;
    tetromino.move(1,0);
}

void game::move_down()
{
    if (SDL_GetTicks() > move_time ) {
        move_time += 800;
        tetromino.move(0,1);
    }
    
}

void game::slow_drop()
{
    if (SDL_GetTicks() > drop_move_time && !obstructed_down()){
        drop_move_time += 5;
        tetromino.move(0,1);
        
        if (obstructed_down())
            cement_block();
    }
    score += 2;
    
}
void game::draw_board()
{
    for ( int i = 0;i<HEIGHT;i++){
        for (int j=0;j<WIDTH;j++){
            if (game_board[i][j] != block::BLOCK_NONE)
            {

                auto && shape_type = game_board[i][j];
                
                SDL_SetRenderDrawColor(renderer,
                                       block::block_colors[shape_type][0],
                                       block::block_colors[shape_type][1],
                                       block::block_colors[shape_type][2],
                                       block::block_colors[shape_type][3]);
         
                SDL_Rect r;
                r.x = (j) * PIXEL_WIDTH;
                r.y = (i) * PIXEL_WIDTH;
                r.w = 30;
                r.h = 30;
                SDL_RenderFillRect( renderer, &r );
            }
        }
    }
}
 
void game::new_block()
{
    tetromino = block(block::SHAPES(utils::random(block::BLOCK_NONE + 1, block::BLOCK_MAX - 1)));
}

void game::next_block()
{
    next = block(block::SHAPES(utils::random(block::BLOCK_NONE + 1, block::BLOCK_MAX - 1)));
}

bool game::obstructed_down()
{
    for (int i=0; i< block::SIZE; i++)
        for (int j=0; j< block::SIZE; j++) {
            
            if (tetromino.current_block[j][i] == 0)
                continue;
            
            if (tetromino.y + j == HEIGHT - 1)
                return true;
            
            if (game_board[tetromino.y+j+1][tetromino.x+i] != block::BLOCK_NONE)
                return true;
        }
    
    return false;
}

void game::cement_block()
{
    for (int i=0; i< block::SIZE; i++){
        for (int j=0; j< block::SIZE; j++){
            
            if (tetromino.current_block[j][i] == 0)
                continue;
            
            game_board[tetromino.y+j][tetromino.x+i] = tetromino.shape_type;
        }
    }
}

void game::display_text(const char *text, int x, int y, int width, int height)
{
    TTF_Init();
    static TTF_Font *font = nullptr;

    if (font == nullptr)
    {
        font = TTF_OpenFont("/Users/mariatrotskaya/Tetris/Tetris/bebas-neue/BebasNeue-Regular.ttf", 36);
        
        if (nullptr == font)
            throw std::runtime_error(std::string("game::display_text: ") + TTF_GetError());
    }
        
    auto const white = SDL_Color {255, 255, 255};
    
    SDL_Surface *surface_message = TTF_RenderText_Solid(font, text, white);
    
    SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surface_message);
    
    auto const rect_message = SDL_Rect{
        x,
        y,
        width,
        height
    };
    
    SDL_FreeSurface(surface_message);
    SDL_RenderCopy(renderer, message, NULL, &rect_message);
    SDL_DestroyTexture(message);
}

game::game()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        std::cerr << "Error" << std::endl;
    
    window = SDL_CreateWindow(
            "Tetris",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH * (block::LENGTH + block::BORDER * 2),
            SCREEN_HEIGHT * (block::LENGTH + block::BORDER * 2),
            SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS
    );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    move_time = SDL_GetTicks();
    drop_move_time = SDL_GetTicks();
    screen = std::make_unique<title_screen>(this);
    
    new_block();
    next_block();
}

game::~game()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    TTF_Quit();
    SDL_Quit();
}

void game::handle_events(SDL_Event &event, bool &quit)
{
    while (SDL_PollEvent(&event)){
        
        if (event.type == SDL_QUIT)
            quit = true;
        
        screen->handle_input(event);
    }

    if (obstructed_down())
    {
        cement_block();
        new_block();
        tetromino = next;
        next_block();
    }
    else
        move_down();
     
    SDL_SetRenderDrawColor(renderer, 0, 48, 96, 0 );
    SDL_RenderClear(renderer);
    
    screen->draw();
    
    if (full_board())
        screen = std::make_unique<end_game_screen>(this);
    
}
bool game::play()
{
    SDL_Event event;
    bool quit = false;

        
    while (!quit)
    {
        handle_events(event, quit);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    return false;
}
