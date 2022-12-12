#pragma once

#include <iostream>
#include <string>
#include <stdlib.h>
#include <Windows.h>
#include "SerialPort.h"
#include "windows.h"
#include "Morser.h"
#include <vector>

int main();
int toArd(); //string command
int toggleArdLED();
int attrToArd(uint8_t intCommand);