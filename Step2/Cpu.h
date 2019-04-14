
#ifndef CPU_H
#define CPU_H

#include "define.h"
#include "Memory.h"

// 명렁어 비트코드
typedef enum _ASM_CMD
{
	NONE = 0b0000,
	LOAD_R = 0b0001,
	LOAD_V = 0b0010,
	STORE_R = 0b0011,
	STORE_V = 0b0100,
	AND = 0b0101,
	OR = 0b0110,
	ADD_R = 0b0111,
	ADD_V = 0b1000,
	SUB_R = 0b1001,
	SUB_V = 0b1010,
	MOV = 0b1011
} ASM_CMD;

class CPU
{
private:
	Memory *myMemory;
	INT16 regs[7]; // regs[0]을 PC와 매칭, regs[1]부터 R1레지스터와 차례대로 매칭.

	ASM_CMD getAsmCmd(INT16 IR);
	INT16 getDstReg(INT16 IR);
	INT16 getBaseReg(INT16 IR);
	INT16 getOffsetReg(INT16 IR);
	INT16 getOffsetValue(INT16 IR);
	INT16 getMovValue(INT16);

public:
	CPU(Memory *memory);
	~CPU();

	void reset();
	INT16 fetch();
	void execute(INT16 IR);
	void dump(INT16 *dumpData, int dumpDataSize);
};

#endif