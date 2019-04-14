

#ifndef LOGGER_H
#define LOGGER_H

#include "define.h"

using namespace std;

class HexViewer {
public:
	static string makeHexString(INT16* data, int dataLen);
	static string makeHexData(INT16 data);
	static void printHexString(string title, string hexString);
	static void printHexData(string title, string hexData);
	static void viewMemory(string title, BYTE* memory, int startAddress, int memorySize);
	static void viewRegister(string title, INT16* regs);
};

#endif