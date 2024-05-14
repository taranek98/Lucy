#include "RAM.h"
#include <iostream>

static RAM ram;

U8 RAM::WRAM_Read(U16 address)
{
    return WRAM[address - WRAM_START_MEMORY_ADDRESS];
}

U8 RAM::HRAM_Read(U16 address)
{
    return HRAM[address - HRAM_START_MEMORY_ADDRESS];
}

U8 RAM::VRAM_Read(U16 address)
{
    return VRAM[address - VRAM_START_MEMORY_ADDRESS];
}

void RAM::WRAM_Write(U16 address, U8 value)
{
    WRAM[address - WRAM_START_MEMORY_ADDRESS] = value;
}

void RAM::HRAM_Write(U16 address, U8 value)
{
    HRAM[address - HRAM_START_MEMORY_ADDRESS] = value;
}

void RAM::VRAM_Write(U16 address, U8 value)
{
    // std::cout<<"address: "<<address<<std::endl;
    VRAM[address - VRAM_START_MEMORY_ADDRESS] = value;
}

void RAM::VRAM_Debug()
{
    for(int j = 0; j < 1000; j++)
    {
        std::cout<<"Adress: ";
        std::cout.setf(std::ios::hex, std::ios::basefield);
        std::cout<<0x8000 + j;
        std::cout.setf(std::ios::dec, std::ios::basefield);
        std::cout<<" = "<<(U16)VRAM[j]<<std::endl;
    }
}

RAM *RAM_GetObj()
{
    return &ram;
}
