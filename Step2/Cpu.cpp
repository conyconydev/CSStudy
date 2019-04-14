
#include <cassert>

#include "define.h"
#include "Cpu.h"

ASM_CMD CPU::getAsmCmd(INT16 IR)
{
	INT16 cmdBit;
	ASM_CMD asmCmd = NONE;

	cmdBit = (IR & 0xF000) >> 12;

	asmCmd = ASM_CMD(cmdBit);

	return asmCmd;
}

INT16 CPU::getDstReg(INT16 IR)
{
	INT16 dsgReg;

	dsgReg = (IR & 0x0E00) >> 9;

	return dsgReg;
}

INT16 CPU::getBaseReg(INT16 IR)
{
	INT16 baseReg;

	baseReg = (IR & 0x01E0) >> 6;

	return baseReg;
}

INT16 CPU::getOffsetReg(INT16 IR)
{
	INT16 regIdx;

	regIdx = (IR & 0x0007);

	return regIdx;
}

INT16 CPU::getOffsetValue(INT16 IR)
{
	INT16 value;

	value = (IR & 0x001F);

	return value;
}

INT16 CPU::getMovValue(INT16 IR)
{
	INT16 value;

	value = (IR & 0x01FF);

	return value;
}

CPU::CPU(Memory *memory)
{
	myMemory = memory;
}

CPU::~CPU()
{
}

void CPU::reset()
{
	memset(regs, 0x00, sizeof(regs));
}

INT16 CPU::fetch()
{
	regs[0] += 2;
	return myMemory->fetch(regs[0] - 2);
}

void CPU::execute(INT16 IR)
{
	ASM_CMD cmdBitCode = getAsmCmd(IR);

	INT16 dstReg;
	INT16 baseReg;
	INT16 offsetValue;
	INT16 offsetReg;

	// 명령어 decode 부분.
	switch (cmdBitCode)
	{
	case NONE:
		// NONE은 지원하지 않는 명령어
		assert(false);
		break;

	case LOAD_R:
		dstReg = getDstReg(IR);
		baseReg = getBaseReg(IR);
		offsetReg = getOffsetReg(IR);

		regs[dstReg] = myMemory->load(regs[baseReg] + regs[offsetReg]);
		break;

	case LOAD_V:
		dstReg = getDstReg(IR);
		baseReg = getBaseReg(IR);
		offsetValue = getOffsetValue(IR);

		regs[dstReg] = myMemory->load(regs[baseReg] + offsetValue);
		break;

	case STORE_R:
		// store의 경우 앞의 3bit가 src reg, 즉 원본 레지스터 이고,
		// 다음 3bit가 dst reg, 저장할 레지스터이다.
		// 기존 함수를 그대로 이용하기 위해서 baseReg,와 dstReg 서로 바꾸어 저장.
		dstReg = getBaseReg(IR);
		baseReg = getDstReg(IR);
		offsetReg = getOffsetReg(IR);

		myMemory->store(regs[dstReg] + regs[offsetReg], regs[baseReg]);
		break;

	case STORE_V:
		dstReg = getBaseReg(IR);
		baseReg = getDstReg(IR);
		offsetValue = getOffsetValue(IR);

		myMemory->store(regs[dstReg] + offsetValue, regs[baseReg]);
		break;

	case AND:
		dstReg = getDstReg(IR);
		baseReg = getBaseReg(IR);
		offsetReg = getOffsetReg(IR);

		regs[dstReg] = baseReg & offsetReg;
		break;

	case OR:
		dstReg = getDstReg(IR);
		baseReg = getBaseReg(IR);
		offsetReg = getOffsetReg(IR);

		regs[dstReg] = baseReg | offsetReg;
		break;

	case ADD_R:
		dstReg = getDstReg(IR);
		baseReg = getBaseReg(IR);
		offsetReg = getOffsetReg(IR);

		regs[dstReg] = regs[baseReg] + regs[offsetReg];
		break;

	case ADD_V:
		dstReg = getDstReg(IR);
		baseReg = getBaseReg(IR);
		offsetValue = getOffsetValue(IR);

		regs[dstReg] = regs[baseReg] + offsetValue;
		break;

	case SUB_R:
		dstReg = getDstReg(IR);
		baseReg = getBaseReg(IR);
		offsetReg = getOffsetReg(IR);

		regs[dstReg] = regs[baseReg] - regs[offsetReg];
		break;

	case SUB_V:
		dstReg = getDstReg(IR);
		baseReg = getBaseReg(IR);
		offsetValue = getOffsetValue(IR);

		regs[dstReg] = regs[baseReg] - offsetValue;
		break;

	case MOV:
		dstReg = getDstReg(IR);
		offsetValue = getMovValue(IR);

		regs[dstReg] = offsetValue;
		break;

	default:
		break;
	};
}

void CPU::dump(INT16 *dumpData, int dumpDataSize)
{
	// dumpData가 NULL 이거나 dumpDataSize가 레지스터 사이즈보다 적으면 assert 발생
	assert((dumpData != NULL) && (dumpDataSize == BUFF_SIZE(regs, INT16)));

	memcpy(dumpData, regs, sizeof(regs));
}
