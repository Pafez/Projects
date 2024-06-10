#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 400

#define CELL_WIDTH 10
#define CELL_HEIGHT 10

#define SNAKE_POS_X 80
#define SNAKE_POS_Y 40
#define SNAKE_VELOCITY 1

int snake_vel_x = 0, snake_vel_y = 0, score = 0;

int is_collision(SDL_Rect obj1, SDL_Rect obj2);

int main() {
    int run = 1;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("DVD_LOGO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Rect snake = {SNAKE_POS_X, SNAKE_POS_Y, CELL_WIDTH, CELL_HEIGHT};

    int food_pos_x = rand() % WINDOW_WIDTH;
    int food_pos_y = rand() % WINDOW_HEIGHT;
    SDL_Rect food = {food_pos_x, food_pos_y, CELL_WIDTH, CELL_HEIGHT};
    printf("%d\n", score);

    while (run) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                            snake_vel_x = 0;
                            snake_vel_y = -SNAKE_VELOCITY;
                            break;
                        case SDLK_s:
                            snake_vel_x = 0;
                            snake_vel_y = SNAKE_VELOCITY;
                            break;
                        case SDLK_a:
                            snake_vel_y = 0;
                            snake_vel_x = -SNAKE_VELOCITY;
                            break;
                        case SDLK_d:
                            snake_vel_y = 0;
                            snake_vel_x = SNAKE_VELOCITY;
                            break;
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

        snake.x += snake_vel_x;
        snake.y += snake_vel_y;

        if (is_collision(snake, food)) {
            score++;
            food.x = rand() % WINDOW_WIDTH;
            food.y = rand() % WINDOW_HEIGHT;
            printf("%d\n", score);
        }

        if (snake.x+snake.w < 0) {snake.x = WINDOW_WIDTH;}
        else if (snake.x > WINDOW_WIDTH) {snake.x = -snake.w;}
        if (snake.y+snake.h < 0) {snake.y = WINDOW_HEIGHT;}
        if (snake.y > WINDOW_HEIGHT) {snake.y = -snake.h;}

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &snake);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &food);

        SDL_RenderPresent(renderer);
        SDL_Delay(5);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int is_collision(SDL_Rect obj1, SDL_Rect obj2) {
    if ((obj1.x <= obj2.x) && (obj2.x <= obj1.x+obj1.w) || (obj2.x <= obj1.x) && (obj1.x <= obj2.x+obj2.w)) {
        if ((obj1.y <= obj2.y) && (obj2.y <= obj1.y+obj1.h) || (obj2.y <= obj1.y) && (obj1.y <= obj2.y+obj2.h)) {
            return 1;
        }
    }
    return 0;
}