#pragma once
#include "../General/General.h"

#define ADDRESS_DIV 0xFF04
#define ADDRESS_TIMA 0xFF05
#define ADDRESS_TMA 0xFF06
#define ADDRESS_TAC 0xFF07

class Timer
{
    private:
        /*Fields*/
        U8 DIV;              /*0xFF04 - Divider register*/
        U8 TIMA;             /*0xFF05 - Timer counter*/
        U8 TMA;              /*0xFF06 - Timer modulo*/
        U8 TAC;              /*0xFF07 - Timer control*/
        U16 CylecesCounter;  /*Counter of Cpu Cyceles*/
        U8 PrevTACvalue;
        U16 ClockFreq;
        /*Methods*/
        void TimerDIV_Update(U8 cycles);
        bool TimerGetTAC2Bit();
        void TimerUpdateFreqClock();

    public:
        Timer();
        void TimerStep(U8 cycles);
        void TimerWrite(U16 address, U8 value);
        U8 TimerRead(U16 address);
        
};

Timer *TimerGetObj();
void TimerInit();