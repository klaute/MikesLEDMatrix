#include "equalizer.h"
 
void equalizer_0()
{
} 
 
void equalizer_1()
{
 cube[4][1] += 0x18; 
 cube[4][2] += 0x18; 
} 
 
void equalizer_2()
{
 cube[4][0] += 0x18; 
 cube[4][1] += 0x24; 
 cube[4][2] += 0x24; 
 cube[4][3] += 0x18; 
} 
 
void equalizer_3()
{
 cube[1][7] += 0x18; 
 cube[4][0] += 0x24; 
 cube[4][1] += 0x42; 
 cube[4][2] += 0x42; 
 cube[4][3] += 0x24; 
 cube[4][4] += 0x18; 
} 
 
void equalizer_4()
{
 cube[1][6] += 0x3c; 
 cube[1][7] += 0x66; 
 cube[4][0] += 0xc3; 
 cube[4][1] += 0x81; 
 cube[4][2] += 0x81; 
 cube[4][3] += 0xc3; 
 cube[4][4] += 0x66; 
 cube[4][5] += 0x3c; 
} 
 
void equalizer_5()
{
 cube[1][5] += 0x3c; 
 cube[1][6] += 0x42; 
 cube[1][7] += 0x81; 
 cube[3][0] += 0x80; 
 cube[3][1] += 0x80; 
 cube[3][2] += 0x80; 
 cube[3][3] += 0x80; 
 cube[4][4] += 0x81; 
 cube[4][5] += 0x42; 
 cube[4][6] += 0x3c; 
 cube[5][0] += 0x01; 
 cube[5][1] += 0x01; 
 cube[5][2] += 0x01; 
 cube[5][3] += 0x01; 
} 
 
void equalizer_6()
{
 cube[0][6] += 0x80; 
 cube[0][7] += 0xc0; 
 cube[1][4] += 0x7e; 
 cube[1][5] += 0xc3; 
 cube[1][6] += 0x81; 
 cube[2][6] += 0x01; 
 cube[2][7] += 0x03; 
 cube[3][0] += 0x40; 
 cube[3][1] += 0x40; 
 cube[3][2] += 0x40; 
 cube[3][3] += 0x40; 
 cube[3][4] += 0xc0; 
 cube[3][5] += 0x80; 
 cube[4][5] += 0x81; 
 cube[4][6] += 0xc3; 
 cube[4][7] += 0x7e; 
 cube[5][0] += 0x02; 
 cube[5][1] += 0x02; 
 cube[5][2] += 0x02; 
 cube[5][3] += 0x02; 
 cube[5][4] += 0x03; 
 cube[5][5] += 0x01; 
} 
 
void equalizer_7()
{
 cube[0][5] += 0x80; 
 cube[0][6] += 0x40; 
 cube[0][7] += 0x20; 
 cube[1][3] += 0x7e; 
 cube[1][4] += 0x81; 
 cube[2][5] += 0x01; 
 cube[2][6] += 0x02; 
 cube[2][7] += 0x04; 
 cube[3][0] += 0x20; 
 cube[3][1] += 0x20; 
 cube[3][2] += 0x20; 
 cube[3][3] += 0x20; 
 cube[3][4] += 0x20; 
 cube[3][5] += 0x40; 
 cube[3][6] += 0x80; 
 cube[4][7] += 0x81; 
 cube[5][0] += 0x04; 
 cube[5][1] += 0x04; 
 cube[5][2] += 0x04; 
 cube[5][3] += 0x04; 
 cube[5][4] += 0x04; 
 cube[5][5] += 0x02; 
 cube[5][6] += 0x01; 
 cube[6][4] += 0x7e; 
} 
 
void equalizer_8()
{
 cube[0][3] += 0x80; 
 cube[0][4] += 0xc0; 
 cube[0][5] += 0x60; 
 cube[0][6] += 0x30; 
 cube[0][7] += 0x10; 
 cube[1][2] += 0xff; 
 cube[1][3] += 0x81; 
 cube[2][3] += 0x01; 
 cube[2][4] += 0x03; 
 cube[2][5] += 0x06; 
 cube[2][6] += 0x0c; 
 cube[2][7] += 0x08; 
 cube[3][0] += 0x10; 
 cube[3][1] += 0x10; 
 cube[3][2] += 0x10; 
 cube[3][3] += 0x10; 
 cube[3][4] += 0x10; 
 cube[3][5] += 0x30; 
 cube[3][6] += 0x60; 
 cube[3][7] += 0xc0; 
 cube[5][0] += 0x08; 
 cube[5][1] += 0x08; 
 cube[5][2] += 0x08; 
 cube[5][3] += 0x08; 
 cube[5][4] += 0x08; 
 cube[5][5] += 0x0c; 
 cube[5][6] += 0x06; 
 cube[5][7] += 0x03; 
 cube[6][0] += 0x80; 
 cube[6][4] += 0x81; 
 cube[6][5] += 0xff; 
 cube[7][2] += 0x01; 
} 
 
void equalizer_9()
{
 cube[0][2] += 0x80; 
 cube[0][3] += 0x40; 
 cube[0][4] += 0x20; 
 cube[0][5] += 0x10; 
 cube[0][6] += 0x08; 
 cube[0][7] += 0x08; 
 cube[1][1] += 0xff; 
 cube[2][2] += 0x01; 
 cube[2][3] += 0x02; 
 cube[2][4] += 0x04; 
 cube[2][5] += 0x08; 
 cube[2][6] += 0x10; 
 cube[2][7] += 0x10; 
 cube[3][0] += 0x08; 
 cube[3][1] += 0x08; 
 cube[3][2] += 0x08; 
 cube[3][3] += 0x08; 
 cube[3][4] += 0x08; 
 cube[3][5] += 0x08; 
 cube[3][6] += 0x10; 
 cube[3][7] += 0x20; 
 cube[5][0] += 0x10; 
 cube[5][1] += 0x10; 
 cube[5][2] += 0x10; 
 cube[5][3] += 0x10; 
 cube[5][4] += 0x10; 
 cube[5][5] += 0x10; 
 cube[5][6] += 0x08; 
 cube[5][7] += 0x04; 
 cube[6][0] += 0x40; 
 cube[6][1] += 0x80; 
 cube[6][6] += 0xff; 
 cube[7][2] += 0x02; 
 cube[7][3] += 0x01; 
} 
 
void equalizer_10()
{
 cube[0][0] += 0x80; 
 cube[0][1] += 0xc0; 
 cube[0][2] += 0x60; 
 cube[0][3] += 0x30; 
 cube[0][4] += 0x18; 
 cube[0][5] += 0x0c; 
 cube[0][6] += 0x04; 
 cube[0][7] += 0x04; 
 cube[1][0] += 0xff; 
 cube[2][0] += 0x01; 
 cube[2][1] += 0x03; 
 cube[2][2] += 0x06; 
 cube[2][3] += 0x0c; 
 cube[2][4] += 0x18; 
 cube[2][5] += 0x30; 
 cube[2][6] += 0x20; 
 cube[2][7] += 0x20; 
 cube[3][0] += 0x04; 
 cube[3][1] += 0x04; 
 cube[3][2] += 0x04; 
 cube[3][3] += 0x04; 
 cube[3][4] += 0x04; 
 cube[3][5] += 0x04; 
 cube[3][6] += 0x0c; 
 cube[3][7] += 0x18; 
 cube[5][0] += 0x20; 
 cube[5][1] += 0x20; 
 cube[5][2] += 0x20; 
 cube[5][3] += 0x20; 
 cube[5][4] += 0x20; 
 cube[5][5] += 0x20; 
 cube[5][6] += 0x30; 
 cube[5][7] += 0x18; 
 cube[6][0] += 0x30; 
 cube[6][1] += 0x60; 
 cube[6][2] += 0xc0; 
 cube[6][3] += 0x80; 
 cube[6][7] += 0xff; 
 cube[7][2] += 0x0c; 
 cube[7][3] += 0x06; 
 cube[7][4] += 0x03; 
 cube[7][5] += 0x01; 
} 
 
