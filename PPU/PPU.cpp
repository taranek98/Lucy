#include <iostream>
#include "PPU.h"
#include "../Interrupt/Interrupt.h"
#include "../Bus/Bus.h"

static PPU * ppu;


void PPU::PpuStateMachine(U8 cycles)
{
    // if(lcd->GetLY() == 47 || lcd->GetLY() == 48 || lcd->GetLY() == 49)
    // std::cout<<"LY: "<<(U16)lcd->GetLY()<<" LCDC: "<<(U16)lcd ->GetLCDC()<<std::endl;
    switch(state)
    {
        case OAM_Scan: 
            PpuOAMState();
            break;

        case PixDraw: 
            PpuPixDrawState(cycles);
            break;

        case Hblank: 
            PpuHblankState();
            break;

        case Vblank: 
            PpuVblankState();
            break;
    }
}

void PPU::PpuOAMState()
{
    /*TODO Implemented OAM*/
    if(CyclesCounter >= 80)
    {
        state = PixDraw;
        pixelFifo.Reset();
        lcd -> SetSTAT_ModeFlag(0x03);
    }
}

void PPU::PpuPixDrawState(U8 cycles)
{
    U8 executeCycles = 0;
    while (executeCycles < cycles)
    {
        if(pixelFifo.Step() >= 160)
        {
            state = Hblank;
            lcd -> SetSTAT_ModeFlag(0x00);
            if(lcd -> GetSTAT().bit.Mode_0 == true)
            {
                InterruptGetObj() ->InterruptRequest(LCD_STAT_INTERRUPT);
            }
            break;
        }
        executeCycles++;
    }
}

void PPU::PpuHblankState()
{
    if(CyclesCounter >= 456) /*TODO: Create defines*/
    {
        lcd -> IncLY();
        if(lcd -> GetLY() == 144)
        {
            if(lcd -> GetSTAT().bit.Mode_1 == true)
            {
                InterruptGetObj() -> InterruptRequest(VBLANK_INTERRUPT);
            }
            state = Vblank;
            lcd -> SetSTAT_ModeFlag(0x01);
        }
        else 
        {
            state = OAM_Scan;
            lcd -> SetSTAT_ModeFlag(0x02);
        }
        CyclesCounter = CyclesCounter%456;
        // CyclesCounter = 0;
    }
}

void PPU::PpuVblankState()
{
    if (CyclesCounter >= 456) 
    {
        lcd -> IncLY();
        if(lcd -> GetLY() >= 154)
        {
            state = OAM_Scan;
            lcd -> SetSTAT_ModeFlag(0x02);
            lcd -> ResetLY();
            windowLine = 0;
        }
        CyclesCounter = CyclesCounter%456;
        // CyclesCounter = 0;
    }
}

bool PPU::PpuCheckLcd(U8 cycles)
{
    if(lcd->IsEnable() == false)
    {
        CyclesCounter = 0;
        state = Vblank;
        return false;
    }
    CyclesCounter += cycles;
    return true;
}

PPU::PPU()
{
    lcd = LcdGetObj();
}

void PPU::PpuStep(U8 cycles)
{
    if(PpuCheckLcd(cycles) == true)
    {
        PpuStateMachine(cycles);
    }
}

void PPU::IncWindowLine()
{
    windowLine++;
}

U8 PPU::GetWindowLine()
{
    return windowLine;
}

void PpuInit()
{
    ppu = new PPU();
}

PPU *PpuGetObj()
{
    return ppu;
}
