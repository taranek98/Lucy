#include "../Cartridge/Cartridge.h"
#include "../CPU/CPU.h"
#include "../PPU/PPU.h"
#include "../Timer/Timer.h"
#include "../Interrupt/Interrupt.h"
#include "../Screen/Screen.h"
#include <iostream>
#include "../RAM/RAM.h"

using namespace std;

void init()
{
    CartridgeInit();
    CpuInit();
    PpuInit();
    TimerInit();
}

void loop()
{
    CartridgeGetObj() -> CartridgePrintInfo();
    while (true)
    {
        // cout<<"CPU"<<endl;
        // CpuGetObj() -> CpuDebugLogFilePrint();
        CpuGetObj() -> CpuStep();
        // CpuGetObj() -> CpuDebugPrint();
        // cout<<"PPU"<<endl;
        PpuGetObj() -> PpuStep(CpuGetObj() -> CpuGetCycles() * 4);
        // cout<<"Timer"<<endl;
        TimerGetObj() -> TimerStep(CpuGetObj() -> CpuGetCycles() * 4);  // 1 machine cycle = 4 clock cycle
        // cout<<"Interupt"<<endl;
        InterruptGetObj() -> InterruptStep();
        // cout<<"CPU Cycle: "<<CpuGetObj() -> CpuGetAllCycles()<<" ";
        /*TODO: Create corect defines*/
        // cout<<"Update"<<endl;
        if(ScreenGetObj() -> ScreenListen() == true) break;
        
        if(CpuGetObj() -> CpuGetAllCycles() > 69905)
        {
            ScreenGetObj() -> ScreenDebugBgTiles();
            CpuGetObj() ->CpuResetCycles();
            ScreenGetObj() -> ScreenUpdate();
            // char a;
            // cin>>a;
            // CpuGetObj() -> CpuDebugPrint();
        }
    }
}
/*TODO: Create easy to use structure of classes and objects*/
/*TODO: Create class of GB emulator*/

int main(int argc, char** argv)
{
    init();
    loop();
    return 0;
}