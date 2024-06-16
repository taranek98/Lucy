all:
	g++ -o Lucy -Isrc/include -Lsrc/lib  Main/main.cpp CPU/CPU.CPP CPU/CPU_Instruction.cpp Bus/Bus.cpp Cartridge/Cartridge.cpp PPU/PPU.cpp PPU/Pixel.cpp PPU/PixelFifo.cpp  RAM/RAM.cpp Screen/Screen.cpp Timer/Timer.cpp Interrupt/Interrupt.cpp IO_Regs/IO_Regs.cpp LCD/LCD.cpp General/General.cpp DB/dbg.cpp -lmingw32 -lSDL2main -lSDL2 -std=c++0x