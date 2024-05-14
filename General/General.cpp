#include "General.h"
#include <stdlib.h>

U8 GetBit(U8 value, U8 bit)
{
    return (value & (0x01 << bit)) >> bit;
}

U8 ShiftLeft(U8 value, U8 shiftNumber)
{
    return value<<shiftNumber;
}

U8 ShiftRight(U8 value, U8 shiftNumber)
{
    return value>>shiftNumber;
}

U16 ShiftLeft(U16 value, U8 shiftNumber)
{
    return value<<shiftNumber;
}

void ShiftLeft(U8 *value, U8 shiftNumber)
{
    *value = *value << shiftNumber;
}

void ShiftLeft(U16 *value, U8 shiftNumber)
{
    *value = *value << shiftNumber;
}

U16 ShiftRight(U16 value, U8 shiftNumber)
{
    return value>>shiftNumber;
}

void ShiftRight(U8 *value, U8 shiftNumber)
{
    *value = *value >> shiftNumber;
}

void ShiftRight(U16 *value, U8 shiftNumber)
{
    *value = *value >> shiftNumber;
}

U16 MergeValues(U8 msb, U8 lsb)
{
    return (U16)((msb<<8) | lsb);
}

void DivideValue(U16 value, U8 *lsb, U8 *msb)
{
    *lsb = value & 0xFF;
    *msb = ShiftRight(value, 8);
}

void DivideValue(U8 value, U8 *lsb, U8 *msb)
{
    *lsb = value & 0x0F;
    *msb = value & 0xF0;
}

void SetBit(U8 *value, U8 bit)
{
    *value |= 1 << bit; 
}

void ResetBit(U8 *value, U8 bit)
{
    *value &= ~(1 << bit);
}

void AbortProgram()
{
    exit(3);
}
