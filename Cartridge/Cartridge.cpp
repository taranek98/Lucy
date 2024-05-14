#include "Cartridge.h"
#include <fstream>
#include <iostream>

using namespace std;
/*Variables*/
static Cartridge * cart;

/*Methods*/
Cartridge::Cartridge()
{
    U32 sizeROM = 0;
    /*TODO: Learn how it's work*/
    ifstream handlerStream( "Cartridge/cpu_instrs.gb", ios::binary | ios::ate);
    sizeROM = handlerStream.tellg();
    //cout<<"size Rom: "<<sizeROM<<endl;
    handlerStream.seekg(0, ios:: beg);
    data = new U8[sizeROM];

    U32 i = 0;
    while(!handlerStream.eof())
    {
        data[i] = handlerStream.get();
        i++;
    }
    header = (CartridgeHeader*)(data + 0x0100);
    handlerStream.close();
    /*TODO: Modify to better look*/
}

void Cartridge::CartridgePrintInfo()
{
    cout<<"Title: "<<header->Title<<endl;
    cout<<"New LicenseeCode: "<<header->NewLicenseeCode<<endl;
    cout<<"SGB Flag: "<<(U16)header->SGB_Flag<<endl;
    cout<<"Cartridge Type: "<<(U16)header->CartridgeType<<endl;
    cout<<"ROM size: "<<(U16)header->ROM_Size<<endl;
    cout<<"RAM Size: "<<(U16)header->RAM_Size<<endl;
    cout<<"Destination Code: "<<(U16)header->DestinationCode<<endl;    
    cout<<"OldLicensee Code: "<<(U16)header->OldLicenseeCode<<endl;
    cout<<"Version: "<<(U16)header->Version<<endl;
    cout<<"Header Checksum: "<<(U16)header->Checksum<<endl;
    cout<<"Global Checksum: "<<header->GlobalChecksum<<endl;
}

U8 Cartridge::CartridgeReadROM(U16 address)
{
    /*No MBC*/
    return data[address];
}

void Cartridge::CartridgeWriteROM(U16 address, U8 value)
{
    /*No MBC*/
    data[address] = value;
}

void Cartridge::CartridgeDebug()
{
    for(int j = 0; j < 500; j++)
    {
        std::cout<<"Adress: ";
        std::cout.setf(std::ios::hex, std::ios::basefield);
        std::cout<<0x0150 + j;
        std::cout.setf(std::ios::dec, std::ios::basefield);
        std::cout<<" = "<<(U16)data[j]<<std::endl;
    }
}

/*************************Interfaces*******************************/
void CartridgeInit()
{
    cart = new Cartridge();
}

Cartridge * CartridgeGetObj()
{
    return cart;
}
