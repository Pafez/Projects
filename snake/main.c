#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linkedlist.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 400
#define WIN_LEN 1000

#define CELL_WIDTH 10
#define CELL_HEIGHT 10

#define SNAKE_HEAD_POS_X 80
#define SNAKE_HEAD_POS_Y 40
#define SNAKE_VELOCITY 1

int snake_vel_x = 0, snake_vel_y = 0, score = 0, snake_length = 1;

int SDLRect_IsCollision(SDL_Rect obj1, SDL_Rect obj2);
int Coord_IsCollision(int obj1_top_x, int obj1_top_y, int obj1_bottom_x, int obj1_bottom_y, int obj2_top_x, int obj2_top_y, int obj2_bottom_x, int obj2_bottom_y);

int main() {
    srand(time(0));
    int run = 1;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    struct Node *Snake_head_pos_history = List_Init(SNAKE_HEAD_POS_X*WIN_LEN + SNAKE_HEAD_POS_Y);
    SDL_Rect snake_cell = {SNAKE_HEAD_POS_X, SNAKE_HEAD_POS_Y, CELL_WIDTH, CELL_HEIGHT};

    int food_pos_x = rand() % WINDOW_WIDTH;
    int food_pos_y = rand() % WINDOW_HEIGHT;
    SDL_Rect food = {food_pos_x, food_pos_y, CELL_WIDTH, CELL_HEIGHT};
    printf("%d\n", score);

    int frame = 0;
    while (run) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                            if (snake_vel_y == 0) {
                                snake_vel_x = 0;
                                snake_vel_y = -SNAKE_VELOCITY;
                            } break;
                        case SDLK_s:
                            if (snake_vel_y == 0) {
                            snake_vel_x = 0;
                            snake_vel_y = SNAKE_VELOCITY;
                            } break;
                        case SDLK_a:
                            if (snake_vel_x == 0) {
                            snake_vel_y = 0;
                            snake_vel_x = -SNAKE_VELOCITY;
                            } break;
                        case SDLK_d:
                            if (snake_vel_x == 0) {
                            snake_vel_y = 0;
                            snake_vel_x = SNAKE_VELOCITY;
                            } break;
                        case SDLK_SPACE:
                            snake_vel_x = snake_vel_y = 0;
                            break;
                        case SDLK_ESCAPE:
                            run = 0;
                            break;
                        default:
                            break;
                    }
                } break;

                case SDL_QUIT:
                    run = 0;
                    break;
            }
        }
        if (!run) break;

        snake_cell.x += snake_vel_x;
        snake_cell.y += snake_vel_y;
        //printf("%d %d\n", snake_cell.x, snake_cell.y);

        if (snake_vel_x != 0 || snake_vel_y != 0)
            Snake_head_pos_history = List_AppInit(snake_cell.x*WIN_LEN + snake_cell.y, Snake_head_pos_history);

        if (SDLRect_IsCollision(snake_cell, food)) {
            score++;
            snake_length++;
            food.x = rand() % WINDOW_WIDTH;
            food.y = rand() % WINDOW_HEIGHT;

            printf("%d\n", score);
        }

        if (snake_cell.x+snake_cell.w < 0) {snake_cell.x = WINDOW_WIDTH;}
        else if (snake_cell.x > WINDOW_WIDTH) {snake_cell.x = -snake_cell.w;}
        if (snake_cell.y+snake_cell.h < 0) {snake_cell.y = WINDOW_HEIGHT;}
        if (snake_cell.y > WINDOW_HEIGHT) {snake_cell.y = -snake_cell.h;}

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        int temp_x = snake_cell.x, temp_y = snake_cell.y;
        int snake_cell_iter1, cell_pos;
        for (snake_cell_iter1=0; snake_cell_iter1 < (snake_length-1)*CELL_WIDTH+1; snake_cell_iter1++) {
            
            cell_pos = List_GetValue(Snake_head_pos_history, snake_cell_iter1);
            snake_cell.x = cell_pos/WIN_LEN;
            snake_cell.y = cell_pos%WIN_LEN;
            SDL_RenderFillRect(renderer, &snake_cell);

        }
        snake_cell.x = temp_x;
        snake_cell.y = temp_y;

        int snake_cell_iter2;
        for (snake_cell_iter2=CELL_WIDTH*2+1; snake_cell_iter2 < snake_length*CELL_WIDTH; snake_cell_iter2++) {
            
            cell_pos = List_GetValue(Snake_head_pos_history, snake_cell_iter2);
            snake_cell.x = cell_pos/WIN_LEN;
            snake_cell.y = cell_pos%WIN_LEN;
            if (Coord_IsCollision(temp_x, temp_y, temp_x+CELL_WIDTH, temp_y+CELL_HEIGHT, snake_cell.x, snake_cell.y, snake_cell.x+snake_cell.w, snake_cell.y+snake_cell.h)) {
                printf("Game Over!\nSCORE: %d\n", score);
                run = 0;
                break;
            }

        }
        snake_cell.x = temp_x;
        snake_cell.y = temp_y;

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &food);

        SDL_RenderPresent(renderer);
        SDL_Delay(5);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
        SDL_RenderClear(renderer);
    }

    List_Delete(Snake_head_pos_history);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int SDLRect_IsCollision(SDL_Rect obj1, SDL_Rect obj2) {
    if ((obj1.x <= obj2.x) && (obj2.x <= obj1.x+obj1.w) || (obj2.x <= obj1.x) && (obj1.x <= obj2.x+obj2.w)) {
        if ((obj1.y <= obj2.y) && (obj2.y <= obj1.y+obj1.h) || (obj2.y <= obj1.y) && (obj1.y <= obj2.y+obj2.h)) {
            return 1;
        }
    }
    return 0;
}

int Coord_IsCollision(int obj1_top_x, int obj1_top_y, int obj1_bottom_x, int obj1_bottom_y, int obj2_top_x, int obj2_top_y, int obj2_bottom_x, int obj2_bottom_y) {
    if ((obj1_top_x <= obj2_top_x) && (obj2_top_x <= obj1_bottom_x) || (obj2_top_x <= obj1_top_x) && (obj1_top_x <= obj2_bottom_x)) {
        if ((obj1_top_y <= obj2_top_y) && (obj2_top_y <= obj1_bottom_y) || (obj2_top_y <= obj1_top_y) && (obj1_top_y <= obj2_bottom_y)) {
            return 1;
        }
    }
    return 0;
}
