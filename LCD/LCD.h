#pragma once
#include "../General/General.h"

#define ADDRESS_LCDC 0xFF40
#define ADDRESS_STAT 0xFF41
#define ADDRESS_SCY  0xFF42
#define ADDRESS_SCX  0xFF43
#define ADDRESS_LY   0xFF44
#define ADDRESS_LYC  0xFF45
#define ADDRESS_BGP  0xFF47
#define ADDRESS_OBP0 0xFF48
#define ADDRESS_OBP1 0xFF49
#define ADDRESS_WY   0xFF4A
#define ADDRESS_WX   0xFF4B

/*LCD Control register - 0xFF40*/
union LCDC_type
{
    struct
    {
        U8 BGandWindowEnable : 1;               //0=Off, 1=On
        U8 OBJenable : 1;                       //0=Off, 1=On
        U8 OBJsize : 1;                         //0=8×8, 1=8×16
        U8 BGtileMapArea : 1;                   //0=9800-9BFF, 1=9C00-9FFF
        U8 BGandWindowTileDataArea : 1;         //0=8800-97FF, 1=8000-8FFF
        U8 WindowsEnable : 1;                   //0=Off, 1=On
        U8 WindowsTileMapArea : 1;              //0=9800-9BFF, 1=9C00-9FFF
        U8 LCDandPPUenable : 1;                 //0=Off, 1=On
    } bit;
    U8 val;
};/*TODO: Invite better names*/

/*LCD status - 0xFF41*/
union STAT_type
{
    struct
    {
        U8 ModeFlag : 2;                //b00: HBlank, b01 VBlank, b10 Sercjing OAM, b11 Transferring Data to LCDC
        U8 LY_Flag : 1;                 //0=Different, 1=Equal
        U8 Mode_0 : 1;                  //1=Enable  HBlank
        U8 Mode_1 : 1;                  //1=Enable  VBlank
        U8 Mode_2 : 1;                  //1=Enable  OAM
        U8 LYC : 1;                     //1=Enable
    }bit;
    U8 val;
};




class LCD
{
    private:
        LCDC_type LCDC;          /*0xFF40*/
        STAT_type STAT;          /*0xFF41*/
        U8 SCY;                  /*0xFF42*/
        U8 SCX;                  /*0xFF43*/
        U8 LY;                   /*0xFF44*/
        U8 LYC;                  /*0xFF45*/
        U8 BGP;                  /*0xFF47*/
        U8 OBP0;                 /*0xFF48*/
        U8 OBP1;                 /*0xFF49*/
        U8 WY;                   /*0xFF4A*/
        U8 WX;                   /*0xFF4B*/
        
        void Reset();

    public:
        LCD();
        bool IsEnable();
        U8 GetLY();
        U8 GetLYC();
        U8 GetWY();
        U8 GetWX();
        U8 GetLCDC();
        void ResetLY();
        void IncLY();
        bool IsBgEnable();
        bool IsWinEnable();
        bool ObjIsEnable();
        bool GetBgTileMap();
        bool GetWinTileMap();
        bool GetBgAndWinTileArea();
        U8 GetSCX();
        U8 GetSCY();
        U8 GetBGP();
        STAT_type GetSTAT();
        U8 Read(U16 address);
        void Write(U16 address, U8 value);
        void SetSTAT_ModeFlag(U8 mode);
        bool IsWidowActive();
};

LCD * LcdGetObj();