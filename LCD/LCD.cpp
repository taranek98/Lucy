#include "LCD.h"
#include "../Interrupt/Interrupt.h"
#include "../PPU/PPU.h"
#include <iostream>

static LCD lcd;

LCD::LCD()
{
    LCDC.val = 0x91;
    STAT.val = 0x00;
    SCX = 0x00;
    SCY = 0x00;
    LY = 0x00;
    LYC = 0x00;
    BGP = 0xFC;
    WY = 0x00;
    WX = 0x00;
}

bool LCD::IsEnable()
{
    if(LCDC.bit.LCDandPPUenable == false )
    {
        Reset();
        return false;
    }

    return true;
}

U8 LCD::GetLY()
{
    return LY;
}

U8 LCD::GetLYC()
{
    return LYC;
}

U8 LCD::GetWY()
{
    return WY;
}

U8 LCD::GetWX()
{
    return WX;
}

U8 LCD::GetLCDC()
{
    return LCDC.val;
}

void LCD::ResetLY()
{
    LY = 0;
}

void LCD::IncLY()
{
    if (IsWidowActive() && LY >= WY && LY < WY + 144) /*TODO: popraw to by jakos wygladało*/
    {
        PpuGetObj()->IncWindowLine();
    }
    LY++;
    if(LY == LYC)
    {
        STAT.bit.LY_Flag = 1;
        if(STAT.bit.LYC == true)
        {
            InterruptGetObj() -> InterruptRequest(LCD_STAT_INTERRUPT);
        }
    }
    else
    {
        STAT.bit.LY_Flag = 0;
    }
}

bool LCD::IsBgEnable()
{    
    return LCDC.bit.BGandWindowEnable;
}

bool LCD::IsWinEnable()
{
    return LCDC.bit.WindowsEnable;
}

bool LCD::ObjIsEnable()
{
    return LCDC.bit.OBJenable;
}

bool LCD::GetBgTileMap()
{
    return LCDC.bit.BGtileMapArea;
}

bool LCD::GetWinTileMap()
{
    return LCDC.bit.WindowsTileMapArea;
}

bool LCD::GetBgAndWinTileArea()
{
    return LCDC.bit.BGandWindowTileDataArea;
}

U8 LCD::GetSCX()
{
    return SCX;
}

U8 LCD::GetSCY()
{
    return SCY;
}

U8 LCD::GetBGP()
{
    return BGP;
}

STAT_type LCD::GetSTAT()
{
    return STAT;
}

U8 LCD::Read(U16 address)
{
    U8 value = 0;
    switch (address)
    {
    case ADDRESS_LCDC:
        value = LCDC.val;
        break;
    
    case ADDRESS_STAT:
        value = STAT.val;
        break;

    case ADDRESS_SCY:
        value = SCY;
        break;

    case ADDRESS_SCX:
        value = SCX;
        break;

    case ADDRESS_LY:
        value = LY;
        break;
    
    case ADDRESS_LYC:
        value = LYC;
        break;

    case ADDRESS_BGP:
        value = BGP;
        break;

    case ADDRESS_OBP0:
        value = OBP0;
        break;

    case ADDRESS_OBP1:
        value = OBP1;
        break;

    case ADDRESS_WX:
        value = WX;
        break;
    
    case ADDRESS_WY:
        value = WY;
        break;

    default:
        /*TODO: czy to tu potrzebne???*/
        std::cout<<"Unhandled LCD address: "<<address<<std::endl;
        AbortProgram();
        break;
    }
    return value;
}

void LCD::Write(U16 address, U8 value)
{
    switch (address)
    {
    case ADDRESS_LCDC:
        LCDC.val = value;
        break;
    
    case ADDRESS_STAT:
        STAT.val = value;
        break;

    case ADDRESS_SCY:
        SCY = value;
        break;

    case ADDRESS_SCX:
        SCX = value;
        break;

    case ADDRESS_LY:
        LY = value;
        break;
    
    case ADDRESS_LYC:
        LYC = value;
        break;
    
    case ADDRESS_BGP:
        BGP = value;
        break;

    case ADDRESS_OBP0:
        OBP0 = value;
        break;

    case ADDRESS_OBP1:
        OBP1 = value;
        break;

    case ADDRESS_WX:
        WX = value;
        break;
    
    case ADDRESS_WY:
        WY = value;
        break;

    default:
    /*TODO: Implement error handling*/
        break;
    }
}

void LCD::SetSTAT_ModeFlag(U8 mode)
{
    STAT.bit.ModeFlag = mode & 0x03;
}

void LCD::Reset()
{
    LY = 0;
    STAT.bit.ModeFlag = 1;
}

bool LCD::IsWidowActive()
{
    if(IsWinEnable())
    {
        if(WX >= 0 && WX <= 166)
        {
            if(WY >= 0 && WY <= 144)
            {
                return true;
            }
        }
    }
    return false;
}
/*************Interfaces*****************/

LCD *LcdGetObj()
{
    return &lcd;
}