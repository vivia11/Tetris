#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <iostream>

#include "TextureManager.h"
#include "TetrisManager.h"

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = NULL;
    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, 320, 480, SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n",
               IMG_GetError());
        return 1;
    }

    const int FPS = 10;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Initialize our texture manager
    TextureManager textMgr = TextureManager(renderer);
    textMgr.init();

    // Initialize our tetris manager
    TetrisManager tetrisMgr = TetrisManager(renderer, &textMgr);
    
    bool quit = false;
    SDL_Event e;

    int dropDelay = 500;
    int dropTime = 0;

    bool drop = false;
    
    tetrisMgr.createNewTetris();
    while (!quit)
    {
        frameStart = SDL_GetTicks();
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_LEFT:
                    tetrisMgr.moveLeft();
                    break;
                case SDLK_RIGHT:
                    tetrisMgr.moveRight();
                    break;
                case SDLK_UP:
                    tetrisMgr.rotate();
                    break;
                case SDLK_DOWN:
                    dropDelay = 50;
                    break;
                case SDLK_SPACE:
                    drop = true;
                    break;
                default:
                    break;
                }
            }
            else if (e.type == SDL_KEYUP)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_DOWN:
                    dropDelay = 500;
                    break;
                case SDLK_SPACE:
                    drop = false;
                    break;
                default:
                    break;
                }
            }
        }
        if (drop)
        {
            tetrisMgr.drop();
            drop = false;
        }
        tetrisMgr.clearLines();
        tetrisMgr.draw();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
        dropTime += (SDL_GetTicks() - frameStart);
        if (dropTime > dropDelay)
        {
            dropTime = 0;
            tetrisMgr.dropTetris();
        }
    }
        
    // Cleanup
    textMgr.cleanup(); // Destory all textures

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();

    return 0;
}
