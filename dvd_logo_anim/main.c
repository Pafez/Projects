#include <stdio.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define LOGO_WIDTH 100
#define LOGO_HEIGHT 70
#define LOGO_START_POS_X 50
#define LOGO_START_POS_Y 300


int main() {
    int run = 1;
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Rect rect = {LOGO_START_POS_X, LOGO_START_POS_Y, LOGO_WIDTH, LOGO_HEIGHT};
    int x_velocity = 1, y_velocity = 1;
    
    while (run) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                run = 0;
                break;
            }
        }
        if (!run) break;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        rect.x += x_velocity;
        rect.y += y_velocity;

        if (rect.x + rect.w >= WINDOW_WIDTH) x_velocity = -1;
        else if (rect.x <= 0) x_velocity = 1;

        if (rect.y + rect.h >= WINDOW_HEIGHT) y_velocity = -1;
        else if (rect.y <= 0) y_velocity = 1;

        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
