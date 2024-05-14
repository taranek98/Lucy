#include "IO_Regs.h"
#include "../Timer/Timer.h"
#include "../Interrupt/Interrupt.h"
#include "../PPU/PPU.h"
#include "../Bus/Bus.h"
#include <iostream>

static IO_Regs io_regs;

/*0xFF00 - 0xFF7F*/
U8 IO_Regs::IO_RegsRead(U16 address)
{
    U8 value = 0;

    if(address == 0xFF00)
    {
        /*TODO: Joypad implemented*/
    }
    else if(address == 0xFF01)
    {
        value = SB;   
    }
    else if(address == 0xFF02)
    {
        value = SC;   
    }
    else if((address >= 0xFF04) && (address <= 0xFF07))
    {
        value = TimerGetObj() -> TimerRead(address);
    }
    else if(address == 0xFF0F)
    {
        value = InterruptGetObj() -> InterruptIF_Read();
    }
    else if((address >= 0xFF10) && (address <= 0xFF3F))
    {
        /*TODO: Audio Implement*/
    }
    else if((address >= 0xFF40) && (address <= 0xFF4B))
    {
        value = LcdGetObj() -> Read(address);
    }
    /*TODO: Implement the rest*/
    return value;
}

void IO_Regs::IO_RegsWrite(U16 address, U8 value)
{
    /*TODO: Implement this*/
    if(address == 0xFF00)
    {
        /*TODO: Joypad implemented*/
    }
    else if(address == 0xFF01)
    {
        SB = value;   
    }
    else if(address == 0xFF02)
    {
        SC = value;   
    }
    else if(address <= 0xFF07)
    {
        TimerGetObj() -> TimerWrite(address, value);
    }
    else if(address == 0xFF0F)
    {
        InterruptGetObj() -> InterruptIF_Write(value);
    }
    else if((address >= 0xFF10) && (address <= 0xFF3F))
    {
        /*TODO: Audio Implement*/
    }
    else if((address >= 0xFF40) && (address <= 0xFF45))
    {
        LcdGetObj() -> Write(address, value);
    }
    else if(address == 0xFF46) /*TODO: zrób to porzadnie*/
    {
        U16 addresss = value << 8 ; // source address is data * 100
        for (int i = 0 ; i < 0xA0; i++)
        {
            BusWrite(0xFE00+i, BusRead(addresss+i)) ;
        }
    }
    else if((address >= 0xFF46) && (address <= 0xFF4B))
    {
        LcdGetObj() -> Write(address, value);
    }
    /*TODO: Implement the rest*/
}



IO_Regs *IO_RegsGetObj()
{
    return &io_regs;
}
