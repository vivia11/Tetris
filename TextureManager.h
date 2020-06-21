#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

const int MAX_TILE_NUM = 8;

class TextureManager
{
public:
    TextureManager(SDL_Renderer* renderer);
    ~TextureManager();
    
    void init();

    SDL_Texture* background() { return mBackground; }
    SDL_Texture* frame() { return mFrame; }
    SDL_Texture* tile(int index) { return mTiles[index]; }

    void cleanup();

private:
    SDL_Texture* addTexture(std::string path);
    void createTiles();

    SDL_Texture* mBackground;
    SDL_Texture* mFrame;
    SDL_Texture* mTiles[MAX_TILE_NUM];
    SDL_Renderer* mRenderer;
};
