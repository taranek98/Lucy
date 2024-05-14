#include "Timer.h"
#include "../Interrupt/Interrupt.h"
#include <iostream>
#include "../CPU/CPU.h"

static Timer * timer;

Timer::Timer()
{
    DIV = 0;              
    TIMA = 0;             
    TMA = 0;              
    TAC = 0;              
    CylecesCounter = 0;  
    PrevTACvalue = TAC;
    ClockFreq = 1024;
}

void Timer::TimerStep(U8 cycles)
{   
    TimerDIV_Update(cycles);
    CylecesCounter += cycles;
    if(TimerGetTAC2Bit() == true)
    {
        
        if(CylecesCounter >= ClockFreq)
        {
            TIMA++;
            if(TIMA == 255)
            {
                TIMA = TMA;
                InterruptGetObj() -> InterruptRequest(TIMER_INTERRUPT);
            }

            CylecesCounter %= ClockFreq;
        }
        // std::cout<<"\n";
        // std::cout<<"IF: "<<(U16)InterruptGetObj() -> InterruptGetIF()<<std::endl;
        // std::cout<<"TIMA: "<<(U16)TIMA<<std::endl;
        // std::cout<<"TAC: "<<(U16)TAC<<std::endl;
        // std::cout<<"Cycles Counter: "<<CylecesCounter<<std::endl;
        // std::cout<<"ClockFreq: "<<ClockFreq<<std::endl;
        // CpuGetObj()->CpuDebugPrint();
        // std::cout<<"\n";
    }
    // static U16 ddiv = 0;
    // unsigned short prev_div = ddiv;

    // ddiv+=cycles;

    // bool timer_update = false;

    // switch(TAC & (0b11)) 
    // {
    //     case 0b00:
    //         timer_update = (prev_div & (1 << 9)) && (!(ddiv & (1 << 9)));
    //         break;
    //     case 0b01:
    //         timer_update = (prev_div & (1 << 3)) && (!(ddiv & (1 << 3)));
    //         break;
    //     case 0b10:
    //         timer_update = (prev_div & (1 << 5)) && (!(ddiv & (1 << 5)));
    //         break;
    //     case 0b11:
    //         timer_update = (prev_div & (1 << 7)) && (!(ddiv & (1 << 7)));
    //         break;
    // }

    // if (timer_update && TAC & (1 << 2)) 
    // {
    //     std::cout<<"TIMA: "<<(U16)TIMA<<std::endl;
    //     std::cout<<"TAC: "<<(U16)TAC<<std::endl;
    //     std::cout<<"Cycles Counter: "<<CylecesCounter<<std::endl;
    //     std::cout<<"ClockFreq: "<<ClockFreq<<std::endl;
    //     std::cout<<"\n";
    //     TIMA++;

    //     if (TIMA == 0xFF) 
    //     {
    //             TIMA = TMA;
    //             InterruptGetObj() -> InterruptRequest(TIMER_INTERRUPT);
    //     }
    //     std::cout<<"IF: "<<(U16)InterruptGetObj() -> InterruptGetIF()<<std::endl;
    // }

}

void Timer::TimerWrite(U16 address, U8 value)
{
    switch (address)
    {
        case ADDRESS_DIV:
        {
            DIV = 0;
            break;
        }
        case ADDRESS_TIMA:
        {
            TIMA = value;
            break;
        }
        case ADDRESS_TMA:
        {
            TMA = value;
            break;
        }
        case ADDRESS_TAC:
        {
            // std::cout<<"New TAC: "<<(U16)value<<std::endl;
            TAC = value;
            TimerUpdateFreqClock();
            break;
        }

        default:
            /*TODO: Implement Error handler czy to tu potrzebne*/ 
            break;
    }
}

U8 Timer::TimerRead(U16 address)
{
    U8 value = 0;
    
    switch (address)
    {
        case ADDRESS_DIV:
        {
            value = DIV;
            break;
        }
        case ADDRESS_TIMA:
        {
            value = TIMA;
            break;
        }
        case ADDRESS_TMA:
        {
            value = TMA;
            break;
        }
        case ADDRESS_TAC:
        {
            value = TAC;
            break;
        }

        default:
            /*TODO: Implement Error handler*/
            break;
    }

    return value;
}


void Timer::TimerDIV_Update(U8 cycles)
{
    static U16 currentCycles = 0;
    currentCycles += cycles;

    if(currentCycles > 0xFF)
    {
        DIV++;
        currentCycles = 0;
    }
}

bool Timer::TimerGetTAC2Bit()
{
    return (bool)((TAC & 0x04)>>2);
}

void Timer::TimerUpdateFreqClock()
{    
    if(PrevTACvalue != TAC)
    {
        PrevTACvalue = TAC;
        // CylecesCounter = 0;
        switch(TAC & 0x03)
        {
            case 0x00: 
                ClockFreq = 1024;
                break;

            case 0x01: 
                ClockFreq = 16;
                break;

            case 0x02: 
                ClockFreq = 64;
                break;

            case 0x03: 
                ClockFreq = 256;
                break;
        }
    }
}

Timer *TimerGetObj()
{
    return timer;
}

void TimerInit()
{
    timer = new Timer;
}
