#pragma once
#include "../General/General.h"

#define VBLANK_INTERRUPT 1
#define LCD_STAT_INTERRUPT 2
#define TIMER_INTERRUPT 4
#define SERIAL_INTERRUPT 8
#define JOYPAD_INTERRUPT 16

class Interrupt
{
    private:
        /*Fields*/
        bool IME;       /*Interrupt master enable flag*/
        bool setIME;
        U8 IE;          /*0xFFFF Interrupt Enable*/
        U8 IF;          /*0xFF0F Interrupt flag*/
        /*Methods*/
        bool InterruptCheckRequest(U8 interruptMode);
        void InterruptHandler(U8 interruptMode);

    public:
        Interrupt();
        void InterruptIE_Write(U8 value);
        U8 InterruptIE_Read();
        void InterruptEnableIME();
        void InterruptEnableIMEbyRETI();
        void InterruptDisableIME();
        U8 InterruptIF_Read();
        void InterruptIF_Write(U8 value);
        void InterruptRequest(U8 value);
        void InterruptStep();
        bool InterruptGetIME();
        bool InterruptGetSetIME();
        U8 InterruptGetIF();
        U8 InterruptGetIE();
};

Interrupt * InterruptGetObj();