#include "Screen.h"
#include "iostream"
#include "../Bus/Bus.h"

static Screen screen;

U8 tileData [] = {
    /*Tile1*/
    0x00, 0x00, 
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    /*Tile2*/
    0xFF, 0x00, 
    0xFF, 0x00,
    0xFF, 0x00,
    0xFF, 0x00,
    0xFF, 0x00,
    0xFF, 0x00,
    0xFF, 0x00,
    0xFF, 0x00,
    /*Tile3*/
    0x00, 0xFF, 
    0x00, 0xFF,
    0x00, 0xFF,
    0x00, 0xFF,
    0x00, 0xFF,
    0x00, 0xFF,
    0x00, 0xFF,
    0x00, 0xFF,
    /*Tile4*/
    0xFF, 0xFF, 
    0xFF, 0xFF,
    0xFF, 0xFF,
    0xFF, 0xFF,
    0xFF, 0xFF,
    0xFF, 0xFF,
    0xFF, 0xFF,
    0xFF, 0xFF,
};

Screen::Screen()
{
    SDL_Init(SDL_INIT_VIDEO);
/*WINDOWS*/
    window = SDL_CreateWindow("Lucy",/*-1900*/SDL_WINDOWPOS_CENTERED, /*120*/SDL_WINDOWPOS_CENTERED, WIDHT, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
/*LINUX*/ /*TODO: Implement to diffenter platform*/
    // window = SDL_CreateWindow("Lucy",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDHT, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    render = SDL_CreateRenderer(window,-1,0);

    surface = SDL_CreateRGBSurface(0, WIDHT, HEIGHT, 32,
                                            0x00FF0000,
                                            0x0000FF00,
                                            0x000000FF,
                                            0xFF000000);
    texture = SDL_CreateTexture(render,
                                                SDL_PIXELFORMAT_ARGB8888,
                                                SDL_TEXTUREACCESS_STREAMING,
                                                WIDHT, HEIGHT);


    windowTile = SDL_CreateWindow("Tiles",/*-1400*/SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED/*120*/, WIDHT_DB, HEIGHT_DB, SDL_WINDOW_ALLOW_HIGHDPI);
    renderTile = SDL_CreateRenderer(windowTile,-1,0);
    surfaceTile = SDL_CreateRGBSurface(0, WIDHT_DB, HEIGHT_DB, 32,
                                            0x00FF0000,
                                            0x0000FF00,
                                            0x000000FF,
                                            0xFF000000);
    textureTile = SDL_CreateTexture(renderTile,
                                                SDL_PIXELFORMAT_ARGB8888,
                                                SDL_TEXTUREACCESS_STREAMING,
                                                WIDHT_DB, HEIGHT_DB);
    // colors[0] = 0xFFFFFFFF; 
    // colors[1] = 0xFFAAAAAA; 
    // colors[2] = 0xFF555555; 
    // colors[3] = 0xFF000000; 
    
    colors[0] = 0xFFE0F8D0; 
    colors[1] = 0xFF88C070; 
    colors[2] = 0xFF346856; 
    colors[3] = 0xFF081820; 
    for(int i = 0; i < 144; i++)
    {
        for(int j = 0; j < 160; j++)
        {
            currentFrame[i][j] = 0;
        }
    }   
}

bool Screen::ScreenListen()
{
    SDL_Event event;

        if(SDL_PollEvent(&event))
        {
            if(SDL_QUIT == event.type)
            {
                SDL_DestroyWindow(window);
                SDL_DestroyWindow(windowTile);
                SDL_Quit();            
                return true;
            }
        }
    
    return false;
}

void Screen::ScreenUpdate()
{
    SDL_Rect rc;

    rc.x = rc.y = 0;
    rc.w = rc.h = 3;

    int indexY = 0; 
    for(rc.y = 0; rc.y < 144 * 3 ; rc.y += 3)
    {
        int indexX = 0;
        for(rc.x = 0; rc.x < 160 * 3; rc.x += 3)
        {
            // if(indexY >= 56 && indexY <= 62 && indexX <=5)
            // {
            //     SDL_FillRect(surface, &rc, currentFrame[indexY][indexX]);
            //     // std::cout<<"currentFrame["<<indexY<<"]["<<indexX<<"]: "<<currentFrame[indexY][indexX]<<std::endl;
            // }

            // if(indexY >= 120 && indexY <= 126 && indexX <=5)
            // {
                SDL_FillRect(surface, &rc, currentFrame[indexY][indexX]);
                // std::cout<<"currentFrame["<<indexY<<"]["<<indexX<<"]: "<<currentFrame[indexY][indexX]<<std::endl;
            // }
            // std::cout<<"currentFrame["<<indexY<<"]["<<indexX<<"]: "<<currentFrame[indexY][indexX]<<std::endl;
            indexX++;
        }
        indexY++;
    }
    SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
    SDL_RenderClear(render);
    SDL_RenderCopy(render, texture, NULL, NULL);
    SDL_RenderPresent(render);
}

void Screen::ScreenUpdateCurrentFrame(U8 x, U8 y, U8 color)
{
    currentFrame[y][x] = colors[color];
}

void Screen::ScreenDebugBgTiles()
{
    Tile tile;
    SDL_Rect rc;

    rc.x = rc.y = 0;
    rc.w = rc.h = 3;

    for(U8 row; row < 24; row++)
    {
        rc.x = 0;
        for(U8 column = 0; column < 16; column++)
        {
            tile.updateTileDebug(0);
            
            for(U8 y = 0; y < 8; y++)
            {
                // for(U8 x = 0; x < 8; x++)
                for(int x = 7; x >= 0; x--)
                {
                    U8 lsb, msb, color;
                    lsb = (tile.pixelLine[y][0] & (1<<x))>>x;
                    msb = (tile.pixelLine[y][1] & (1<<x))>>x;
                    color = tile.TileSpecifyColor(lsb, msb);
                    SDL_FillRect(surfaceTile, &rc, colors[color]);
                    rc.x += 3;
                }
                rc.x -= 8*3;
                rc.y += 3;
            }
            rc.y -= 8*3;
            rc.x += 8*3;
        }
        rc.y+=3*8;
    }
    SDL_UpdateTexture(textureTile, NULL, surfaceTile->pixels, surfaceTile->pitch);
    SDL_RenderClear(renderTile);
    SDL_RenderCopy(renderTile, textureTile, NULL, NULL);
    SDL_RenderPresent(renderTile);
    tile.~Tile();
}

Screen *ScreenGetObj()
{
    return &screen;
}

Tile::Tile()
{
    tileAddress = 0x8000;
}

void Tile::updateTileDebug(U8 offset)
{
    tileAddress += offset;
    for(U8 tileLine = 0; tileLine < 8; tileLine++)
    {
        for(U8 byteLine = 0; byteLine < 2; byteLine++)
        {
            pixelLine[tileLine][byteLine] = BusRead(tileAddress);
            // std::cout<<"tile address: "<<tileAddress<<" wartosc: "<<(U16)BusRead(tileAddress)<<std::endl;
            tileAddress++;       
        }
    }
}

Tile::~Tile()
{
}

U8 Tile::TileSpecifyColor(U8 lsb, U8 msb)
{   
    /*TODO: create defines*/

    U8 value, BGP;
    BGP = BusRead(0xFF47);
    switch ((msb<<1)|lsb)
    {
    case 0:
        value = BGP & 3;                /*White*/
        break;

    case 1:
        value = (BGP & 12) >> 2;        /*Light Grey*/
        break;

    case 2:
        value = (BGP & 48) >> 4;        /*Dark Grey*/
        break;

    case 3:
        value = (BGP & 192) >> 6;       /*Black*/
        break;    
    
    default:
    /*TODO: create error handling*/
        break;
    }
    return value;
}