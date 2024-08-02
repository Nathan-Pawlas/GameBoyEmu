#include <stdio.h>
#include <SDL.h>
#include <Windows.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    const int WIDTH = 640;
    const int HEIGHT = 480;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* image = NULL;
    SDL_Rect rectImage;
    int w, h;
    int frames = 0;
    clock_t last_tick = clock();

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_QueryTexture(image, NULL, NULL, &w, &h);
    rectImage = { 0, 0, w, h };
    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }

        rectImage.x += 4;
        rectImage.y += 4;

        if (rectImage.x > WIDTH) rectImage.x = 0;
        if (rectImage.y > HEIGHT) rectImage.y = 0;

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);

        SDL_RenderFillRect(renderer, NULL);

        SDL_RenderCopy(renderer, image, NULL, &rectImage);
        SDL_RenderPresent(renderer);

        frames++;

        clock_t now = clock();
        if (now > (last_tick + CLOCKS_PER_SEC))
        {
            char buff[52];
            _snprintf(buff, 52, "%d fps\n", frames);
            OutputDebugStringA(buff);
            frames = 0;
            last_tick = now;
        }
    }

    SDL_DestroyTexture(image);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}