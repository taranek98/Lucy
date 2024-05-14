#pragma once
#include "../General/General.h"
#include "../LCD/LCD.h"

class IO_Regs
{ 
    private: 
        U8 SB;      /*0xFF01 — Serial transfer data*/
        U8 SC;      /*0xFF02 — Serial transfer control*/
    public:
        U8 IO_RegsRead(U16 address);
        void IO_RegsWrite(U16 address, U8 value);
};

IO_Regs * IO_RegsGetObj();
