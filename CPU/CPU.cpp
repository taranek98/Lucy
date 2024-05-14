#include "CPU.h"
#include "../Bus/Bus.h"
#include <iostream>
#include "../Interrupt/Interrupt.h"
#include "../DB/dbg.h"
#include <fstream>
#include <string>
#include "../LCD/LCD.h"
static CPU * cpu;

using namespace std;
CPU :: CPU()
{
    AF.val = 0x01B0;
    BC.val = 0x0013;
    DE.val = 0x00D8;
    HL.val = 0x014D;
    SP = 0xFFFE;
    PC = 0x0100;
    OpCode = 0;
}

void CPU :: CpuStep()
{
    Cycles = 0;
    if(Halt_active == false)
    {
        CpuFetchOpCode();
        // dbg_update();
        // dbg_print();
        CpuExecuteOpCode();
        // if(SP == 0xDFF7)
        // {
        //     std::cout<<"(SP): "<<(U16)BusRead(SP)<<std::endl;
        // }
    }
    else
    {
        // std::cout<<"halt"<<std::endl;
        // std::cout<<"LY: "<<(U16)LcdGetObj() -> LcdGetLY()<<std::endl;
        // std::cout<<"LYC: "<<(U16)LcdGetObj() -> LcdGetLYC()<<std::endl;
        if(InterruptGetObj() -> InterruptIF_Read() != 0) /*TODO check this*/
        {
            std::cout<<"halt stop"<<std::endl;
            Halt_active = false;
        }
        CpuIncCycle(MECHANICAL_CYCLES_1);
    }
    
    AllCycles += Cycles;
}

void CPU :: CpuFetchOpCode()
{
    OpCode = BusRead(PC);
    /*Set PC to next instruction*/
    PC++;                   
}

void CPU::CpuSetFlagZ(FlagValue opValue)
{
    if(opValue == ResetFlag)
    {
        ResetBit(&AF.byte.lo, BIT_7);
    }
    else if(opValue == SetFlag)
    {
        SetBit(&AF.byte.lo, BIT_7);
    }
}

void CPU::CpuSetFlagN(FlagValue opValue)
{
    if(opValue == ResetFlag)
    {
        ResetBit(&AF.byte.lo, BIT_6);
    }
    else if(opValue == SetFlag)
    {
        SetBit(&AF.byte.lo, BIT_6);
    }
}

void CPU::CpuSetFlagH(FlagValue opValue)
{
    if(opValue == ResetFlag)
    {
        ResetBit(&AF.byte.lo, BIT_5);
    }
    else if(opValue == SetFlag)
    {
        SetBit(&AF.byte.lo, BIT_5);
    }
}

void CPU::CpuSetFlagC(FlagValue opValue)
{
    if(opValue == ResetFlag)
    {
        ResetBit(&AF.byte.lo, BIT_4);
    }
    else if(opValue == SetFlag)
    {
        SetBit(&AF.byte.lo, BIT_4);
    }
}

U8 CPU::CpuGetFlagZ()
{
    return GetBit(AF.byte.lo, BIT_7);
}

U8 CPU::CpuGetFlagN()
{
    return GetBit(AF.byte.lo, BIT_6);
}

U8 CPU::CpuGetFlagH()
{
    return GetBit(AF.byte.lo, BIT_5);
}

U8 CPU::CpuGetFlagC()
{
    return GetBit(AF.byte.lo, BIT_4);
}

U8 CPU::CpuGetCycles()
{
    return Cycles;
}

U32 CPU::CpuGetAllCycles()
{
    return AllCycles;;
}

void CPU::CpuPrepareIntterupt(U8 interruptMode)
{
    /*TODO: test it*/
    Halt_active = false;
    U8 lsb, msb;
    DivideValue(PC, &lsb, &msb);
    SP--;
    BusWrite(SP, msb);
    SP--;
    BusWrite(SP, lsb);
    // std::cout<<"interrupt Mode: "<<(U16)interruptMode<<std::endl;
    switch (interruptMode)
    {
        case VBLANK_INTERRUPT:
        {
            PC = VBLANK_ADDRESS;
            break;
        }

        case LCD_STAT_INTERRUPT:
        {
            PC = LCD_STAT_ADDRESS;
            break;
        }

        case TIMER_INTERRUPT:
        {
            PC = TIMER_ADDRESS;
            break;
        }

        case SERIAL_INTERRUPT:
        {
            PC = SERIAL_ADDRESS;
            break;
        }

        case JOYPAD_INTERRUPT:
        {
            PC = JOYPAD_ADDRESS;
            break;
        }
        default:
            std::cout<<"Unhandled Interrupt: "<<interruptMode<<std::endl;
            AbortProgram();
            break;
    }
}

void CPU::CpuResetCycles()
{
    AllCycles = 0;
}

void CPU::CpuDebugPrint() /*TODO: paste this to Debug module*/
{
    cout.setf(ios::hex, ios::basefield);
    cout<<"A: "<< (U16)AF.byte.hi <<" BC: "<<BC.val<<" DE: "<<DE.val<<" HL: "<<HL.val<<" SP: "<<SP<<" PC: "<<PC<<" OpCode: ";
    cout<<(U16)OpCode;
    cout<<" Flags: "<< (U16)AF.byte.lo<<std::endl;
    cout.setf(ios::dec, ios::basefield);
}

void CPU::CpuDebugLogFilePrint()
{
    fstream plik;
    plik.open("logfile.log", std::ios::out | ios::app);
    if(plik.good())
    {
        string s = "A:" + (string)CpuConvertHex(AF.byte.hi)
            + " F:" + (string)CpuConvertHex(AF.byte.lo)
            + " B:" + (string)CpuConvertHex(BC.byte.hi)
            + " C:" + (string)CpuConvertHex(BC.byte.lo)
            + " D:" + (string)CpuConvertHex(DE.byte.hi)
            + " E:" + (string)CpuConvertHex(DE.byte.lo)
            + " H:" + (string)CpuConvertHex(HL.byte.hi)
            + " L:" + (string)CpuConvertHex(HL.byte.lo)
            + " SP:" + (string)CpuConvertHexU16(SP)
            + " PC:" + (string)CpuConvertHexU16(PC)
            + " PCMEM:" + (string)CpuConvertHex(BusRead(PC)) 
            + "," + (string)CpuConvertHex(BusRead(PC+1)) 
            + "," + (string)CpuConvertHex(BusRead(PC+2)) 
            + "," + (string)CpuConvertHex(BusRead(PC+3));
        
        plik << s<< "\n";
    }
    plik.close();
}

void CPU::CpuBitTest(U8 bitNumber, U8 * reg)
{
    FlagValue z = ResetFlag;
    U8 bit = GetBit(*reg, bitNumber);

    if(bit == 0)
    {
        z = SetFlag;
    }

    CpuSetFlagZ(z);
    CpuSetFlagN(ResetFlag);
    CpuSetFlagH(SetFlag);
    CpuIncCycle(MECHANICAL_CYCLES_2);
}

void CPU::CpuBitTest(U8 bitNumber, U16 address)
{
    FlagValue z = ResetFlag;
    U8 value = BusRead(address);
    U8 bit = GetBit(value, bitNumber);

    if(bit == 0)
    {
        z = SetFlag;
    }

    CpuSetFlagZ(z);
    CpuSetFlagN(ResetFlag);
    CpuSetFlagH(SetFlag);
    CpuIncCycle(MECHANICAL_CYCLES_3);
}

void CPU::CpuBitReset(U8 bitNumber, U8 * reg)
{
    ResetBit(reg, bitNumber);
    CpuIncCycle(MECHANICAL_CYCLES_2);
}

void CPU::CpuBitReset(U8 bitNumber, U16 address)
{
    U8 value = BusRead(address);
    ResetBit(&value, bitNumber);
    BusWrite(address, value);
    CpuIncCycle(MECHANICAL_CYCLES_4);
}

void CPU::CpuBitSet(U8 bitNumber, U8 * reg)
{
    SetBit(reg, bitNumber);
    CpuIncCycle(MECHANICAL_CYCLES_2);
}

void CPU::CpuBitSet(U8 bitNumber, U16 address)
{
    U8 value = BusRead(address);
    SetBit(&value, bitNumber);
    BusWrite(address, value);
    CpuIncCycle(MECHANICAL_CYCLES_4);
}

void CPU::CpuIncCycle(U8 cycles)
{
    Cycles += cycles;
}

void CPU::CpuInstrutionRLC(U8 *value)
{
    FlagValue z = ResetFlag;
    FlagValue c = ResetFlag;
    U8 lastBit = GetBit(*value, BIT_7);
            
    ShiftLeft(value, 1);
    *value |= lastBit;
            
    /*Check Flag*/
    if(lastBit == 1)
    {
        c = SetFlag;
    }
    if(*value == 0)
    {
        z = SetFlag;
    }

    CpuSetFlagZ(z);
    CpuSetFlagN(ResetFlag);
    CpuSetFlagH(ResetFlag);
    CpuSetFlagC(c);
}

void CPU::CpuInstrutionRRC(U8 *value)
{
    FlagValue z = ResetFlag;
    FlagValue c = ResetFlag;
    U8 firstBit = GetBit(*value, BIT_0);

    ShiftRight(value, 1);
    *value |= ShiftLeft(firstBit, 7);

    /*Check Flag*/
    if(firstBit == 1)
    {
        c = SetFlag;
    }
    if(*value == 0)
    {
        z = SetFlag;
    }

    CpuSetFlagZ(z);
    CpuSetFlagN(ResetFlag);
    CpuSetFlagH(ResetFlag);
    CpuSetFlagC(c);
}

void CPU::CpuInstrutionRL(U8 *value)
{
    FlagValue z = ResetFlag;
    FlagValue c = ResetFlag;
    U8 lastBit = GetBit(*value, BIT_7);
    
    ShiftLeft(value, 1);
    *value |= (U8)CpuGetFlagC(); 
    
    /*Check Flag*/
    if(lastBit == 1)
    {
        c = SetFlag;
    }
    if(*value == 0)
    {
        z = SetFlag;
    }
    
    CpuSetFlagZ(z);
    CpuSetFlagN(ResetFlag);
    CpuSetFlagH(ResetFlag);
    CpuSetFlagC(c);
}

void CPU::CpuInstrutionRR(U8 *value)
{
    FlagValue z = ResetFlag;
    FlagValue c = ResetFlag;
    U8 firstBit = GetBit(*value,BIT_0);
    
    ShiftRight(value, 1);
    *value |= ShiftLeft((U8)CpuGetFlagC(), 7); 
    
    /*Check Flag*/
    if(firstBit == 1)
    {
        c = SetFlag;
    }
    if(*value == 0)
    {
        z = SetFlag;
    }
    CpuSetFlagZ(z);
    CpuSetFlagN(ResetFlag);
    CpuSetFlagH(ResetFlag);
    CpuSetFlagC(c);
}

void CPU::CpuInstrutionSLA(U8 *value)
{
    FlagValue z = ResetFlag;
    FlagValue c = ResetFlag;
    U8 lastBit = GetBit(*value, BIT_7);
    
    ShiftLeft(value, 1);
    
    /*Check Flag*/
    if(lastBit == 1)
    {
        c = SetFlag;
    }
    if(*value == 0)
    {
        z = SetFlag;
    }
    
    CpuSetFlagZ(z);
    CpuSetFlagN(ResetFlag);
    CpuSetFlagH(ResetFlag);
    CpuSetFlagC(c);
}

void CPU::CpuInstrutionSLA(U16 address)
{
    U8 value = BusRead(address);
    FlagValue z = ResetFlag;
    FlagValue c = ResetFlag;
    U8 lastBit = GetBit(value, BIT_7);
    
    ShiftLeft(&value, 1);
    
    /*Check Flag*/
    if(lastBit == 1)
    {
        c = SetFlag;
    }
    if(value == 0)
    {
        z = SetFlag;
    }

    BusWrite(address, value);
    
    CpuSetFlagZ(z);
    CpuSetFlagN(ResetFlag);
    CpuSetFlagH(ResetFlag);
    CpuSetFlagC(c);
}

void CPU::CpuInstrutionSRA(U8 *value)
{
    FlagValue z = ResetFlag;
    FlagValue c = ResetFlag;
    U8 lastBit = GetBit(*value, BIT_7);
    U8 firstBit = GetBit(*value, BIT_0);
    
    ShiftRight(value, 1);
    *value |= ShiftLeft(lastBit, 7);
    
    /*Check Flag*/
    if(firstBit == 1)
    {
        c = SetFlag;
    }
    if(*value == 0)
    {
        z = SetFlag;
    }
    
    CpuSetFlagZ(z);
    CpuSetFlagN(ResetFlag);
    CpuSetFlagH(ResetFlag);
    CpuSetFlagC(c);
}

void CPU::CpuInstrutionSRL(U8 *value)
{
    FlagValue z = ResetFlag;
    FlagValue c = ResetFlag;
    U8 firstBit = GetBit(*value, BIT_0);
    
    ShiftRight(value, 1);
    
    /*Check Flag*/
    if(firstBit == 1)
    {
        c = SetFlag;
    }
    if(*value == 0)
    {
        z = SetFlag;
    }
    
    CpuSetFlagZ(z);
    CpuSetFlagN(ResetFlag);
    CpuSetFlagH(ResetFlag);
    CpuSetFlagC(c);
}

void CPU::CpuInstrutionSWAP(U8 *value)
{
    FlagValue z = ResetFlag;
    U8 lsb, msb;
    DivideValue(*value, &lsb, &msb);
    
    *value = ShiftLeft(lsb, 4) | ShiftRight(msb, 4);
    
    /*Check flag*/
    if(*value == 0)
    {
        z = SetFlag;
    }
    
    CpuSetFlagZ(z);
    CpuSetFlagN(ResetFlag);
    CpuSetFlagH(ResetFlag);
    CpuSetFlagC(ResetFlag);   
}

void CPU::CpuInstructionINC_U8(U8 * req)
{
    FlagValue z = ResetFlag;
    FlagValue h = ResetFlag;
    (*req)++;
    CpuIncCycle(MECHANICAL_CYCLES_1);
            
    /*Check Z flag*/
    if(*req == 0)
    {
        z = SetFlag;
    }
    /*Check H flag*/
    if((*req & 0x0F) == 0 )
    {
        h = SetFlag;
    }

    CpuSetFlagZ(z);
    CpuSetFlagH(h);
    CpuSetFlagN(ResetFlag);
}

void CPU::CpuInstructionDEC_U8(U8 * req)
{
    FlagValue z = ResetFlag;
    FlagValue h = ResetFlag;
    (*req)--;
    CpuIncCycle(MECHANICAL_CYCLES_1);
            
    /*Check Z flag*/
    if(*req == 0)
    {
        z = SetFlag;
    }
    /*Check H flag*/
    if((*req & 0x0F) == 0x0F)
    {
        h = SetFlag;
    }

    CpuSetFlagZ(z);
    CpuSetFlagH(h);
    CpuSetFlagN(SetFlag);
}

char * CPU::CpuConvertHex(U8 value)
{
    char hexChar [] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    static char  valueReturnU8[] = "FF";
    valueReturnU8[0] = hexChar[(value & 0xF0) >> 4];
    valueReturnU8[1] = hexChar[value & 0x0F];
    return valueReturnU8;
}

char *CPU::CpuConvertHexU16(U16 value)
{
    static char  valueReturnU16 [] ="FFFF";
    char hexChar [] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    valueReturnU16[0] = hexChar[(value & 0xF000) >> 12];
    valueReturnU16[1] = hexChar[(value & 0x0F00) >> 8];
    valueReturnU16[2] = hexChar[(value & 0x00F0) >> 4];
    valueReturnU16[3] = hexChar[value & 0x000F];
    return valueReturnU16;
}

U8 CPU::CpuGetA()
{
    return AF.byte.hi;
}
U16 CPU::CpuGetBC()
{
    return BC.val;
}
U16 CPU::CpuGetDE()
{
    return DE.val;
}
U16 CPU::CpuGetHL()
{
    return HL.val;
}
U16 CPU::CpuGetPC()
{
    return PC;
}
U16 CPU::CpuGetSP()
{
    return SP;
}
U8 CPU::CpuGetOpCode()
{
    return OpCode;
}

/***************Interfaces******************/
void CpuInit()
{
    cpu = new CPU();
}

CPU * CpuGetObj()
{
    return cpu;
}

