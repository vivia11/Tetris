#include "TetrisManager.h"

#include <time.h>

TetrisManager::TetrisManager(SDL_Renderer* mRenderer, TextureManager* mTextMgr) :
    mRenderer(mRenderer),
    mTextMgr(mTextMgr)
{
    srand(time(0));
}
  
TetrisManager::~TetrisManager()
{}

void TetrisManager::draw()
{
    SDL_RenderClear(mRenderer);
    SDL_RenderCopy(mRenderer, mTextMgr->background(), NULL, NULL);
    for (int i = 0; i < MAX_HEIGHT; i++)
    {
        for (int j = 0; j < MAX_WIDTH; j++)
        {
            if (mPile[i][j])
            {
                SDL_Rect rect;
                rect.x = 28 + 18*j;
                rect.y = 31 + 18*i;
                rect.w = rect.h = 18;
                SDL_RenderCopy(mRenderer, mTextMgr->tile(mPile[i][j]-1),
                               NULL, &rect);
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        SDL_Rect rect;
        rect.x = 28 + 18*(p.x[i]);
        rect.y = 31 + 18*(p.y[i]);
        rect.w = rect.h = 18;
        SDL_RenderCopy(mRenderer, mTextMgr->tile(p.color - 1),
                        NULL, &rect);
    }

    SDL_RenderCopy(mRenderer, mTextMgr->frame(), NULL, NULL);
    SDL_RenderPresent(mRenderer);
}

void TetrisManager::createNewTetris()
{
    int color = rand()%8 + 1;
    int fig =  rand()%7;

    p.color = color;
    for (int i = 0; i < 4; i++)
    {
        p.x[i] = figure[fig][i]/2;
        p.y[i] = figure[fig][i]%2;
    }
    if (!checkBounds(p))
        std::cout << "END GAME CONDITION" << std::endl;
}

void TetrisManager::dropTetris()
{
    struct Tetris old;
    old = p;
    for (int i = 0; i < 4; i++)
        p.y[i]++;

    if (!checkBounds(p))
    {
        p = old;
        for (int i = 0; i <4; i++)
            mPile[p.y[i]][p.x[i]] = p.color;
        
        createNewTetris();
    }
}

void TetrisManager::dump()
{
    for (int i = 0; i < MAX_HEIGHT; i++)
    {
        for (int j = 0; j < MAX_WIDTH; j++)
            std::cout << mPile[i][j];
        std::cout << std::endl;
    }
    std::cout << "************************" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const struct Tetris t)
{
    for (int i = 0; i < 4; i++)
        os << t.x[i] << " , " << t.y[i] << std::endl;

    return os;
}

void TetrisManager::moveRight()
{
    struct Tetris old;
    old = p;
    for (int i = 0; i < 4; i++)
        p.x[i]++;

    if (!checkBounds(p))
        p = old;
}

void TetrisManager::moveLeft()
{
    struct Tetris old;
    old = p;
    for (int i = 0; i < 4; i++)
        p.x[i]--;

    if (!checkBounds(p))
        p = old;
}

void TetrisManager::rotate()
{
    int x = p.x[1]; int y = p.y[1];
    struct Tetris old = p;
    for (int i = 0; i < 4 ; i++)
    {
        int dx = p.y[i] - y;
        int dy = p.x[i] - x;
        p.x[i] = x - dx;
        p.y[i] = y - dy;
    }
    if (!checkBounds(p))
        p = old;
}

void TetrisManager::clearLines()
{
    int k = MAX_HEIGHT-1;
    for (int i = MAX_HEIGHT-1; i > 0; i--)
    {
        int count = 0;
        for (int j = 0; j < MAX_WIDTH; j++)
        {
            if (mPile[i][j])
                count++;
            mPile[k][j] = mPile[i][j];
        }
        if (count < MAX_WIDTH)
            k--;
    }
}

void TetrisManager::drop()
{
    struct Tetris old;
    while(true)
    {
        old = p; 
        for (int i = 0; i < 4; i++)
            p.y[i]++;
        if (!checkBounds(p))
        {
            p = old;
            break;
        }
    }
}

bool TetrisManager::checkBounds(const struct Tetris t)
{
    for (int i = 0; i < 4; i++)
    {
        if (t.x[i] < 0 || t.x[i] >= MAX_WIDTH ||
            t.y[i] >= MAX_HEIGHT)
        {
            return false;
        }
        else if (mPile[t.y[i]][t.x[i]])
        {
            return false;
        }
    }
    return true;
}
