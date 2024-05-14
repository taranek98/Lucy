#include "Bus.h"
#include "../Cartridge/Cartridge.h"
#include "../RAM/RAM.h"
#include "../PPU/PPU.h"
#include "../Interrupt/Interrupt.h"
#include "../IO_Regs/IO_Regs.h"
#include <iostream> /*TODO: delete*/


U8 BusRead(U16 address)
{
    U8 value = 0;

    /*0x0000 - 7FFF Cartridge ROM Banks*/
    if(address <= 0x7FFF )
    {
        value = CartridgeGetObj() -> CartridgeReadROM(address);
    }

    /*0x8000 - 0x9FFF Video RAM*/
    else if(address <= 0x9FFF)
    {
        value = RAM_GetObj() -> VRAM_Read(address);
    }

    /*0xA000 - 0xBFFF External RAM*/
    else if(address <= 0xBFFF)
    {
        value = CartridgeGetObj() ->CartridgeReadROM(address);
    }

    /*0xC000 - 0xDFFF Work RAM*/
    else if(address <= 0xDFFF)
    {
        value = RAM_GetObj() -> WRAM_Read(address);   
    }

    /*0xE000 - 0xFDFF ECHO RAM*/
    else if(address <= 0xFDFF)
    {
        /*Nothing to do*/
    }

    /*0xFE00 - 0xFE9F OAM*/
    else if(address <= 0xFE9F)
    {
        /*TODO: Implement this*/
        // value = OAM_Read();   
    }

    /*0xFEA0 - 0xFEFF Not used*/
    else if(address <= 0xFEFF)
    {
        /*Do nothing*/ 
    }

    /*0xFF00 - 0xFF7F I/O Registers */
    else if(address <= 0xFF7F)
    {
        value = IO_RegsGetObj() -> IO_RegsRead(address);
    }

    /*0xFF80 - 0xFFFE High RAM*/
    else if(address <= 0xFFFE)
    {
        value = RAM_GetObj() -> HRAM_Read(address);
    }

    /*0xFFFF Interrupt Enable register*/
    else
    {
        value = InterruptGetObj() -> InterruptIE_Read();
    }

    return value;
}

void BusWrite(U16 address, U8 value)
{
    // std::cout<<"address: "<<address<<std::endl;
    /*0x0000 - 7FFF Cartridge ROM Banks*/
    if(address <= 0x7FFF )
    {
        CartridgeGetObj() -> CartridgeWriteROM(address, value);
        // std::cout<<"address: "<<address<<std::endl;
    }

    /*0x8000 - 0x9FFF Video RAM*/
    else if(address <= 0x9FFF)
    {
        RAM_GetObj() -> VRAM_Write(address, value);
    }

    /*0xA000 - 0xBFFF External RAM*/
    else if(address <= 0xBFFF)
    {
        CartridgeGetObj() ->CartridgeWriteROM(address, value);
    }

    /*0xC000 - 0xDFFF Work RAM*/
    else if(address <= 0xDFFF)
    {
        RAM_GetObj() -> WRAM_Write(address, value);   
        
    }

    /*0xE000 - 0xFDFF ECHO RAM*/
    else if(address <= 0xFDFF)
    {
        /*Do nothing*/
    }

    /*0xFE00 - 0xFE9F OAM*/
    else if(address <= 0xFE9F)
    {
        /*TODO: Implement this*/
        // value = OAM_Write(value);   
    }

    /*0xFEA0 - 0xFEFF Not used*/
    else if(address <= 0xFEFF)
    {
        /*Do nothing*/ 
    }

    /*0xFF00 - 0xFF7F I/O Registers */
    else if(address <= 0xFF7F)
    {
        IO_RegsGetObj() -> IO_RegsWrite(address, value);
    }

    /*0xFF80 - 0xFFFE High RAM*/
    else if(address <= 0xFFFE)
    {
        RAM_GetObj() -> HRAM_Write(address, value);
    }

    /*0xFFFF Interrupt Enable register*/
    else
    {
        // std::cout<<"address: "<<address<<std::endl;
        InterruptGetObj() -> InterruptIE_Write(value);
    }
}
