
//---------------------------------------------------
// conyconydev
// IDE : visual studio 2017
// 플랫폼 도구 집합 : Visual Studio 2017 (v141)
// 문자 집합 : 멀티바이트 문자 집합
// 명령줄 옵션 : /await /std:c++17
// 미리 컴파일된 헤더 미사용.
// 전처리기 명령어 추가 : _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "define.h"
#include "Memory.h"
#include "Cpu.h"
#include "HexViewer.h"

using namespace std;

// test function prototype
void memoryLoadAndStore_Test();
void memoryLocateAndFetch_Test();
void simulator_Test();

// test function define
void memoryLoadAndStore_Test()
{
	shared_ptr<Memory> myMemory(new Memory());

	HexViewer::viewMemory("데이터 저장 전 메모리 뷰", myMemory->getProgramHeapArea(), 0, 32);

	cout << endl;

	INT16 inputData = 0xF0AB;
	HexViewer::printHexData("입력 데이터 값 : ", HexViewer::makeHexData(inputData));
	myMemory->store(9, inputData);

	cout << endl;

	HexViewer::viewMemory("데이터 저장 후 메모리 뷰", myMemory->getProgramHeapArea(), 0, 32);

	cout << endl;

	INT16 loadedData = myMemory->load(9);
	HexViewer::printHexData("로드한 데이터 : ", HexViewer::makeHexData(loadedData));
}

void memoryLocateAndFetch_Test()
{
	shared_ptr<Memory> myMemory(new Memory());

	INT16 programCode[] = {
		0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007,
		0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F,
		0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017,
		0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x001E, 0x001F,
		0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
		0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F};

	HexViewer::viewMemory("입력 데이터", (BYTE *)programCode, 0, BUFF_SIZE(programCode, INT16));
	cout << endl;
	HexViewer::viewMemory("locate() 전 메모리 뷰", myMemory->getProgramTextArea(), 0, BUFF_SIZE(programCode, INT16));
	cout << endl;

	myMemory->locate(programCode, sizeof(programCode));
	HexViewer::viewMemory("locate() 후 메모리 뷰", myMemory->getProgramTextArea(), 0, BUFF_SIZE(programCode, INT16));
	cout << endl;

	cout << "fetch 데이터" << endl;

	for (int cnt = 0; cnt < 16; cnt++)
	{
		char title[64];
		string pcData;

		memset(title, 0x00, sizeof(title));
		sprintf(title, "fetch data[%d]", cnt);

		pcData = HexViewer::makeHexData(myMemory->fetch(cnt));
		HexViewer::printHexData(title, pcData);
	}
}

void simulator_Test()
{

	INT16 exampleProgram[] = {
		// 0x0000 MOV R4, 0xA0		>> 1011 1000 1010 0000
		0xB8A0,
		// 0x0002 MOV R5, 0x02		>> 1011 1010 0000 0002
		0xBA02,
		// 0x0004 LDR R1, R4, R5	>> 0001 0011 0000 0101
		0x1305,
		// 0x0006 ADD R2, R1, #4	>> 1000 0100 0110 0004
		0x8464,
		// 0x0008 SUB R3, R1, R2	>> 1001 0110 0100 0002
		0x9642,
		// 0x000A STR R3, R4, #4	>> 0100 0111 0000 0004
		0x4704};

	Memory memory;

	memory.locate(exampleProgram, sizeof(exampleProgram));

	HexViewer::viewMemory("Locate 된 Text Memory View", memory.getProgramTextArea(), 0, sizeof(exampleProgram));
	cout << endl;

	CPU cpu(&memory);
	INT16 IR = cpu.fetch();

	while (IR != 0x00)
	{
		INT16 dumpData[7];

		cpu.dump(dumpData, BUFF_SIZE(dumpData, INT16));
		HexViewer::viewRegister("Register view, before execute", dumpData);

		cpu.execute(IR);

		cpu.dump(dumpData, BUFF_SIZE(dumpData, INT16));
		HexViewer::viewRegister("Register view, after execute", dumpData);

		IR = cpu.fetch();

		cout << endl;
	}

	HexViewer::viewMemory("프로그램 실행 후 Memory Heap View", memory.getProgramHeapArea(), 0, 256);
}

int main(int argc, char *argv[])
{
	// Memory Locate 및 Fetch 명령어 테스트.
	//memoryLocateAndFetch_Test();

	// Memory Store 및 Load 명령어 테스트.
	//memoryLoadAndStore_Test();

	// cpu simulator test
	simulator_Test();
}
