#include "../General/General.h"

struct CartridgeHeader
{
    U8 EntryPoint [4];                       //$0100 - $0103
    U8 NintendoLogo[0x30];                   //#0104 - $0133
    char Title[16];                          //$0134 - $0143
    U16 NewLicenseeCode;                     //$0144 - $0145
    U8 SGB_Flag;                             //$0146
    U8 CartridgeType;                        //$0147
    U8 ROM_Size;                             //$0148
    U8 RAM_Size;                             //$0149
    U8 DestinationCode;                      //$014A
    U8 OldLicenseeCode;                      //$014B
    U8 Version;                              //$014C
    U8 Checksum;                             //$014D
    U16 GlobalChecksum;                      //$014E - $014F

};

class Cartridge
{
    private:
        U8 * data;
        CartridgeHeader * header;

    public: 
        Cartridge();
        void CartridgePrintInfo();
        U8 CartridgeReadROM(U16 address);
        void CartridgeWriteROM(U16 address, U8 value);
        void CartridgeDebug();
};

void CartridgeInit();
Cartridge * CartridgeGetObj();