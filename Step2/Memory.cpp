
#include <memory>
#include <cassert>

#include "Memory.h"

Memory::Memory()
{
	memoryArea = new BYTE[MEMORY_SIZE];

	memset(memoryArea, 0x00, MEMORY_SIZE);
}

Memory::~Memory()
{
	delete[] memoryArea;
}

INT16 Memory::peek(INT32 address)
{
	// memory address check
	assert((address >= 0) && (address <= MEMORY_SIZE));
	INT16 data = 0;

	if (address < PROGRAM_HEAP_START_ADDR)
	{
		data = *(memoryArea + address);
	}
	else if (address < MEMORY_SIZE)
	{
		data = *(memoryArea + address);
	}

	return data;
}

void Memory::locate(INT16 *program, INT16 size)
{
	assert(programSize <= PROGRAM_TEXT_AREA_SIZE);

	memcpy(memoryArea, program, size);

	programSize = size / sizeof(INT16);
}

INT16 Memory::fetch(INT16 PC)
{
	INT16 IR;

	if (programSize > 0)
	{
		programSize--;
		memcpy(&IR, memoryArea + PC, sizeof(INT16));
		return IR;
	}
	else
	{
		return 0;
	}
}

INT16 Memory::load(INT16 address)
{
	assert((address >= 0) || address <= PROGRAM_HEAP_AREA_SIZE);

	INT16 *loadedData = (INT16 *)(memoryArea + PROGRAM_HEAP_START_ADDR + address);

	return *loadedData;
}

void Memory::store(INT16 address, INT16 data)
{
	// memory address check
	assert((address >= 0) && (address <= PROGRAM_HEAP_AREA_SIZE));

	void *storeAddr = (memoryArea + PROGRAM_HEAP_START_ADDR + address);

	memcpy((void *)storeAddr, (void *)&data, sizeof(WORD));
}

BYTE *Memory::getProgramTextArea()
{
	// Text 영역은 0x00000에서 시작.
	return memoryArea;
}

BYTE *Memory::getProgramHeapArea()
{
	// Heap 영역은 기본 주소 0x10000에서 시작하기 때문에 memory 시작 주소 + 0x10000하여 처리.
	return memoryArea + PROGRAM_HEAP_START_ADDR;
}
