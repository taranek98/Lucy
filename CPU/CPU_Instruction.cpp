#include "CPU.h"
#include "CPU_Instruction.h"
#include "../Bus/Bus.h"
#include "../Interrupt/Interrupt.h"
#include <iostream>

void CPU :: CpuExecuteOpCode()
{
    switch (OpCode)
    {
        /*Cpu Control Operations*/
        case NOP:
        {
            /*Do nothing*/
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case STOP:
        {
            //TODO Implement shout down console
            std::cout<<"STOP Instuction"<<std::endl;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case HALT:
        {
            Halt_active = true;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            std::cout<<"HALT Instuction"<<std::endl;
            break;
        }

        case CCF:
        {
            FlagValue c = ResetFlag;

            if(CpuGetFlagC() == ResetFlag)
            {
                c = SetFlag;
            }
            
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(c);
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case SCF:
        {
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(SetFlag);
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        /*Load operations 8bit*/
        case LD_A_A:
        {
            AF.byte.hi = AF.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }
        case LD_A_B:
        {
            AF.byte.hi = BC.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_A_C:
        {
            AF.byte.hi = BC.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_A_D:
        {
            AF.byte.hi = DE.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_A_E:
        {
            AF.byte.hi = DE.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_A_H:
        {
            AF.byte.hi = HL.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_A_L:
        {
            AF.byte.hi = HL.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }
        
        case LD_B_A:
        {
            BC.byte.hi = AF.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_B_B:
        {
            BC.byte.hi = BC.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_B_C:
        {
            BC.byte.hi = BC.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }
        case LD_B_D:
        {
            BC.byte.hi = DE.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_B_E:
        {
            BC.byte.hi = DE.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_B_H:
        {
            BC.byte.hi = HL.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }
        
        case LD_B_L:
        {
            BC.byte.hi = HL.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_C_A:
        {
            BC.byte.lo = AF.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_C_B:
        {
            BC.byte.lo = BC.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_C_C:
        {
            BC.byte.lo = BC.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_C_D:
        {
            BC.byte.lo = DE.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_C_E:
        {
            BC.byte.lo = DE.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_C_H:
        {
            BC.byte.lo = HL.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_C_L:
        {
            BC.byte.lo = HL.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_D_A:
        {
            DE.byte.hi = AF.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_D_B:
        {
            DE.byte.hi = BC.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_D_C:
        {
            DE.byte.hi = BC.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_D_D:
        {
            DE.byte.hi = DE.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_D_E:
        {
            DE.byte.hi = DE.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_D_H:
        {
            DE.byte.hi = HL.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_D_L:
        {
            DE.byte.hi = HL.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_E_A:
        {
            DE.byte.lo = AF.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_E_B:
        {
            DE.byte.lo = BC.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_E_C:
        {
            DE.byte.lo = BC.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_E_D:
        {
            DE.byte.lo = DE.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_E_E:
        {
            DE.byte.lo = DE.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_E_H:
        {
            DE.byte.lo = HL.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_E_L:
        {
            DE.byte.lo = HL.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_H_A:
        {
            HL.byte.hi = AF.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_H_B:
        {
            HL.byte.hi = BC.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_H_C:
        {
            HL.byte.hi = BC.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_H_D:
        {
            HL.byte.hi = DE.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_H_E:
        {
            HL.byte.hi = DE.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_H_H:
        {
            HL.byte.hi = HL.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_H_L:
        {
            HL.byte.hi = HL.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_L_A:
        {
            HL.byte.lo = AF.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_L_B:
        {
            HL.byte.lo = BC.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_L_C:
        {
            HL.byte.lo = BC.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_L_D:
        {
            HL.byte.lo = DE.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_L_E:
        {
            HL.byte.lo = DE.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_L_H:
        {
            HL.byte.lo = HL.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_L_L:
        {
            HL.byte.lo = HL.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case LD_A_n:
        {
            U8 n = BusRead(PC);
            PC++;
            AF.byte.hi = n;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case LD_B_n:
        {
            U8 n = BusRead(PC);
            PC++;
            BC.byte.hi = n;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case LD_C_n:
        {
            U8 n = BusRead(PC);
            PC++;
            BC.byte.lo = n;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }
        
        case LD_D_n:
        {
            U8 n = BusRead(PC);
            PC++;
            DE.byte.hi = n;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case LD_E_n:
        {
            U8 n = BusRead(PC);
            PC++;
            DE.byte.lo = n;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case LD_H_n:
        {
            U8 n = BusRead(PC);
            PC++;
            HL.byte.hi = n;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case LD_L_n:
        {
            U8 n = BusRead(PC);
            PC++;
            HL.byte.lo = n;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case LD_adr_BC_A:
        {
            BusWrite(BC.val, AF.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case LD_adr_DE_A:
        {
            BusWrite(DE.val, AF.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case LD_A_adr_BC:
        {
            U8 value = BusRead(BC.val);
            AF.byte.hi = value;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case LD_A_adr_DE:
        {
            U8 value = BusRead(DE.val);
            AF.byte.hi = value;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case LD_A_adr_HL:
        {
            U8 value = BusRead(HL.val);
            AF.byte.hi = value;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break; 
        }

        case LD_B_adr_HL:
        {
            U8 value = BusRead(HL.val);
            BC.byte.hi = value;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break; 
        }

        case LD_C_adr_HL:
        {
            U8 value = BusRead(HL.val);
            BC.byte.lo = value;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break; 
        }

        case LD_D_adr_HL:
        {
            U8 value = BusRead(HL.val);
            DE.byte.hi = value;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break; 
        }

        case LD_E_adr_HL:
        {
            U8 value = BusRead(HL.val);
            DE.byte.lo = value;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break; 
        }

        case LD_H_adr_HL:
        {
            U8 value = BusRead(HL.val);
            HL.byte.hi = value;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break; 
        }

        case LD_L_adr_HL:
        {
            U8 value = BusRead(HL.val);
            HL.byte.lo = value;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break; 
        }

        case LD_adr_HL_A:
        {
            BusWrite(HL.val, AF.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case LD_adr_HL_B:
        {
            BusWrite(HL.val, BC.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }
        case LD_adr_HL_C:
        {
            BusWrite(HL.val, BC.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }
        case LD_adr_HL_D:
        {
            BusWrite(HL.val, DE.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }
        case LD_adr_HL_E:
        {
            BusWrite(HL.val, DE.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }
        case LD_adr_HL_H:
        {
            BusWrite(HL.val, HL.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }
        case LD_adr_HL_L:
        {
            BusWrite(HL.val, HL.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case LD_adr_HL_n:
        {
            U8 value;
            value = BusRead(PC);
            PC++;
            BusWrite(HL.val, value);
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break;                
        }

        case LDI_adr_HL_A:
        {
            BusWrite(HL.val, AF.byte.hi);
            HL.val++;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case LDD_adr_HL_A:
        {
            BusWrite(HL.val, AF.byte.hi);
            HL.val--;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case LDD_A_adr_HL:
        {
            U8 value = BusRead(HL.val);
            AF.byte.hi = value;
            HL.val--;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case LDI_A_adr_HL:
        {
            U8 value = BusRead(HL.val);
            AF.byte.hi = value;
            HL.val++;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break; 
        }

        case LD_A_adr_nn:
        {
            U8 nnLSB, nnMSB;
            nnLSB = BusRead(PC);
            PC++;
            nnMSB = BusRead(PC);
            PC++;
            AF.byte.hi = BusRead(MergeValues(nnMSB, nnLSB));
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        case LD_adr_nn_A:
        {
            U8 nnLSB, nnMSB;
            nnLSB = BusRead(PC);
            PC++;
            nnMSB = BusRead(PC);
            PC++;
            BusWrite((U16)((nnMSB<<8)|nnLSB), AF.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }
        
        case LDH_adr_n_A:
        {
            U8 n;
            n = BusRead(PC);
            PC++;
            BusWrite(0xFF00 + (U16)n, AF.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break;
        }

        case LDH_A_adr_n:
        {
            U8 n;
            n = BusRead(PC);
            // std::cout<<"IF: "<<(U16)InterruptGetObj()->InterruptGetIF()<<std::endl;
            PC++;
            AF.byte.hi = BusRead(0xFF00 + (U16)n);
            CpuIncCycle(MECHANICAL_CYCLES_3);
            // CpuDebugPrint();
            break;
        }

        case LDH_adr_C_A:
        {
            BusWrite(0xFF00 + (U16)BC.byte.lo, AF.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case LDH_A_adr_C:
        {
            AF.byte.hi = BusRead(0xFF00 + (U16)BC.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        /*Load operations 16bit*/
        case LD_BC_nn: 
        {
            U8 lsb = BusRead(PC);
            PC++;
            U8 msb = BusRead(PC);
            PC++;
            BC.val = MergeValues(msb, lsb);
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break;
        }

        case LD_DE_nn:
        {
            U8 nnLSB, nnMSB;
            nnLSB = BusRead(PC);
            PC++;
            nnMSB = BusRead(PC);
            PC++;
            DE.val = MergeValues(nnMSB, nnLSB);
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break;
        }

        case LD_HL_nn:
        {
            U8 nnLSB, nnMSB;
            nnLSB = BusRead(PC);
            PC++;
            nnMSB = BusRead(PC);
            PC++;
            HL.val = MergeValues(nnMSB, nnLSB);
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break;
        }

        case LD_SP_nn:
        {
            U8 nnLSB, nnMSB;
            nnLSB = BusRead(PC);
            PC++;
            nnMSB = BusRead(PC);
            PC++;
            SP = MergeValues(nnMSB, nnLSB);
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break;
        }
        
        case LD_adr_nn_SP:
        {
            /*TODO: Create STACK class and implemented*/
            U8 nnLSB, nnMSB;
            U8 spLSB = SP & 0x00FF;
            U8 spMSB = (SP & 0xFF00) >> 8;
            U16 nn;

            nnLSB = BusRead(PC);
            PC++;
            nnMSB = BusRead(PC);
            PC++;
            nn = MergeValues(nnMSB, nnLSB);
            BusWrite(nn,spLSB);
            nn++;
            BusWrite(nn,spMSB);
            CpuIncCycle(MECHANICAL_CYCLES_5);
            
            break;
        }

        case LD_SP_HL:
        {
            SP = HL.val;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case LD_HL_SP_plus_e:
        {
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;
            S8 e;
            e = (S8)BusRead(PC);
            PC++;
            HL.val = SP + e;
            CpuIncCycle(MECHANICAL_CYCLES_3);
            
            /*16bit register ALU add speraletly 8bit data of 16bit value what cause H and C flag are set by low byte*/
            /*Check H flag*/
            if(((SP & 0x000F) + ((U8)e & 0x0F)) > 0x000F)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(((SP & 0x00FF) + (U8)e) > 0x00FF)
            {
                c = SetFlag;
            }
            
            CpuSetFlagZ(ResetFlag);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }
        /*POP information*/
        case POP_AF:
        {
            U8 lsb, msb;
            lsb = BusRead(SP);
            lsb &= 0xF0; /*LSB of Flag register can not be written*/
            SP++;
            msb = BusRead(SP);
            SP++;
            AF.val = MergeValues(msb, lsb);
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break;
        }

        case POP_BC:
        {
            U8 lsb, msb;
            lsb = BusRead(SP);
            SP++;
            msb = BusRead(SP);
            SP++;
            BC.val = MergeValues(msb, lsb);
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break;
        }

        case POP_DE:
        {
            U8 lsb, msb;
            lsb = BusRead(SP);
            SP++;
            msb = BusRead(SP);
            SP++;
            DE.val = MergeValues(msb, lsb);
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break;
        }

        case POP_HL:
        {
            U8 lsb, msb;
            lsb = BusRead(SP);
            SP++;
            msb = BusRead(SP);
            SP++;
            HL.val = MergeValues(msb, lsb);
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break;
        }

        /*Incrementation operations 16bit*/
        case INC_BC:
        {
            BC.val++;    
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;       
        }

        case INC_DE:
        {
            DE.val++;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case INC_HL:
        {
            HL.val++;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case INC_SP:
        {
            SP++;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        /*Incrementation operations 8bit*/
        case INC_A:
        {
            CpuInstructionINC_U8(&AF.byte.hi);
            break;
        }
        case INC_B:
        {
            CpuInstructionINC_U8(&BC.byte.hi);
            break;
        }

        case INC_C:
        {
            CpuInstructionINC_U8(&BC.byte.lo);
            break;
        }

        case INC_D:
        {
            CpuInstructionINC_U8(&DE.byte.hi);
            break;
        }

        case INC_E:
        {
            CpuInstructionINC_U8(&DE.byte.lo);
            break;
        }

        case INC_H:
        {
            CpuInstructionINC_U8(&HL.byte.hi);
            break;
        }

        case INC_L:
        {
            CpuInstructionINC_U8(&HL.byte.lo);
            break;
        }

        case INC_adr_HL:
        {
            U8 value = BusRead(HL.val);
            CpuInstructionINC_U8(&value);
            BusWrite(HL.val, value);
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break;
        }
        /*Decrementation operations 16bit*/
        case DEC_BC:
        {
            BC.val--;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case DEC_DE:
        {
            DE.val--;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case DEC_HL:
        {
            HL.val--;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case DEC_SP:
        {
            SP--;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        /*Decrementation operations 8bit*/
        case DEC_A:
        {
            CpuInstructionDEC_U8(&AF.byte.hi);
            break;           
        }
        case DEC_B:
        {
            CpuInstructionDEC_U8(&BC.byte.hi);
            break;           
        }

        case DEC_C:
        {
            CpuInstructionDEC_U8(&BC.byte.lo);
            break;
        }

        case DEC_D:
        {
            CpuInstructionDEC_U8(&DE.byte.hi);
            break;
        }

        case DEC_E:
        {
            CpuInstructionDEC_U8(&DE.byte.lo);
            break;
        }

        case DEC_H:
        {
            CpuInstructionDEC_U8(&HL.byte.hi);
            break;
        }

        case DEC_L:
        {
            CpuInstructionDEC_U8(&HL.byte.lo);
            break;
        }

        case DEC_adr_HL:
        {
            U8 value = BusRead(HL.val);
            CpuInstructionDEC_U8(&value);
            BusWrite(HL.val, value);
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break;
        }

        /*Rotate operation*/
        case RLCA:
        {
            FlagValue c = ResetFlag;
            U8 lastBit = GetBit(AF.byte.hi, BIT_7); 
            AF.byte.hi = ShiftLeft(AF.byte.hi, 1); 
            AF.byte.hi |= lastBit;
            
            /*Check C flag*/
            if(lastBit == 1)
            {
                c = SetFlag;
            }

            CpuSetFlagZ(ResetFlag);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(c);
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case RRCA:
        {
            FlagValue c = ResetFlag;
            U8 firstBit = GetBit(AF.byte.hi, BIT_0);
            AF.byte.hi = ShiftRight(AF.byte.hi, 1);
            AF.byte.hi |= ShiftLeft(firstBit, 7);

            /*Check C flag*/
            if(firstBit == 1)
            {
                c = SetFlag;
            }

            CpuSetFlagZ(ResetFlag);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(c);
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case RLA:
        {
            FlagValue c = ResetFlag;
            U8 lastBit = GetBit(AF.byte.hi, BIT_7);
            AF.byte.hi = ShiftLeft(AF.byte.hi, 1);
            AF.byte.hi |= CpuGetFlagC();

            /*Check C flag*/
            if(lastBit == 1)
            {
                c = SetFlag;
            }

            CpuSetFlagZ(ResetFlag);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(c);
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case RRA:
        {
            FlagValue c = ResetFlag;
            U8 firstBit = GetBit(AF.byte.hi, BIT_0);
            AF.byte.hi = ShiftRight(AF.byte.hi, 1);
            AF.byte.hi |= ShiftLeft(CpuGetFlagC(), 7);

            /*Check C flag*/
            if(firstBit == 1)
            {
                c = SetFlag;
            }

            CpuSetFlagZ(ResetFlag);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(c);
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case CB_op:
        {
            U8 prefix = BusRead(PC);
            PC++;
            // std::cout<<"CB prefix: "<<(U16)prefix<<std::endl;
            CpuExecute_CB_Instruction(prefix);
            break;
        }

        /*Addition operations 8bit*/
        case ADD_n:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;
            U8 n;
            n = BusRead(PC);
            PC++;
            /*Check H flag*/
            if((AF.byte.hi & 0x0F) + (n & 0x0F) > 0x0F)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi + n > 0xFF)
            {
                c = SetFlag;
            }

            AF.byte.hi += n;

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case ADD_A:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           

            /*Check H flag*/
            if((AF.byte.hi & 0x0F) + (AF.byte.hi & 0x0F) > 0x0F)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi + AF.byte.hi > 0xFF)
            {
                c = SetFlag;
            }

            AF.byte.hi += AF.byte.hi;

             /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case ADD_B:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           


            /*Check H flag*/
            if((AF.byte.hi & 0x0F) + (BC.byte.hi & 0x0F) > 0x0F)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi + BC.byte.hi > 0xFF)
            {
                c = SetFlag;
            }

            AF.byte.hi += BC.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case ADD_C:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           


            /*Check H flag*/
            if((AF.byte.hi & 0x0F) + (BC.byte.lo & 0x0F)  > 0x0F)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi + BC.byte.lo > 0xFF)
            {
                c = SetFlag;
            }

            AF.byte.hi += BC.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;

        }

        case ADD_D:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           


            /*Check H flag*/
            if((AF.byte.hi & 0x0F) + (DE.byte.hi & 0x0F) > 0x0F)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi + DE.byte.hi > 0xFF)
            {
                c = SetFlag;
            }

            AF.byte.hi += DE.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;

        }

        case ADD_E:
        {

            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           

            /*Check H flag*/
            if((AF.byte.hi & 0x0F) + (DE.byte.lo & 0x0F) > 0x0F)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi + DE.byte.lo > 0xFF)
            {
                c = SetFlag;
            }

            AF.byte.hi += DE.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;

        }

        case ADD_H:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           

            /*Check H flag*/
            if((AF.byte.hi & 0x0F) + (HL.byte.hi & 0x0F) > 0x0F)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi + HL.byte.hi > 0xFF)
            {
                c = SetFlag;
            }

            AF.byte.hi += HL.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;

        }

        case ADD_L:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           

            /*Check H flag*/
            if((AF.byte.hi & 0x0F) + (HL.byte.lo & 0x0F) > 0x0F)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi + HL.byte.lo > 0xFF)
            {
                c = SetFlag;
            }

            AF.byte.hi += HL.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case ADD_adr_HL:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           
            U8 value = BusRead(HL.val);


            /*Check H flag*/
            if((AF.byte.hi & 0x0F) + (value & 0x0F) > 0x0F)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi + value > 0xFF)
            {
                c = SetFlag;
            }

            AF.byte.hi += value;
            CpuIncCycle(MECHANICAL_CYCLES_2);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case ADC_n:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag; 
            U8 n;
            n = BusRead(PC);
            PC++;
            
            /*Check H flag*/
            if((AF.byte.hi & 0x0F) + ((n & 0x0F) + CpuGetFlagC()) > 0x0F)
            {
                h = SetFlag;
            }
            /*Check H flag*/
            if(AF.byte.hi + (n + (U8)CpuGetFlagC()) > 0xFF)
            {
                c = SetFlag;
            }
            AF.byte.hi += (n + (U8)CpuGetFlagC());

            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case ADC_A:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag; 
            
            /*Check H flag*/
            if((AF.byte.hi & 0x0F) + ((AF.byte.hi & 0x0F) + (U8)CpuGetFlagC()) > 0x0F)
            {
                h = SetFlag;
            }
            /*Check H flag*/
            if(AF.byte.hi + (AF.byte.hi + (U8)CpuGetFlagC()) > 0xFF)
            {
                c = SetFlag;
            }
            AF.byte.hi += AF.byte.hi + (U8)CpuGetFlagC();
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case ADC_B:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag; 
            
            /*Check H flag*/
            if((AF.byte.hi & 0x0F) + ((BC.byte.hi & 0x0F) + (U8)CpuGetFlagC()) > 0x0F)
            {
                h = SetFlag;
            }
            /*Check H flag*/
            if(AF.byte.hi + (BC.byte.hi + (U8)CpuGetFlagC()) > 0xFF)
            {
                c = SetFlag;
            }
            AF.byte.hi += BC.byte.hi + (U8)CpuGetFlagC();
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case ADC_C:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag; 
            
            /*Check H flag*/
            if((AF.byte.hi & 0x0F) + ((BC.byte.lo & 0x0F) + (U8)CpuGetFlagC()) > 0x0F)
            {
                h = SetFlag;
            }
            /*Check H flag*/
            if(AF.byte.hi + (BC.byte.lo + (U8)CpuGetFlagC()) > 0xFF)
            {
                c = SetFlag;
            }
            AF.byte.hi += BC.byte.lo + (U8)CpuGetFlagC();
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case ADC_D:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag; 
            
            /*Check H flag*/
            if((AF.byte.hi & 0x0F) + ((DE.byte.hi & 0x0F) + (U8)CpuGetFlagC()) > 0x0F)
            {
                h = SetFlag;
            }
            /*Check H flag*/
            if(AF.byte.hi + (DE.byte.hi + (U8)CpuGetFlagC()) > 0xFF)
            {
                c = SetFlag;
            }
            AF.byte.hi += DE.byte.hi + (U8)CpuGetFlagC();
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case ADC_E:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag; 
            
            /*Check H flag*/
            if((AF.byte.hi & 0x0F) + ((DE.byte.lo & 0x0F) + (U8)CpuGetFlagC()) > 0x0F)
            {
                h = SetFlag;
            }
            /*Check H flag*/
            if(AF.byte.hi + (DE.byte.lo + (U8)CpuGetFlagC()) > 0xFF)
            {
                c = SetFlag;
            }
            AF.byte.hi += DE.byte.lo + (U8)CpuGetFlagC();
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case ADC_H:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag; 
            
            /*Check H flag*/
            if((AF.byte.hi & 0x0F) + ((HL.byte.hi & 0x0F) + (U8)CpuGetFlagC()) > 0x0F)
            {
                h = SetFlag;
            }
            /*Check H flag*/
            if(AF.byte.hi + (HL.byte.hi + (U8)CpuGetFlagC()) > 0xFF)
            {
                c = SetFlag;
            }
            AF.byte.hi += HL.byte.hi + (U8)CpuGetFlagC();
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case ADC_L:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag; 
            
            /*Check H flag*/
            if((AF.byte.hi & 0x0F) + ((HL.byte.lo & 0x0F) + (U8)CpuGetFlagC()) > 0x0F)
            {
                h = SetFlag;
            }
            /*Check H flag*/
            if(AF.byte.hi + (HL.byte.lo + (U8)CpuGetFlagC()) > 0xFF)
            {
                c = SetFlag;
            }
            AF.byte.hi += HL.byte.lo + (U8)CpuGetFlagC();
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case ADC_adr_HL:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag; 
            U8 value = BusRead(HL.val);
            
            /*Check H flag*/
            if((AF.byte.hi & 0x0F) + ((value & 0x0F) + (U8)CpuGetFlagC()) > 0x0F)
            {
                h = SetFlag;
            }
            /*Check H flag*/
            if(AF.byte.hi + (value + (U8)CpuGetFlagC()) > 0xFF)
            {
                c = SetFlag;
            }
            AF.byte.hi += value + (U8)CpuGetFlagC();
            CpuIncCycle(MECHANICAL_CYCLES_2);

            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }
        
        /*Addition operations 16bit*/
        case ADD_HL_BC:
        {
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;
            
            /*Check h flag*/
            if(((HL.val & 0x0FFF) + (BC.val & 0x0FFF)) > 0x0FFF)
            {
                h = SetFlag;
            } 

            /*Check c flag*/
            if(HL.val + BC.val > 0xFFFF)
            {
                c = SetFlag;
            }
            
            HL.val += BC.val;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case ADD_HL_DE:
        {
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;
            
            /*Check h flag*/
            if(((HL.val & 0x0FFF) + (DE.val & 0x0FFF)) > 0x0FFF)
            {
                h = SetFlag;
            } 
            /*Check c flag*/
            if((HL.val + DE.val) > 0xFFFF)
            {
                c = SetFlag;
            }
            
            HL.val += DE.val;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case ADD_HL_HL:
        {
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;
            
            /*Check h flag*/
            if(((HL.val & 0x0FFF) + (HL.val & 0x0FFF)) > 0x0FFF)
            {
                h = SetFlag;
            } 
            /*Check c flag*/
            if(HL.val + HL.val > 0xFFFF)
            {
                c = SetFlag;
            }
            
            HL.val += HL.val;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case ADD_HL_SP:
        {
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;
            
            /*Check h flag*/
            if(((HL.val & 0x0FFF) + (SP & 0x0FFF)) > 0x0FFF)
            {
                h = SetFlag;
            } 
            /*Check c flag*/
            if(HL.val + SP > 0xFFFF)
            {
                c = SetFlag;
            }
            
            HL.val += SP;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case ADD_SP_e:
        {
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;
            S8 e = (S8)BusRead(PC);
            PC++;
            
            /*16bit register ALU add speraletly 8bit data of 16bit value what cause H and C flag are set by low byte*/
            /*Check h flag*/
            if(((SP & 0x000F) + ((U8)e & 0x0F) ) > 0x000F)
            {
                h = SetFlag;
            } 
            /*Check c flag*/
            if(((SP & 0x00FF) + (U8)e) > 0x00FF)
            {
                c = SetFlag;
            }
            
            SP += e;
            CpuIncCycle(MECHANICAL_CYCLES_4);
            
            CpuSetFlagZ(ResetFlag);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);

            break;
        }


        /*Subtraction operations 8bit*/
        case SUB_n:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;      
            U8 n;
            n = BusRead(PC);     
            PC++;

            /*Check H flag*/ 
            if((AF.byte.hi & 0x0F) - (n & 0x0F) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if((AF.byte.hi - n) < 0x00)
            {
                c = SetFlag;
            }

            AF.byte.hi -= n;

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SUB_A:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           

            /*Check H flag*/ 
            if((AF.byte.hi & 0x0F) - (AF.byte.hi & 0x0F) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi - AF.byte.hi < 0x00)
            {
                c = SetFlag;
            }

            AF.byte.hi -= AF.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case SUB_B:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           

            /*Check H flag*/ 
            if((AF.byte.hi & 0x0F) - (BC.byte.hi & 0x0F) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi - BC.byte.hi < 0x00)
            {
                c = SetFlag;
            }

            AF.byte.hi -= BC.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case SUB_C:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           

            /*Check H flag*/ 
            if((AF.byte.hi & 0x0F) - (BC.byte.lo & 0x0F) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi - BC.byte.lo < 0x00)
            {
                c = SetFlag;
            }

            AF.byte.hi -= BC.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case SUB_D:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           

            /*Check H flag*/ 
            if((AF.byte.hi & 0x0F) - (DE.byte.hi & 0x0F) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi - DE.byte.hi < 0x00)
            {
                c = SetFlag;
            }

            AF.byte.hi -= DE.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case SUB_E:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           

            /*Check H flag*/ 
            if((AF.byte.hi & 0x0F) - (DE.byte.lo & 0x0F) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi - DE.byte.lo < 0x00)
            {
                c = SetFlag;
            }

            AF.byte.hi -= DE.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case SUB_H:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           

            /*Check H flag*/ 
            if((AF.byte.hi & 0x0F) - (HL.byte.hi & 0x0F) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi - HL.byte.hi < 0x00)
            {
                c = SetFlag;
            }

            AF.byte.hi -= HL.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case SUB_L:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           

            /*Check H flag*/ 
            if((AF.byte.hi & 0x0F) - (HL.byte.lo & 0x0F) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi - HL.byte.lo < 0x00)
            {
                c = SetFlag;
            }

            AF.byte.hi -= HL.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case SUB_adr_HL:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           
            U8 value = BusRead(HL.val);

            /*Check H flag*/ 
            if((AF.byte.hi & 0x0F) - (value & 0x0F) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi - value < 0x00)
            {
                c = SetFlag;
            }

            AF.byte.hi -= value;
            CpuIncCycle(MECHANICAL_CYCLES_2);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case SBC_n:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;   
            U8 n;
            n = BusRead(PC);        
            PC++;

            /*Check H flag*/ 
            if((AF.byte.hi & 0x0F) - ((n & 0x0F) + (U8)CpuGetFlagC()) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi - (n + (U8)CpuGetFlagC()) < 0x00)
            {
                c = SetFlag;
            }

            AF.byte.hi -= n + (U8)CpuGetFlagC();
            CpuIncCycle(MECHANICAL_CYCLES_2);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case SBC_A:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           

            /*Check H flag*/ 
            if((AF.byte.hi & 0x0F) - ((AF.byte.hi & 0x0F) + (U8)CpuGetFlagC()) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi - (AF.byte.hi + (U8)CpuGetFlagC()) < 0x00)
            {
                c = SetFlag;
            }

            AF.byte.hi -= AF.byte.hi + (U8)CpuGetFlagC();
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case SBC_B:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           

            /*Check H flag*/ 
            if((AF.byte.hi & 0x0F) - ((BC.byte.hi & 0x0F) + (U8)CpuGetFlagC()) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi - (BC.byte.hi + (U8)CpuGetFlagC()) < 0x00)
            {
                c = SetFlag;
            }

            AF.byte.hi -= BC.byte.hi + (U8)CpuGetFlagC();
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case SBC_C:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           

            /*Check H flag*/ 
            if((AF.byte.hi & 0x0F) - ((BC.byte.lo & 0x0F) + (U8)CpuGetFlagC()) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi - (BC.byte.lo + (U8)CpuGetFlagC()) < 0x00)
            {
                c = SetFlag;
            }

            AF.byte.hi -= BC.byte.lo + (U8)CpuGetFlagC();
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case SBC_D:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           

            /*Check H flag*/ 
            if((AF.byte.hi & 0x0F) - ((DE.byte.hi & 0x0F) + (U8)CpuGetFlagC()) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi - (DE.byte.hi + (U8)CpuGetFlagC()) < 0x00)
            {
                c = SetFlag;
            }

            AF.byte.hi -= DE.byte.hi + (U8)CpuGetFlagC();
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case SBC_E:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           

            /*Check H flag*/ 
            if((AF.byte.hi & 0x0F) - ((DE.byte.lo & 0x0F) + (U8)CpuGetFlagC()) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi - (DE.byte.lo + (U8)CpuGetFlagC()) < 0x00)
            {
                c = SetFlag;
            }

            AF.byte.hi -= DE.byte.lo + (U8)CpuGetFlagC();
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case SBC_H:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           

            /*Check H flag*/ 
            if((AF.byte.hi & 0x0F) - ((HL.byte.hi & 0x0F) + (U8)CpuGetFlagC()) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi - (HL.byte.hi + (U8)CpuGetFlagC()) < 0x00)
            {
                c = SetFlag;
            }

            AF.byte.hi -= HL.byte.hi + (U8)CpuGetFlagC();
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case SBC_L:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           

            /*Check H flag*/ 
            if((AF.byte.hi & 0x0F) - ((HL.byte.lo & 0x0F) + (U8)CpuGetFlagC()) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi - (HL.byte.lo + (U8)CpuGetFlagC()) < 0x00)
            {
                c = SetFlag;
            }

            AF.byte.hi -= HL.byte.lo + (U8)CpuGetFlagC();
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case SBC_adr_HL:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;           
            U8 value = BusRead(HL.val);

            /*Check H flag*/ 
            if((AF.byte.hi & 0x0F) - ((value & 0x0F) + (U8)CpuGetFlagC()) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(AF.byte.hi - (value + (U8)CpuGetFlagC()) < 0x00)
            {
                c = SetFlag;
            }

            AF.byte.hi -= value + (U8)CpuGetFlagC();
            CpuIncCycle(MECHANICAL_CYCLES_2);

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        /*Logical operation*/
        case CPL: 
        {
            AF.byte.hi = AF.byte.hi ^ 0xFF;
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(SetFlag);
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case DAA:
        {
            FlagValue z = ResetFlag;
            FlagValue c = ResetFlag;  
            U8 value = 0;

            if((CpuGetFlagH() == SetFlag) || ((CpuGetFlagN() == ResetFlag) && (AF.byte.hi & 0xF)> 9))
            {
                value = 6;
            }

            if((CpuGetFlagC() == SetFlag) || ((CpuGetFlagN() == ResetFlag) && AF.byte.hi > 0x99))
            {
                value |= 0x60;
                c = SetFlag;
            }

            if(CpuGetFlagN() == ResetFlag)
            {
                AF.byte.hi += value; 
            }
            else
            {
                AF.byte.hi += -value; 
            }

            /*Check Z flag*/
            if(AF.byte.hi == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(c);
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }
        
        case AND_n:
        {
            FlagValue z = ResetFlag;
            U8 n;
            n = BusRead(PC);
            PC++;

            AF.byte.hi &= n;
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(SetFlag);
            CpuSetFlagC(ResetFlag);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case AND_A:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi &= AF.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(SetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case AND_B:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi &= BC.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(SetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case AND_C:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi &= BC.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(SetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case AND_D:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi &= DE.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(SetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case AND_E:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi &= DE.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(SetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case AND_H:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi &= HL.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(SetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case AND_L:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi &= HL.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(SetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case AND_adr_HL:
        {
            FlagValue z = ResetFlag;
            U8 value = BusRead(HL.val);

            AF.byte.hi &= value;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(SetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case XOR_n:
        {
            FlagValue z = ResetFlag;
            U8 n;
            n = BusRead(PC);
            PC++;

            AF.byte.hi ^= n;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case XOR_A:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi ^= AF.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case XOR_B:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi ^= BC.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case XOR_C:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi ^= BC.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case XOR_D:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi ^= DE.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case XOR_E:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi ^= DE.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case XOR_H:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi ^= HL.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case XOR_L:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi ^= HL.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case XOR_adr_HL:
        {
            FlagValue z = ResetFlag;
            U8 value = BusRead(HL.val);

            AF.byte.hi ^= value;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case OR_n:
        {
            FlagValue z = ResetFlag;
            U8 n;
            n = BusRead(PC);
            PC++;

            AF.byte.hi |= n;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case OR_A:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi |= AF.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case OR_B:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi |= BC.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(ResetFlag);   
            break;    
        }

        case OR_C:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi |= BC.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case OR_D:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi |= DE.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case OR_E:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi |= DE.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case OR_H:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi |= HL.byte.hi;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case OR_L:
        {
            FlagValue z = ResetFlag;

            AF.byte.hi |= HL.byte.lo;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case OR_adr_HL:
        {
            FlagValue z = ResetFlag;
            U8 value = BusRead(HL.val);

            AF.byte.hi |= value;
            CpuIncCycle(MECHANICAL_CYCLES_2);
            
            /*Check Z flag*/
            if(AF.byte.hi == 0x00)
            {
                z = SetFlag;
            }
            
            CpuSetFlagZ(z);
            CpuSetFlagN(ResetFlag);
            CpuSetFlagH(ResetFlag);
            CpuSetFlagC(ResetFlag);
            break;
        }

        case CP_n:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;
            U8 valueA = AF.byte.hi;
            U8 value_n = BusRead(PC);
            PC++;

            /*Check H flag*/ 
            if((valueA & 0x0F) - (value_n & 0x0F) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(valueA - value_n < 0x00)
            {
                c = SetFlag;
            }

            valueA -= value_n;
            CpuIncCycle(MECHANICAL_CYCLES_2);

            /*Check Z flag*/
            if(valueA == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case CP_A:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;
            U8 valueA = AF.byte.hi;

            /*Check H flag*/ 
            if((valueA & 0x0F) - (valueA & 0x0F) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(valueA - valueA < 0x00)
            {
                c = SetFlag;
            }

            valueA -= valueA;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(valueA == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case CP_B:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;
            U8 valueA = AF.byte.hi;
            U8 valueB = BC.byte.hi;

            /*Check H flag*/ 
            if((valueA & 0x0F) - (valueB & 0x0F) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(valueA - valueB < 0x00)
            {
                c = SetFlag;
            }

            valueA -= valueB;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(valueA == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case CP_C:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;
            U8 valueA = AF.byte.hi;
            U8 valueC = BC.byte.lo;

            /*Check H flag*/ 
            if((valueA & 0x0F) - (valueC & 0x0F) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(valueA - valueC < 0x00)
            {
                c = SetFlag;
            }

            valueA -= valueC;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(valueA == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case CP_D:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;
            U8 valueA = AF.byte.hi;
            U8 valueD = DE.byte.hi;

            /*Check H flag*/ 
            if((valueA & 0x0F) - (valueD & 0x0F) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(valueA - valueD < 0x00)
            {
                c = SetFlag;
            }

            valueA -= valueD;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(valueA == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case CP_E:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;
            U8 valueA = AF.byte.hi;
            U8 valueE = DE.byte.lo;

            /*Check H flag*/ 
            if((valueA & 0x0F) - (valueE & 0x0F) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(valueA - valueE < 0x00)
            {
                c = SetFlag;
            }

            valueA -= valueE;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(valueA == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case CP_H:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;
            U8 valueA = AF.byte.hi;
            U8 valueH = HL.byte.hi;

            /*Check H flag*/ 
            if((valueA & 0x0F) - (valueH & 0x0F) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(valueA - valueH < 0x00)
            {
                c = SetFlag;
            }

            valueA -= valueH;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(valueA == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case CP_L:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;
            U8 valueA = AF.byte.hi;
            U8 valueL = HL.byte.lo;

            /*Check H flag*/ 
            if((valueA & 0x0F) - (valueL & 0x0F) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(valueA - valueL < 0x00)
            {
                c = SetFlag;
            }

            valueA -= valueL;
            CpuIncCycle(MECHANICAL_CYCLES_1);

            /*Check Z flag*/
            if(valueA == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        case CP_adr_HL:
        {
            FlagValue z = ResetFlag;
            FlagValue h = ResetFlag;
            FlagValue c = ResetFlag;
            U8 valueA = AF.byte.hi;
            U8 valueAdrHL = BusRead(HL.val);

            /*Check H flag*/ 
            if((valueA & 0x0F) - (valueAdrHL & 0x0F) < 0x00)
            {
                h = SetFlag;
            }
            /*Check C flag*/
            if(valueA - valueAdrHL < 0x00)
            {
                c = SetFlag;
            }

            valueA -= valueAdrHL;
            CpuIncCycle(MECHANICAL_CYCLES_2);

            /*Check Z flag*/
            if(valueA == 0)
            {
                z = SetFlag;
            }

            CpuSetFlagZ(z);
            CpuSetFlagN(SetFlag);
            CpuSetFlagH(h);
            CpuSetFlagC(c);
            break;
        }

        /*Jump operations*/
        case JR_e:
        {
            S8 e;
            e = (S8)BusRead(PC);
            PC++;
            PC += e;
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break;
        }

        case JR_NZ_e:
        {
            S8 e;
            e = (S8)(BusRead(PC) & 0xFF);
            PC++;
            if(CpuGetFlagZ() == ResetFlag)
            {
                PC += e;
                CpuIncCycle(MECHANICAL_CYCLES_1);
            }
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case JR_Z_e:
        {
            S8 e;
            e = (S8)(BusRead(PC) & 0xFF);
            PC++;
            if(CpuGetFlagZ() == SetFlag)
            {
                PC += e;
                CpuIncCycle(MECHANICAL_CYCLES_1);
            }
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case JR_NC_e:
        {
            S8 e;
            e = (S8)(BusRead(PC) & 0xFF);
            PC++;
            if(CpuGetFlagC() == ResetFlag)
            {
                PC += e;
                CpuIncCycle(MECHANICAL_CYCLES_1);
            }
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case JR_C_e:
        {
            S8 e;
            e = (S8)(BusRead(PC) & 0xFF);
            PC++;
            if(CpuGetFlagC() == SetFlag)
            {
                PC += e;
                CpuIncCycle(MECHANICAL_CYCLES_1);
            }
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case JP_nn:
        {
            U8 lsb, msb;
            lsb = BusRead(PC);
            PC++;
            msb = BusRead(PC);
            PC++;
            PC = MergeValues(msb, lsb);
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        case JP_NZ_nn:
        {
            U8 lsb, msb;
            lsb = BusRead(PC);
            PC++;
            msb = BusRead(PC);
            PC++;
            if(CpuGetFlagZ() == ResetFlag)
            {
                PC = MergeValues(msb, lsb);
                CpuIncCycle(MECHANICAL_CYCLES_1);
            }
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break;
        }

        case JP_Z_nn:
        {
            U8 lsb, msb;
            lsb = BusRead(PC);
            PC++;
            msb = BusRead(PC);
            PC++;
            if(CpuGetFlagZ() == SetFlag)
            {
                PC = MergeValues(msb, lsb);
                CpuIncCycle(MECHANICAL_CYCLES_1);
                // AbortProgram();
            }
            CpuIncCycle(MECHANICAL_CYCLES_3);
            
            break;
        }

        case JP_NC_nn:
        {
            U8 lsb, msb;
            lsb = BusRead(PC);
            PC++;
            msb = BusRead(PC);
            PC++;
            if(CpuGetFlagC() == ResetFlag)
            {
                PC = MergeValues(msb, lsb);
                CpuIncCycle(MECHANICAL_CYCLES_1);
            }
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break;
        }

        case JP_C_nn:
        {
            U8 lsb, msb;
            lsb = BusRead(PC);
            PC++;
            msb = BusRead(PC);
            PC++;
            if(CpuGetFlagC() == SetFlag)
            {
                PC = MergeValues(msb, lsb);
                CpuIncCycle(MECHANICAL_CYCLES_1);
            }
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break;
        }

        case JP_HL:
        {
            PC = HL.val;
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        /*Restart operations*/
        case RST_0x00:
        {
            SP--;
            BusWrite(SP, (U8)(PC>>8));
            SP--;
            BusWrite(SP, (U8)(PC & 0xFF));
            PC = 0x0000;
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        case RST_0x08:
        {
            SP--;
            BusWrite(SP, (U8)(PC>>8));
            SP--;
            BusWrite(SP, (U8)(PC & 0xFF));
            PC = 0x0008;
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        case RST_0x10:
        {
            SP--;
            BusWrite(SP, (U8)(PC>>8));
            SP--;
            BusWrite(SP, (U8)(PC & 0xFF));
            PC = 0x0010;
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;            
        }

        case RST_0x18:
        {
            SP--;
            BusWrite(SP, (U8)(PC>>8));
            SP--;
            BusWrite(SP, (U8)(PC & 0xFF));
            PC = 0x0018;
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        case RST_0x20:
        {
            SP--;
            BusWrite(SP, (U8)(PC>>8));
            SP--;
            BusWrite(SP, (U8)(PC & 0xFF));
            PC = 0x0020;
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        case RST_0x28:
        {
            SP--;
            BusWrite(SP, (U8)(PC>>8));
            SP--;
            BusWrite(SP, (U8)(PC & 0xFF));
            PC = 0x0028;
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        case RST_0x30:
        {
            SP--;
            BusWrite(SP, (U8)(PC>>8));
            SP--;
            BusWrite(SP, (U8)(PC & 0xFF));
            PC = 0x0030;
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        case RST_0x38:
        {
            SP--;
            BusWrite(SP, (U8)(PC>>8));
            SP--;
            BusWrite(SP, (U8)(PC & 0xFF));
            PC = 0x0038;
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        /*Push Operation*/
        case PUSH_AF:
        {
            SP--;
            BusWrite(SP, AF.byte.hi);
            SP--;
            BusWrite(SP, AF.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        case PUSH_BC:
        {
            SP--;
            BusWrite(SP, BC.byte.hi);
            SP--;
            BusWrite(SP, BC.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        case PUSH_DE:
        {
            SP--;
            BusWrite(SP, DE.byte.hi);
            SP--;
            BusWrite(SP, DE.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        case PUSH_HL:
        {
            SP--;
            BusWrite(SP, HL.byte.hi);
            SP--;
            BusWrite(SP, HL.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        /*Return operation*/
        case RET:
        {
            U8 lsb, msb;
            lsb = BusRead(SP);
            SP++;
            msb = BusRead(SP);
            SP++;
            PC = MergeValues(msb, lsb);
            CpuIncCycle(MECHANICAL_CYCLES_4);

            break;
        }

        case RET_NZ:
        {
            U8 lsb, msb;
            if(CpuGetFlagZ() == ResetFlag)
            {
                lsb = BusRead(SP);
                SP++;
                msb = BusRead(SP);
                SP++;
                PC = MergeValues(msb, lsb);
                CpuIncCycle(MECHANICAL_CYCLES_3);
            }
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RET_Z:
        {
            U8 lsb, msb;
            if(CpuGetFlagZ() == SetFlag)
            {
                lsb = BusRead(SP);
                SP++;
                msb = BusRead(SP);
                SP++;
                PC = MergeValues(msb, lsb);
                CpuIncCycle(MECHANICAL_CYCLES_3);

            }
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RET_NC:
        {
            U8 lsb, msb;
            if(CpuGetFlagC() == ResetFlag)
            {
                lsb = BusRead(SP);
                SP++;
                msb = BusRead(SP);
                SP++;
                PC = MergeValues(msb, lsb);
                CpuIncCycle(MECHANICAL_CYCLES_3);
            }
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break; 
        }

        case RET_C:
        {
            U8 lsb, msb;
            if(CpuGetFlagC() == SetFlag)
            {
                lsb = BusRead(SP);
                SP++;
                msb = BusRead(SP);
                SP++;
                PC = MergeValues(msb, lsb);
                CpuIncCycle(MECHANICAL_CYCLES_3);
            }
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;             
        }

        case RETI:
        {
            U8 lsb, msb;
            lsb = BusRead(SP);
            SP++;
            msb = BusRead(SP);
            SP++;
            PC = MergeValues(msb, lsb);
            InterruptGetObj() -> InterruptEnableIMEbyRETI(); 
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        /*Call operations*/
        case CALL_nn:
        {
            U8 nnLSB, nnMSB;
            U8 pcLSB, pcMSB;
            /*Read out nn*/
            nnLSB = BusRead(PC);
            PC++;
            nnMSB = BusRead(PC);
            PC++;
            /*Write SP*/
            DivideValue(PC, &pcLSB, &pcMSB);
            SP--;
            BusWrite(SP, pcMSB);
            SP--;
            BusWrite(SP, pcLSB);
            /*Write PC*/
            PC = MergeValues(nnMSB, nnLSB);
            CpuIncCycle(MECHANICAL_CYCLES_6);

            break;
        }

        case CALL_NZ_nn:
        {
            U8 nnLSB, nnMSB;
            U8 pcLSB, pcMSB;
            /*Read out nn*/
            nnLSB = BusRead(PC);
            PC++;
            nnMSB = BusRead(PC);
            PC++;
            
            if(CpuGetFlagZ() == ResetFlag)
            {
                /*Write SP*/
                DivideValue(PC, &pcLSB, &pcMSB);
                SP--;
                BusWrite(SP, pcMSB);
                SP--;
                BusWrite(SP, pcLSB);
                /*Write PC*/
                PC = MergeValues(nnMSB, nnLSB);
                CpuIncCycle(MECHANICAL_CYCLES_3);
            }
            
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break;
        }

        case CALL_Z_nn:
        {
            U8 nnLSB, nnMSB;
            U8 pcLSB, pcMSB;
            /*Read out nn*/
            nnLSB = BusRead(PC);
            PC++;
            nnMSB = BusRead(PC);
            PC++;
            
            if(CpuGetFlagZ() == SetFlag)
            {
                /*Write SP*/
                DivideValue(PC, &pcLSB, &pcMSB);
                SP--;
                BusWrite(SP, pcMSB);
                SP--;
                BusWrite(SP, pcLSB);
                /*Write PC*/
                PC = MergeValues(nnMSB, nnLSB);
                CpuIncCycle(MECHANICAL_CYCLES_3);
            }
            
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break; 
        }

        case CALL_NC_nn:
        {
            U8 nnLSB, nnMSB;
            U8 pcLSB, pcMSB;
            /*Read out nn*/
            nnLSB = BusRead(PC);
            PC++;
            nnMSB = BusRead(PC);
            PC++;
            
            if(CpuGetFlagC() == ResetFlag)
            {
                /*Write SP*/
                DivideValue(PC, &pcLSB, &pcMSB);
                SP--;
                BusWrite(SP, pcMSB);
                SP--;
                BusWrite(SP, pcLSB);
                /*Write PC*/
                PC = MergeValues(nnMSB, nnLSB);
                CpuIncCycle(MECHANICAL_CYCLES_3);
            }
            
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break; 
        }

        case CALL_C_nn:
        {
            U8 nnLSB, nnMSB;
            U8 pcLSB, pcMSB;
            /*Read out nn*/
            nnLSB = BusRead(PC);
            PC++;
            nnMSB = BusRead(PC);
            PC++;
            
            if(CpuGetFlagC() == SetFlag)
            {
                /*Write SP*/
                DivideValue(PC, &pcLSB, &pcMSB);
                SP--;
                BusWrite(SP, pcMSB);
                SP--;
                BusWrite(SP, pcLSB);
                /*Write PC*/
                PC = MergeValues(nnMSB, nnLSB);
                CpuIncCycle(MECHANICAL_CYCLES_3);
            }
            
            CpuIncCycle(MECHANICAL_CYCLES_3);
            break; 
        }

        /*Interrupt operations*/
        case DI:
        {
            InterruptGetObj() -> InterruptDisableIME();
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        case EI:
        {
            InterruptGetObj() -> InterruptEnableIME();
            CpuIncCycle(MECHANICAL_CYCLES_1);
            break;
        }

        default:
            std::cout<<"Unhandled opcode: "<<(U16)OpCode<<std::endl;
            break;
    }
}

void CPU :: CpuExecute_CB_Instruction(U8 prefix)
{
    switch (prefix)
    {
        /*Rotate left Circular operations*/
        case RLC_A:
        {
            CpuInstrutionRLC(&AF.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RLC_B:
        {
            CpuInstrutionRLC(&BC.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }
        
        case RLC_C:
        {
            CpuInstrutionRLC(&BC.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RLC_D:
        {
            CpuInstrutionRLC(&DE.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RLC_E:
        {
            CpuInstrutionRLC(&DE.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RLC_H:
        {
            CpuInstrutionRLC(&HL.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RLC_L:
        {
            CpuInstrutionRLC(&HL.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RLC_adr_HL:
        {
            U8 value = BusRead(HL.val);
            CpuInstrutionRLC(&value);
            BusWrite(HL.val,value);
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        /*Rotate right Circular operations*/
        case RRC_A:
        {
            CpuInstrutionRRC(&AF.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RRC_B:
        {
            CpuInstrutionRRC(&BC.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RRC_C:
        {
            CpuInstrutionRRC(&BC.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RRC_D:
        {
            CpuInstrutionRRC(&DE.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RRC_E:
        {
            CpuInstrutionRRC(&DE.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RRC_H:
        {
            CpuInstrutionRRC(&HL.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RRC_L:
        {
            CpuInstrutionRRC(&HL.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RRC_adr_HL:
        {
            U8 value = BusRead(HL.val);
            CpuInstrutionRRC(&value);
            BusWrite(HL.val, value);
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        /*Rotate left operations*/
        case RL_A:
        {
            CpuInstrutionRL(&AF.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;

        }

        case RL_B:
        {
            CpuInstrutionRL(&BC.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RL_C:
        {
            CpuInstrutionRL(&BC.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RL_D:
        {
            CpuInstrutionRL(&DE.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RL_E:
        {
            CpuInstrutionRL(&DE.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RL_H:
        {
            CpuInstrutionRL(&HL.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RL_L:
        {
            CpuInstrutionRL(&HL.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RL_adr_HL:
        {
            U8 value = BusRead(HL.val);
            CpuInstrutionRL(&value);
            BusWrite(HL.val, value);
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;            
        }

        /*Rotate right operations*/
        case RR_A:
        {
            CpuInstrutionRR(&AF.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;

        }

        case RR_B:
        {
            CpuInstrutionRR(&BC.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RR_C:
        {
            CpuInstrutionRR(&BC.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RR_D:
        {
            CpuInstrutionRR(&DE.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RR_E:
        {
            CpuInstrutionRR(&DE.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RR_H:
        {
            CpuInstrutionRR(&HL.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case RR_L:
        {
            CpuInstrutionRR(&HL.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }   

        case RR_adr_HL:
        {   
            U8 value = BusRead(HL.val);
            CpuInstrutionRR(&value);
            BusWrite(HL.val, value);
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        /*Shift Left Arithmetic operations*/
        case SLA_A:
        {
            CpuInstrutionSLA(&AF.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SLA_B:
        {
            CpuInstrutionSLA(&BC.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SLA_C:
        {
            CpuInstrutionSLA(&BC.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SLA_D:
        {
            CpuInstrutionSLA(&DE.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SLA_E:
        {
            CpuInstrutionSLA(&DE.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SLA_H:
        {
            CpuInstrutionSLA(&HL.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SLA_L:
        {
            CpuInstrutionSLA(&HL.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SLA_adr_HL:
        {
            CpuInstrutionSLA(HL.val);
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        /*Shift Right Aritmetic operations*/
        case SRA_A:
        {
            CpuInstrutionSRA(&AF.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SRA_B:
        {
            CpuInstrutionSRA(&BC.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SRA_C:
        {
            CpuInstrutionSRA(&BC.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SRA_D:
        {
            CpuInstrutionSRA(&DE.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SRA_E:
        {
            CpuInstrutionSRA(&DE.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SRA_H:
        {
            CpuInstrutionSRA(&HL.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SRA_L:
        {
            CpuInstrutionSRA(&HL.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SRA_adr_HL:
        {
            U8 value = BusRead(HL.val);
            CpuInstrutionSRA(&value);
            BusWrite(HL.val, value);
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        /*Shift Right Logical operations*/
        case SRL_A:
        {
            CpuInstrutionSRL(&AF.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SRL_B:
        {
            CpuInstrutionSRL(&BC.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SRL_C:
        {
            CpuInstrutionSRL(&BC.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SRL_D:
        {
            CpuInstrutionSRL(&DE.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SRL_E:
        {
            CpuInstrutionSRL(&DE.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SRL_H:
        {
            CpuInstrutionSRL(&HL.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SRL_L:
        {
            CpuInstrutionSRL(&HL.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SRL_adr_HL:
        {
            U8 value = BusRead(HL.val);
            CpuInstrutionSRL(&value);
            BusWrite(HL.val, value);
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        /*Swap operations*/
        case SWAP_A:
        {
            CpuInstrutionSWAP(&AF.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SWAP_B:
        {
            CpuInstrutionSWAP(&BC.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SWAP_C:
        {
            CpuInstrutionSWAP(&BC.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SWAP_D:
        {
            CpuInstrutionSWAP(&DE.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SWAP_E:
        {
            CpuInstrutionSWAP(&DE.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SWAP_H:
        {
            CpuInstrutionSWAP(&HL.byte.hi);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SWAP_L:
        {
            CpuInstrutionSWAP(&HL.byte.lo);
            CpuIncCycle(MECHANICAL_CYCLES_2);
            break;
        }

        case SWAP_adr_HL:
        {
            U8 value = BusRead(HL.val);
            CpuInstrutionSWAP(&value);
            BusWrite(HL.val, value);
            CpuIncCycle(MECHANICAL_CYCLES_4);
            break;
        }

        /*Test bit 0 operations*/
        case BIT_0_A:
        {
            CpuBitTest(0, &AF.byte.hi);
            break;
        }

        case BIT_0_B:
        {
            CpuBitTest(0, &BC.byte.hi);
            break;
        }

        case BIT_0_C:
        {
            CpuBitTest(0, &BC.byte.lo);
            break;
        }

        case BIT_0_D:
        {
            CpuBitTest(0, &DE.byte.hi);
            break;
        }

        case BIT_0_E:
        {
            CpuBitTest(0, &DE.byte.lo);
            break;
        }

        case BIT_0_H:
        {
            CpuBitTest(0, &HL.byte.hi);
            break;
        }

        case BIT_0_adr_HL:
        {
            CpuBitTest(0, HL.val);
            break;
        }

        case BIT_0_L:
        {
            CpuBitTest(0, &HL.byte.lo);
            break;
        }   

        /*Test bit 1 operations*/
        case BIT_1_A:
        {
            CpuBitTest(1, &AF.byte.hi);
            break;
        }

        case BIT_1_B:
        {
            CpuBitTest(1, &BC.byte.hi);
            break;
        }

        case BIT_1_C:
        {
            CpuBitTest(1, &BC.byte.lo);
            break;
        }

        case BIT_1_D:
        {
            CpuBitTest(1, &DE.byte.hi);
            break;
        }

        case BIT_1_E:
        {
            CpuBitTest(1, &DE.byte.lo);
            break;
        }

        case BIT_1_H:
        {
            CpuBitTest(1, &HL.byte.hi);
            break;
        }

        case BIT_1_L:
        {
            CpuBitTest(1, &HL.byte.lo);
            break;
        }   

        case BIT_1_adr_HL:
        {
            CpuBitTest(1, HL.val);
            break;
        }

        /*Test bit 2 operations*/
        case BIT_2_A:
        {
            CpuBitTest(2, &AF.byte.hi);
            break;
        }

        case BIT_2_B:
        {
            CpuBitTest(2, &BC.byte.hi);
            break;
        }

        case BIT_2_C:
        {
            CpuBitTest(2, &BC.byte.lo);
            break;
        }

        case BIT_2_D:
        {
            CpuBitTest(2, &DE.byte.hi);
            break;
        }

        case BIT_2_E:
        {
            CpuBitTest(2, &DE.byte.lo);
            break;
        }

        case BIT_2_H:
        {
            CpuBitTest(2, &HL.byte.hi);
            break;
        }

        case BIT_2_L:
        {
            CpuBitTest(2, &HL.byte.lo);
            break;
        }   

        case BIT_2_adr_HL:
        {
            CpuBitTest(2, HL.val);
            break;
        }

        /*Test bit 3 operations*/
        case BIT_3_A:
        {
            CpuBitTest(3, &AF.byte.hi);
            break;
        }

        case BIT_3_B:
        {
            CpuBitTest(3, &BC.byte.hi);
            break;
        }

        case BIT_3_C:
        {
            CpuBitTest(3, &BC.byte.lo);
            break;
        }

        case BIT_3_D:
        {
            CpuBitTest(3, &DE.byte.hi);
            break;
        }

        case BIT_3_E:
        {
            CpuBitTest(3, &DE.byte.lo);
            break;
        }

        case BIT_3_H:
        {
            CpuBitTest(3, &HL.byte.hi);
            break;
        }

        case BIT_3_L:
        {
            CpuBitTest(3, &HL.byte.lo);
            break;
        } 

        case BIT_3_adr_HL:
        {
            CpuBitTest(3, HL.val);
            break;
        }

        /*Test bit 4 operations*/
        case BIT_4_A:
        {
            CpuBitTest(4, &AF.byte.hi);
            break;
        }

        case BIT_4_B:
        {
            CpuBitTest(4, &BC.byte.hi);
            break;
        }

        case BIT_4_C:
        {
            CpuBitTest(4, &BC.byte.lo);
            break;
        }

        case BIT_4_D:
        {
            CpuBitTest(4, &DE.byte.hi);
            break;
        }

        case BIT_4_E:
        {
            CpuBitTest(4, &DE.byte.lo);
            break;
        }

        case BIT_4_H:
        {
            CpuBitTest(4, &HL.byte.hi);
            break;
        }

        case BIT_4_L:
        {
            CpuBitTest(4, &HL.byte.lo);
            break;
        }

        case BIT_4_adr_HL:
        {
            CpuBitTest(4, HL.val);
            break;
        }

        /*Test bit 5 operations*/
        case BIT_5_A:
        {
            CpuBitTest(5, &AF.byte.hi);
            break;
        }

        case BIT_5_B:
        {
            CpuBitTest(5, &BC.byte.hi);
            break;
        }

        case BIT_5_C:
        {
            CpuBitTest(5, &BC.byte.lo);
            break;
        }

        case BIT_5_D:
        {
            CpuBitTest(5, &DE.byte.hi);
            break;
        }

        case BIT_5_E:
        {
            CpuBitTest(5, &DE.byte.lo);
            break;
        }

        case BIT_5_H:
        {
            CpuBitTest(5, &HL.byte.hi);
            break;
        }

        case BIT_5_L:
        {
            CpuBitTest(5, &HL.byte.lo);
            break;
        } 

        case BIT_5_adr_HL:
        {
            CpuBitTest(5, HL.val);
            break;
        }

        /*Test bit 6 operations*/
        case BIT_6_A:
        {
            CpuBitTest(6, &AF.byte.hi);
            break;
        }

        case BIT_6_B:
        {
            CpuBitTest(6, &BC.byte.hi);
            break;
        }

        case BIT_6_C:
        {
            CpuBitTest(6, &BC.byte.lo);
            break;
        }

        case BIT_6_D:
        {
            CpuBitTest(6, &DE.byte.hi);
            break;
        }

        case BIT_6_E:
        {
            CpuBitTest(6, &DE.byte.lo);
            break;
        }

        case BIT_6_H:
        {
            CpuBitTest(6, &HL.byte.hi);
            break;
        }

        case BIT_6_L:
        {
            CpuBitTest(6, &HL.byte.lo);
            break;
        } 

        case BIT_6_adr_HL:
        {
            CpuBitTest(6, HL.val);
            break;
        }

        /*Test bit 7 operations*/
        case BIT_7_A:
        {
            CpuBitTest(7, &AF.byte.hi);
            break;
        }

        case BIT_7_B:
        {
            CpuBitTest(7, &BC.byte.hi);
            break;
        }

        case BIT_7_C:
        {
            CpuBitTest(7, &BC.byte.lo);
            break;
        }

        case BIT_7_D:
        {
            CpuBitTest(7, &DE.byte.hi);
            break;
        }

        case BIT_7_E:
        {
            CpuBitTest(7, &DE.byte.lo);
            break;
        }

        case BIT_7_H:
        {
            CpuBitTest(7, &HL.byte.hi);
            break;
        }

        case BIT_7_L:
        {
            CpuBitTest(7, &HL.byte.lo);
            break;
        } 

        case BIT_7_adr_HL:
        {
            CpuBitTest(7, HL.val);
            break;
        }

        /*Reset bit 0 operations*/
        case RES_0_A:
        {
            CpuBitReset(0, &AF.byte.hi);
            break;
        }

        case RES_0_B:
        {
            CpuBitReset(0, &BC.byte.hi);
            break;
        }

        case RES_0_C:
        {
            CpuBitReset(0, &BC.byte.lo);
            break;
        }

        case RES_0_D:
        {
            CpuBitReset(0, &DE.byte.hi);
            break;
        }

        case RES_0_E:
        {
            CpuBitReset(0, &DE.byte.lo);
            break;
        }

        case RES_0_H:
        {
            CpuBitReset(0, &HL.byte.hi);
            break;
        }

        case RES_0_L:
        {
            CpuBitReset(0, &HL.byte.lo);
            break;
        }   

        case RES_0_adr_HL:
        {
            CpuBitReset(0, HL.val);
            break;
        }

        /*Reset bit 1 operations*/
        case RES_1_A:
        {
            CpuBitReset(1, &AF.byte.hi);
            break;
        }

        case RES_1_B:
        {
            CpuBitReset(1, &BC.byte.hi);
            break;
        }

        case RES_1_C:
        {
            CpuBitReset(1, &BC.byte.lo);
            break;
        }

        case RES_1_D:
        {
            CpuBitReset(1, &DE.byte.hi);
            break;
        }

        case RES_1_E:
        {
            CpuBitReset(1, &DE.byte.lo);
            break;
        }

        case RES_1_H:
        {
            CpuBitReset(1, &HL.byte.hi);
            break;
        }

        case RES_1_L:
        {
            CpuBitReset(1, &HL.byte.lo);
            break;
        }   

        case RES_1_adr_HL:
        {
            CpuBitReset(1, HL.val);
            break;
        }

        /*Reset bit 2 operations*/
        case RES_2_A:
        {
            CpuBitReset(2, &AF.byte.hi);
            break;
        }

        case RES_2_B:
        {
            CpuBitReset(2, &BC.byte.hi);
            break;
        }

        case RES_2_C:
        {
            CpuBitReset(2, &BC.byte.lo);
            break;
        }

        case RES_2_D:
        {
            CpuBitReset(2, &DE.byte.hi);
            break;
        }

        case RES_2_E:
        {
            CpuBitReset(2, &DE.byte.lo);
            break;
        }

        case RES_2_H:
        {
            CpuBitReset(2, &HL.byte.hi);
            break;
        }

        case RES_2_L:
        {
            CpuBitReset(2, &HL.byte.lo);
            break;
        }   

        case RES_2_adr_HL:
        {
            CpuBitReset(2, HL.val);
            break;
        }

        /*Reset bit 3 operations*/
        case RES_3_A:
        {
            CpuBitReset(3, &AF.byte.hi);
            break;
        }

        case RES_3_B:
        {
            CpuBitReset(3, &BC.byte.hi);
            break;
        }

        case RES_3_C:
        {
            CpuBitReset(3, &BC.byte.lo);
            break;
        }

        case RES_3_D:
        {
            CpuBitReset(3, &DE.byte.hi);
            break;
        }

        case RES_3_E:
        {
            CpuBitReset(3, &DE.byte.lo);
            break;
        }

        case RES_3_H:
        {
            CpuBitReset(3, &HL.byte.hi);
            break;
        }

        case RES_3_L:
        {
            CpuBitReset(3, &HL.byte.lo);
            break;
        } 

        case RES_3_adr_HL:
        {
            CpuBitReset(3, HL.val);
            break;
        }

        /*Reset bit 4 operations*/
        case RES_4_A:
        {
            CpuBitReset(4, &AF.byte.hi);
            break;
        }

        case RES_4_B:
        {
            CpuBitReset(4, &BC.byte.hi);
            break;
        }

        case RES_4_C:
        {
            CpuBitReset(4, &BC.byte.lo);
            break;
        }

        case RES_4_D:
        {
            CpuBitReset(4, &DE.byte.hi);
            break;
        }

        case RES_4_E:
        {
            CpuBitReset(4, &DE.byte.lo);
            break;
        }

        case RES_4_H:
        {
            CpuBitReset(4, &HL.byte.hi);
            break;
        }

        case RES_4_L:
        {
            CpuBitReset(4, &HL.byte.lo);
            break;
        } 

        case RES_4_adr_HL:
        {
            CpuBitReset(4, HL.val);
            break;
        }

        /*Reset bit 5 operations*/
        case RES_5_A:
        {
            CpuBitReset(5, &AF.byte.hi);
            break;
        }

        case RES_5_B:
        {
            CpuBitReset(5, &BC.byte.hi);
            break;
        }

        case RES_5_C:
        {
            CpuBitReset(5, &BC.byte.lo);
            break;
        }

        case RES_5_D:
        {
            CpuBitReset(5, &DE.byte.hi);
            break;
        }

        case RES_5_E:
        {
            CpuBitReset(5, &DE.byte.lo);
            break;
        }

        case RES_5_H:
        {
            CpuBitReset(5, &HL.byte.hi);
            break;
        }

        case RES_5_L:
        {
            CpuBitReset(5, &HL.byte.lo);
            break;
        } 

        case RES_5_adr_HL:
        {
            CpuBitReset(5, HL.val);
            break;
        }

        /*Reset bit 6 operations*/
        case RES_6_A:
        {
            CpuBitReset(6, &AF.byte.hi);
            break;
        }

        case RES_6_B:
        {
            CpuBitReset(6, &BC.byte.hi);
            break;
        }

        case RES_6_C:
        {
            CpuBitReset(6, &BC.byte.lo);
            break;
        }

        case RES_6_D:
        {
            CpuBitReset(6, &DE.byte.hi);
            break;
        }

        case RES_6_E:
        {
            CpuBitReset(6, &DE.byte.lo);
            break;
        }

        case RES_6_H:
        {
            CpuBitReset(6, &HL.byte.hi);
            break;
        }

        case RES_6_L:
        {
            CpuBitReset(6, &HL.byte.lo);
            break;
        }

        case RES_6_adr_HL:
        {
            CpuBitReset(6, HL.val);
            break;
        }

        /*Reset bit 7 operations*/
        case RES_7_A:
        {
            CpuBitReset(7, &AF.byte.hi);
            break;
        }

        case RES_7_B:
        {
            CpuBitReset(7, &BC.byte.hi);
            break;
        }

        case RES_7_C:
        {
            CpuBitReset(7, &BC.byte.lo);
            break;
        }

        case RES_7_D:
        {
            CpuBitReset(7, &DE.byte.hi);
            break;
        }

        case RES_7_E:
        {
            CpuBitReset(7, &DE.byte.lo);
            break;
        }

        case RES_7_H:
        {
            CpuBitReset(7, &HL.byte.hi);
            break;
        }

        case RES_7_L:
        {
            CpuBitReset(7, &HL.byte.lo);
            break;
        } 

        case RES_7_adr_HL:
        {
            CpuBitReset(7, HL.val);
            break;
        }

        /*Set bit 0 operations*/
        case SET_0_A:
        {
            CpuBitSet(0, &AF.byte.hi);
            break;
        }

        case SET_0_B:
        {
            CpuBitSet(0, &BC.byte.hi);
            break;
        }

        case SET_0_C:
        {
            CpuBitSet(0, &BC.byte.lo);
            break;
        }

        case SET_0_D:
        {
            CpuBitSet(0, &DE.byte.hi);
            break;
        }

        case SET_0_E:
        {
            CpuBitSet(0, &DE.byte.lo);
            break;
        }

        case SET_0_H:
        {
            CpuBitSet(0, &HL.byte.hi);
            break;
        }

        case SET_0_L:
        {
            CpuBitSet(0, &HL.byte.lo);
            break;
        }   

        case SET_0_adr_HL:
        {
            CpuBitSet(0, HL.val);
            break;
        }

        /*Set bit 1 operations*/
        case SET_1_A:
        {
            CpuBitSet(1, &AF.byte.hi);
            break;
        }

        case SET_1_B:
        {
            CpuBitSet(1, &BC.byte.hi);
            break;
        }

        case SET_1_C:
        {
            CpuBitSet(1, &BC.byte.lo);
            break;
        }

        case SET_1_D:
        {
            CpuBitSet(1, &DE.byte.hi);
            break;
        }

        case SET_1_E:
        {
            CpuBitSet(1, &DE.byte.lo);
            break;
        }

        case SET_1_H:
        {
            CpuBitSet(1, &HL.byte.hi);
            break;
        }

        case SET_1_L:
        {
            CpuBitSet(1, &HL.byte.lo);
            break;
        }   

        case SET_1_adr_HL:
        {
            CpuBitSet(1, HL.val);
            break;
        }

        /*Set bit 2 operations*/
        case SET_2_A:
        {
            CpuBitSet(2, &AF.byte.hi);
            break;
        }

        case SET_2_B:
        {
            CpuBitSet(2, &BC.byte.hi);
            break;
        }

        case SET_2_C:
        {
            CpuBitSet(2, &BC.byte.lo);
            break;
        }

        case SET_2_D:
        {
            CpuBitSet(2, &DE.byte.hi);
            break;
        }

        case SET_2_E:
        {
            CpuBitSet(2, &DE.byte.lo);
            break;
        }

        case SET_2_H:
        {
            CpuBitSet(2, &HL.byte.hi);
            break;
        }

        case SET_2_L:
        {
            CpuBitSet(2, &HL.byte.lo);
            break;
        }   

        case SET_2_adr_HL:
        {
            CpuBitSet(2, HL.val);
            break;
        }

        /*Set bit 3 operations*/
        case SET_3_A:
        {
            CpuBitSet(3, &AF.byte.hi);
            break;
        }

        case SET_3_B:
        {
            CpuBitSet(3, &BC.byte.hi);
            break;
        }

        case SET_3_C:
        {
            CpuBitSet(3, &BC.byte.lo);
            break;
        }

        case SET_3_D:
        {
            CpuBitSet(3, &DE.byte.hi);
            break;
        }

        case SET_3_E:
        {
            CpuBitSet(3, &DE.byte.lo);
            break;
        }

        case SET_3_H:
        {
            CpuBitSet(3, &HL.byte.hi);
            break;
        }

        case SET_3_L:
        {
            CpuBitSet(3, &HL.byte.lo);
            break;
        } 

        case SET_3_adr_HL:
        {
            CpuBitSet(3, HL.val);
            break;
        }

        /*Set bit 4 operations*/
        case SET_4_A:
        {
            CpuBitSet(4, &AF.byte.hi);
            break;
        }

        case SET_4_B:
        {
            CpuBitSet(4, &BC.byte.hi);
            break;
        }

        case SET_4_C:
        {
            CpuBitSet(4, &BC.byte.lo);
            break;
        }

        case SET_4_D:
        {
            CpuBitSet(4, &DE.byte.hi);
            break;
        }

        case SET_4_E:
        {
            CpuBitSet(4, &DE.byte.lo);
            break;
        }

        case SET_4_H:
        {
            CpuBitSet(4, &HL.byte.hi);
            break;
        }

        case SET_4_L:
        {
            CpuBitSet(4, &HL.byte.lo);
            break;
        } 

        case SET_4_adr_HL:
        {
            CpuBitSet(4, HL.val);
            break;
        }

        /*Set bit 5 operations*/
        case SET_5_A:
        {
            CpuBitSet(5, &AF.byte.hi);
            break;
        }

        case SET_5_B:
        {
            CpuBitSet(5, &BC.byte.hi);
            break;
        }

        case SET_5_C:
        {
            CpuBitSet(5, &BC.byte.lo);
            break;
        }

        case SET_5_D:
        {
            CpuBitSet(5, &DE.byte.hi);
            break;
        }

        case SET_5_E:
        {
            CpuBitSet(5, &DE.byte.lo);
            break;
        }

        case SET_5_H:
        {
            CpuBitSet(5, &HL.byte.hi);
            break;
        }

        case SET_5_L:
        {
            CpuBitSet(5, &HL.byte.lo);
            break;
        } 

        case SET_5_adr_HL:
        {
            CpuBitSet(5, HL.val);
            break;
        }

        /*Set bit 6 operations*/
        case SET_6_A:
        {
            CpuBitSet(6, &AF.byte.hi);
            break;
        }

        case SET_6_B:
        {
            CpuBitSet(6, &BC.byte.hi);
            break;
        }

        case SET_6_C:
        {
            CpuBitSet(6, &BC.byte.lo);
            break;
        }

        case SET_6_D:
        {
            CpuBitSet(6, &DE.byte.hi);
            break;
        }

        case SET_6_E:
        {
            CpuBitSet(6, &DE.byte.lo);
            break;
        }

        case SET_6_H:
        {
            CpuBitSet(6, &HL.byte.hi);
            break;
        }

        case SET_6_L:
        {
            CpuBitSet(6, &HL.byte.lo);
            break;
        } 

        case SET_6_adr_HL:
        {
            CpuBitSet(6, HL.val);
            break;
        }

        /*Set bit 7 operations*/
        case SET_7_A:
        {
            CpuBitSet(7, &AF.byte.hi);
            break;
        }

        case SET_7_B:
        {
            CpuBitSet(7, &BC.byte.hi);
            break;
        }

        case SET_7_C:
        {
            CpuBitSet(7, &BC.byte.lo);
            break;
        }

        case SET_7_D:
        {
            CpuBitSet(7, &DE.byte.hi);
            break;
        }

        case SET_7_E:
        {
            CpuBitSet(7, &DE.byte.lo);
            break;
        }

        case SET_7_H:
        {
            CpuBitSet(7, &HL.byte.hi);
            break;
        }

        case SET_7_L:
        {
            CpuBitSet(7, &HL.byte.lo);
            break;
        } 

        case SET_7_adr_HL:
        {
            CpuBitSet(7, HL.val);
            break;
        }

        default:
            std::cout<<"Unhandled prefix: "<<(U16)prefix<<std::endl;
            AbortProgram();
            break;
    }
}