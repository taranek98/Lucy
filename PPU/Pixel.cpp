#include "Pixel.h"
#include <iostream>
PixelList::PixelList()
{
    firstPixel = nullptr;
    pixelCount = 0;
}

void PixelList::AddPixel(U8 idColor)
{
    Pixel * pixel = firstPixel; 
    bool pixelAdded = false;
    
    if(pixel == nullptr)
    {
        pixelCount++;
        firstPixel = new Pixel;
        firstPixel->color = idColor;
        firstPixel->nextPixel = nullptr;
        pixelAdded = true;
    }
    while (pixelAdded != true)
    {
        if(pixel->nextPixel == nullptr)
        {
            pixelCount++;
            pixel->nextPixel = new Pixel;
            pixel->nextPixel->color = idColor;
            pixel->nextPixel->nextPixel = nullptr;
            pixelAdded = true;
        }
        else
        {
            pixel = pixel->nextPixel;
        }
    }
}

U8 PixelList::GetPixelCount()
{
    return pixelCount;
}

U8 PixelList::PopPixel()
{
    Pixel * pixel = firstPixel;
    U8 color = pixel->color;
    firstPixel = firstPixel->nextPixel;
    pixelCount--;
    delete pixel;
    return color;
}

void PixelList::Reset()
{
    while (pixelCount != 0)
    {
        PopPixel();
    }

}
