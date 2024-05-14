#pragma once
#include "../General/General.h"
#include "../LCD/LCD.h"
#include "Pixel.h"

enum PixelFifo_FetcherState 
{
    GetTileID = 0,
    GetDataLow = 1,
    GetDataHigh = 2,
    Sleep = 3,
    Push = 4,
};

class PixelFifo
{
    private:
        PixelList list;
        PixelFifo_FetcherState fetcherState;
        U8 xPositionCounter;
        U8 xPushCounter;
        U8 xFetch;
        U8 tileId;
        U8 dataLow;
        U8 dataHigh;
        LCD * lcd;

        void FetcherStateMachineStep();
        bool FetcherPushPixelToFifo();
        void PushToLCD();
        U8 SpecifyColor(U8 idColor);
        bool IsPixelWindowPosition();
        void GetWindowTile();
        void GetBgTile();
        
    public:
        PixelFifo();
        U8 Step();
        void Reset();
};

