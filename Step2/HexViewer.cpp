
#include <iostream>
#include <string>

#include "HexViewer.h"

using namespace std;

string HexViewer::makeHexString(INT16 *data, int dataLen)
{
	string hexString;
	char logFmt[32];

	for (int cnt = 0; cnt < dataLen; cnt++)
	{
		unsigned char *hex = (unsigned char *)(data + cnt);

		if (cnt % 8 == 0)
		{
			hexString.append("\n");
		}

		memset(logFmt, 0x00, sizeof(logFmt));
		sprintf(logFmt, "%.02X %.02X ", *(hex), *(hex + 1));
		hexString.append(logFmt);
	}

	return hexString;
}

string HexViewer::makeHexData(INT16 data)
{
	string hexData;
	char logFmt[32];

	unsigned char *hex = (unsigned char *)(&data);
	sprintf(logFmt, "%.02X %.02X ", *(hex), *(hex + 1));
	hexData.append(logFmt);

	return hexData;
}

void HexViewer::printHexString(string title, string hexString)
{
	cout << title.c_str() << " : " << hexString.c_str() << endl;
}

void HexViewer::printHexData(string title, string hexData)
{
	cout << title.c_str() << " : " << hexData.c_str() << endl;
}

// Memory View WORD(2byte)단위로 Little Endian으로 표시.
// Offset은 16바이트 단위로 표시하며 기준은 startAddress를 0으로 지정.
// offset는 동일 오브젝트 안에서 오브젝트 처음부터 주어진 요소나 지점까지의 변위차를 나타내는 정수형이다.
void HexViewer::viewMemory(string title, BYTE *memory, int startAddress, int memorySize)
{
	string memoryData;
	char offset[64];
	char logFmt[128];

	memoryData.append("[" + title + "]\n");

	for (int cnt = 0; cnt < memorySize; cnt++)
	{

		if (cnt % 16 == 0)
		{
			if (cnt != 0)
			{
				memoryData.append("\n");
			}

			memset(offset, 0x00, sizeof(offset));
			sprintf(offset, "0x%.08x | ", cnt);
			memoryData.append(offset);
		}

		memset(logFmt, 0x00, sizeof(logFmt));

		unsigned char *hex = (unsigned char *)(memory + startAddress + cnt);
		sprintf(logFmt, "%.02X ", *hex);
		memoryData.append(logFmt);
	}

	cout << memoryData << endl;
}

void HexViewer::viewRegister(string title, INT16 *regs)
{
	string registerData;
	char buff[64];

	registerData.append("[" + title + "]\n");

	memset(buff, 0x00, sizeof(buff));
	sprintf(buff, "[regs0] : %s (PC)\n", makeHexData(regs[0]).c_str());

	registerData.append(buff);

	for (int idx = 1; idx < 7; idx++)
	{
		memset(buff, 0x00, sizeof(buff));
		sprintf(buff, "regs[%d] : %s\n", idx, makeHexData(*(regs + idx)).c_str());
		registerData.append(buff);
	}

	cout << registerData << endl;
}
