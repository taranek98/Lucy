#include "PixelFifo.h"
#include "../Bus/Bus.h"
#include "../Screen/Screen.h"
#include "PPU.h"
#include <iostream>


void PixelFifo::FetcherStateMachineStep()
{
    switch (fetcherState)
    {
        case GetTileID:
        {
            if(lcd -> IsBgEnable())
            {
                if(lcd -> IsWidowActive() && IsPixelWindowPosition())
                {
                    GetWindowTile();
                }
                else
                {
                    GetBgTile();
                }
                if(lcd->GetBgAndWinTileArea() == 0)
                {
                    tileId += 128;
                }
            }
            xFetch += 8;
            fetcherState = GetDataLow;
            break;
        }
        case GetDataLow:
        {
            U16 tileArea = 0x8000;
            if(lcd->GetBgAndWinTileArea() == 0)
            {
                tileArea = 0x8800;
            }
            dataLow = BusRead(tileArea + (tileId * 16) + (((lcd->GetLY() + lcd->GetSCY()) % 8) * 2));
            fetcherState = GetDataHigh;
            break;
        }
        case GetDataHigh:
        {
            U16 tileArea = 0x8000;
            // std::cout<<"LY: "<<(U16)lcd -> GetLY()<<" sda "<<(U16)lcd->GetBgAndWinTileArea()<<std::endl;
            if(lcd->GetBgAndWinTileArea() == 0)
            {
                tileArea = 0x8800;
            }
            dataHigh = BusRead(tileArea + (tileId * 16) + (((lcd->GetLY() + lcd->GetSCY()) % 8) * 2) + 1);
            fetcherState = Sleep;
            break;
        }
        case Sleep:
        {
            fetcherState = Push;
            break;
        }
        case Push:
        {
            if(FetcherPushPixelToFifo() == true)
            {
                fetcherState = GetTileID;
            }
            break;
        }
    }
}

bool PixelFifo::FetcherPushPixelToFifo()
{
    if(list.GetPixelCount() <= 8)
    {   
        int x = xFetch - (8 - (lcd ->GetSCX() % 8));
        for(S8 i = 7; i >= 0; i--)
        {
            U8 color;
            U8 lsb = (dataLow & (0x01 << i)) >> i;
            U8 msb = (dataHigh & (0x01 << i)) >> i;
            if(lcd->IsBgEnable() == true)
            {
                color = SpecifyColor(ShiftLeft(msb,1) | lsb);
            }
            else
            {
                color = SpecifyColor(0);
            }
            if(x >= 0)
            {
                list.AddPixel(color);
            }
        }
        return true;
    }
    return false;
}

void PixelFifo::PushToLCD()
{
    if(list.GetPixelCount() > 8)
    {
        U8 color = list.PopPixel();
        if(xPositionCounter >= (lcd -> GetSCX() % 8))
        {
            ScreenGetObj() -> ScreenUpdateCurrentFrame(xPushCounter, lcd -> GetLY(), color);
            xPushCounter++;
        }
        xPositionCounter++;
    }
}

U8 PixelFifo::SpecifyColor(U8 idColor)
{
    /*TODO: create defines*/
    U8 value;
    U8 BGP = lcd -> GetBGP();
    switch (idColor)
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
        std::cout<<"Unhandled Color: "<<(U16)(idColor)<<std::endl;
        AbortProgram();
        break;
    }
    return value;
}

bool PixelFifo::IsPixelWindowPosition()
{
    if (xFetch + 7 >= lcd->GetWX() && xFetch + 7 < lcd->GetWX() + 144 + 14) 
    {
        if (lcd->GetLY() >= lcd->GetWY() && lcd->GetLY() < lcd->GetWY() + 160) 
        {
            return true;
        }
    }
    return false;
}

void PixelFifo::GetWindowTile()
{
    U16 winMapAddress = 0x9800;
    if(LcdGetObj() -> GetWinTileMap() == 1)
    {
        winMapAddress = 0x9C00;
    }
    tileId = BusRead(winMapAddress + ((xFetch + 7 - lcd -> GetWX()) / 8) + ((PpuGetObj()->GetWindowLine() / 8) * 32));   
}

void PixelFifo::GetBgTile()
{
    U16 bgMapAddress = 0x9800; /*TODO: sprawdz czy ta zmiena lokalna ginie*/
    if(LcdGetObj() -> GetBgTileMap() == 1)
    {
        bgMapAddress = 0x9C00;
    }
    tileId = BusRead(bgMapAddress + ((lcd->GetSCX() + xFetch) / 8) + ((((lcd->GetLY() + lcd->GetSCY())&0xFF) / 8 ) * 32));
}

PixelFifo::PixelFifo()
{
    fetcherState = GetTileID;
    xPositionCounter = 0;
    xFetch = 0;
    xPushCounter = 0;
    lcd = LcdGetObj();
    dataLow = 0;
    dataHigh = 0;
}

U8 PixelFifo::Step()
{
    static bool fetcherActive = false;
    if(fetcherActive == true)
    {
        FetcherStateMachineStep();
        fetcherActive = false;
    }
    else
    {
        fetcherActive = true;
    }
    PushToLCD();
    
    return xPushCounter;
}

void PixelFifo::Reset()
{
    fetcherState = GetTileID;
    xPositionCounter = 0;
    xFetch = 0;
    xPushCounter = 0;
    dataLow = 0;
    dataHigh = 0;
    list.Reset();
}
