#include "Interrupt.h"
#include "../CPU/CPU.h"
#include <iostream>

static Interrupt interrupt;

bool Interrupt::InterruptCheckRequest(U8 interruptMode)
{
    if(((IF & interruptMode) != 0) && ((IE & interruptMode) != 0))
    {
        InterruptHandler(interruptMode);
        return true;
    }
    return false;
}

void Interrupt::InterruptHandler(U8 interruptMode)
{
    IME = false;
    IF &= ~interruptMode;
    CpuGetObj() -> CpuPrepareIntterupt(interruptMode);
}

Interrupt::Interrupt()
{
    IME = false;
    IE = 0x00;
    IF = 0x00;
    setIME = false;
}

void Interrupt::InterruptIE_Write(U8 value)
{
    IE = value;
}

U8 Interrupt::InterruptIE_Read()
{
    return IE;
}

void Interrupt::InterruptEnableIME()
{
    setIME = true;
}

void Interrupt::InterruptEnableIMEbyRETI()
{
    IME = true;
}

void Interrupt::InterruptDisableIME()
{
    IME = false;
}

void Interrupt::InterruptIF_Write(U8 value)
{
    IF = value;
}

void Interrupt::InterruptRequest(U8 value)
{
    IF |= value;
}

void Interrupt::InterruptStep()
{
    // std::cout<<"IE: "<<(U16)IE<<std::endl;
    if(IME == true)
    {   
        if(InterruptCheckRequest(VBLANK_INTERRUPT) == false);
        {
            if(InterruptCheckRequest(LCD_STAT_INTERRUPT) == false)
            {
                if(InterruptCheckRequest(TIMER_INTERRUPT) == false)
                {
                    if(InterruptCheckRequest(SERIAL_INTERRUPT) == false)
                    {
                        // TODO: Implemented(void)InterruptCheckRequest(JOYPAD_INTERRUPT);
                    }
                }
            }
        }
        setIME = false;
    }

    if(setIME == true)
    {
        IME = true;
    }
}

bool Interrupt::InterruptGetIME()
{
    return IME;
}

bool Interrupt::InterruptGetSetIME()
{
    return setIME;
}

U8 Interrupt::InterruptGetIF()
{
    return IF;
}

U8 Interrupt::InterruptGetIE()
{
    return IE;
}

U8 Interrupt::InterruptIF_Read()
{
    return IF;
}

Interrupt *InterruptGetObj()
{
    return &interrupt;
}
