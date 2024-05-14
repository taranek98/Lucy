#pragma once
#define Linux 0
#define Windows 1
#define System Windows

/*Type definitions*/
typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned long U32;
typedef signed char S8;
typedef signed short S16;
typedef signed long S32;

#define BIT_0 0
#define BIT_1 1
#define BIT_2 2
#define BIT_3 3
#define BIT_4 4
#define BIT_5 5
#define BIT_6 6
#define BIT_7 7

U8 GetBit(U8 value, U8 bit);
U8 ShiftLeft(U8 value, U8 shiftNumber);
U16 ShiftLeft(U16 value, U8 shiftNumber);
void ShiftLeft(U8 * value, U8 shiftNumber);
void ShiftLeft(U16 * value, U8 shiftNumber);
U8 ShiftRight(U8 value, U8 shiftNumber);
U16 ShiftRight(U16 value, U8 shiftNumber);
void ShiftRight(U8 * value, U8 shiftNumber);
void ShiftRight(U16 * value, U8 shiftNumber);
U16 MergeValues(U8 msb, U8 lsb);
void DivideValue(U16 value, U8 * lsb, U8 * msb);
void DivideValue(U8 value, U8 * lsb, U8 * msb);
void SetBit(U8 * value, U8 bit);
void ResetBit(U8 * value, U8 bit);
void AbortProgram();