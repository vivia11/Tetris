#include "TextureManager.h"

TextureManager::TextureManager(SDL_Renderer* renderer) :
    mRenderer(renderer)
{
}

TextureManager::~TextureManager()
{
    cleanup();
}

void TextureManager::init()
{
    mBackground = addTexture("images/background.png");
    mFrame = addTexture("images/frame.png");
    createTiles();
}

void TextureManager::cleanup()
{
    for (auto tile : mTiles)
    {
        SDL_DestroyTexture(tile);
        tile = NULL;
    }

    SDL_DestroyTexture(mBackground);
    mBackground = NULL;

    SDL_DestroyTexture(mFrame);
    mFrame = NULL;
}

void TextureManager::createTiles()
{
    SDL_Rect src;
    src.w = src.h = 18;
    src.x = src.y = 0;

    SDL_Texture* fullTex = addTexture("images/tiles.png");

    for (int i = 0; i < MAX_TILE_NUM; i++)
    {
        src.x = 18*i;
        mTiles[i] = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_ARGB8888,
                                      SDL_TEXTUREACCESS_TARGET,
                                      src.w, src.h);
        SDL_SetRenderTarget(mRenderer, mTiles[i]);
        SDL_RenderCopy(mRenderer, fullTex, &src, NULL);
    }

    SDL_SetRenderTarget(mRenderer, NULL);
    SDL_DestroyTexture(fullTex);
}

SDL_Texture* TextureManager::addTexture(std::string path)
{
    SDL_Surface* tmpSurface = NULL;
    tmpSurface = IMG_Load(path.c_str());

    SDL_Texture* newText = NULL;

    if (!tmpSurface)
    {
        printf("Unable to load image %s! SDL_image error: %s\n",
               path.c_str(), IMG_GetError());
    }
    else
    {
        newText = SDL_CreateTextureFromSurface(mRenderer, tmpSurface);
        if (!newText)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n",
                    path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(tmpSurface);
    }
    return newText;
}
