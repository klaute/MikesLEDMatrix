#ifndef BLOCK0_H
#define BLOCK0_H

#include <stdbool.h>

#include "ledcube.h"

typedef unsigned char uchar;

volatile uchar qBlock[7];
volatile uchar falldown;

void blockEqualizerBold(uchar*, bool);

#endif
