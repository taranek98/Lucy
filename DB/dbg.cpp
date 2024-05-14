#include "dbg.h"
#include "../Bus/Bus.h"
#include <iostream>

static char dbg_msg[1024] = {0};
static int msg_size = 0;

void dbg_update() {
    if (BusRead(0xFF02) == 0x81) {
        char c = BusRead(0xFF01);

        dbg_msg[msg_size++] = c;

        BusWrite(0xFF02, 0);
    }
}

void dbg_print() {
    if (dbg_msg[0]) 
    {
        std::cout<<"DBG: "<< dbg_msg<<std::endl;
    }
}