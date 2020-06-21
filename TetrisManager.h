#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#include "TextureManager.h"

const int MAX_HEIGHT = 20;
const int MAX_WIDTH = 10;

const int figure[7][4] = 
{
    1,3,5,7, // I
    2,4,5,7, // Z
    3,5,4,6, // S
    3,5,4,7, // T
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5, // O
};

struct Tetris
{
    int x[4] = {0};
    int y[4] = {0};
    int color = 0;
    friend std::ostream& operator<<(std::ostream& os, const struct Tetris t);
};

class TetrisManager
{
public:
    TetrisManager(SDL_Renderer* renderer, TextureManager* textMgr);
    ~TetrisManager();

    void draw();
    void createNewTetris();
    void dropTetris();
    void dump();
    void moveRight();
    void moveLeft();
    void rotate();
    void clearLines();
    void drop();

private:
    bool checkBounds(const struct Tetris t);

    SDL_Renderer* mRenderer;
    TextureManager* mTextMgr;
    struct Tetris p;
    int mPile[MAX_HEIGHT][MAX_WIDTH] = {{0}};
};
