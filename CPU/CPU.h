#include "../General/General.h"

#define MECHANICAL_CYCLES_1 1
#define MECHANICAL_CYCLES_2 2
#define MECHANICAL_CYCLES_3 3
#define MECHANICAL_CYCLES_4 4
#define MECHANICAL_CYCLES_5 5
#define MECHANICAL_CYCLES_6 6
#define VBLANK_ADDRESS 0x40
#define LCD_STAT_ADDRESS 0x48
#define TIMER_ADDRESS 0x50
#define SERIAL_ADDRESS 0x58
#define JOYPAD_ADDRESS 0x60

enum FlagValue
{
    ResetFlag = 0,
    SetFlag = 1,
    NotSetFlag = 2 
};

union Cpu_Register
{
    struct
    {
        U8 lo; 
        U8 hi;
    } byte;
    U16 val;
};

class CPU
{
    private: 
        // Registers
        Cpu_Register AF;    //Accumulator & Flags
        Cpu_Register BC;    //BC
        Cpu_Register DE;    //DE
        Cpu_Register HL;    //HL
        U16 SP;             //Stack Pointer
        U16 PC;             //Program Counter
        
        U8 OpCode;          //Operation Code readed from Program Counter        
        U8 Cycles;          //Cycles of one instuction
        U32 AllCycles;      //Counter of CPU machine cycles
        bool Halt_active;    

        void CpuSetFlagZ(FlagValue opValue);
        void CpuSetFlagN(FlagValue opValue);
        void CpuSetFlagH(FlagValue opValue);
        void CpuSetFlagC(FlagValue opValue);

        void CpuExecute_CB_Instruction(U8 prefix);
        void CpuFetchOpCode();
        void CpuExecuteOpCode();
        void CpuBitTest(U8 bitNumber, U8 * reg);
        void CpuBitTest(U8 bitNumber, U16 address);
        void CpuBitReset(U8 bitNumber, U8 * reg);
        void CpuBitReset(U8 bitNumber, U16 address);
        void CpuBitSet(U8 bitNumber, U8 * reg);
        void CpuBitSet(U8 bitNumber, U16 address);
        void CpuIncCycle(U8 cycles);
        void CpuInstrutionRLC(U8 * value);
        void CpuInstrutionRRC(U8 * value);
        void CpuInstrutionRL(U8 * value);
        void CpuInstrutionRR(U8 * value);
        void CpuInstrutionSLA(U8 * value);
        void CpuInstrutionSLA(U16 address);
        void CpuInstrutionSRA(U8 * value);
        void CpuInstrutionSRL(U8 * value);
        void CpuInstrutionSWAP(U8 * value);
        void CpuInstructionINC_U8(U8 * req);
        void CpuInstructionDEC_U8(U8 * req);
        char * CpuConvertHex(U8 value);
        char * CpuConvertHexU16(U16 value);




    public:
        //CPU Construktor
        CPU();
        
        // CPU Tick Step
        void CpuStep();

        U8 CpuGetFlagZ();
        U8 CpuGetFlagN();
        U8 CpuGetFlagH();
        U8 CpuGetFlagC();
        U8 CpuGetCycles();
        U8 CpuGetA();
        U16 CpuGetBC();
        U16 CpuGetDE();
        U16 CpuGetHL();
        U16 CpuGetPC();
        U16 CpuGetSP();
        U8 CpuGetOpCode();
        U32 CpuGetAllCycles();
        void CpuPrepareIntterupt(U8 interruptMode);
        void CpuResetCycles();
        void CpuDebugPrint();
        void CpuDebugLogFilePrint();
};

/***************Interfaces******************/
void CpuInit();
CPU * CpuGetObj();