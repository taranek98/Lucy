#pragma once
#include "../General/General.h"

#define WRAM_SIZE 8192
#define VRAM_SIZE  8192  
#define HRAM_SIZE  128  
#define WRAM_START_MEMORY_ADDRESS 0xC000
#define VRAM_START_MEMORY_ADDRESS 0x8000
#define HRAM_START_MEMORY_ADDRESS 0xFF80

class RAM
{
    private:
        U8 WRAM[WRAM_SIZE];
        U8 VRAM[VRAM_SIZE];                          
        U8 HRAM[HRAM_SIZE];
    
    public:
        U8 WRAM_Read(U16 address);
        U8 HRAM_Read(U16 address);
        U8 VRAM_Read(U16 address);
        void WRAM_Write(U16 address, U8 value);
        void HRAM_Write(U16 address, U8 value);
        void VRAM_Write(U16 address, U8 value);
        void VRAM_Debug();
};

RAM * RAM_GetObj();