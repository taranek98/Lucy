#pragma once
#include "../General/General.h"
#include "../LCD/LCD.h"
#include "PixelFifo.h"

enum PPU_StateMachine
{
    OAM_Scan = 0,
    PixDraw = 1,
    Hblank = 2,
    Vblank = 3
};

class PPU
{
    private:
        /*Fields*/
        U16 CyclesCounter;
        LCD * lcd;
        PPU_StateMachine state;
        PixelFifo pixelFifo;
        U8 windowLine;
    
        /*Methods*/
        void PpuStateMachine(U8 cycles);
        void PpuOAMState();
        void PpuPixDrawState(U8 cycles);
        void PpuHblankState();
        void PpuVblankState();
        bool PpuCheckLcd(U8 cycles);

    public:
        PPU();
        void PpuStep(U8 cycles);
        void IncWindowLine();
        U8 GetWindowLine();
};

/***************Interfaces******************/
void PpuInit();
PPU * PpuGetObj();
