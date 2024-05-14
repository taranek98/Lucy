#pragma once
#include <SDL2/SDL.h>
#include "../General/General.h"

#define WIDHT 160*3
#define HEIGHT 144*3
#define WIDHT_DB 16*8*3
#define HEIGHT_DB 24*8*3

class Screen
{
    private:
        SDL_Window * window;
        SDL_Renderer * render;
        SDL_Texture * texture;
        SDL_Surface * surface;
        SDL_Window * windowTile;
        SDL_Renderer * renderTile;
        SDL_Texture * textureTile;
        SDL_Surface * surfaceTile;
        U32 currentFrame[144][160];
        U32 colors[4];

    public:
        Screen();
        bool ScreenListen();
        void ScreenUpdate();
        void ScreenUpdateCurrentFrame(U8 x, U8 y, U8 color);
        void ScreenDebugBgTiles();
};

Screen * ScreenGetObj();

class Tile
{
    private:
        

    public:
        U16 tileAddress;
        U8 pixelLine[8][2];
        Tile();
        void updateTileDebug(U8 ofset);
        U8 TileSpecifyColor(U8 lsb, U8 msb);
        ~Tile();
};