#pragma once
#include "../General/General.h"

struct Pixel
{
    U8 color;
    // U8 palette;
    // U8 BgPriority;
    Pixel * nextPixel;
};

class PixelList
{
    private:
        Pixel * firstPixel;
        U8 pixelCount;
    public: 
        PixelList();
        void AddPixel(U8 idColor);
        U8 GetPixelCount();
        U8 PopPixel();
        void Reset();
};