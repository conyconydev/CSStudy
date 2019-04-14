

#ifndef MEMORY_H
#define MEMORY_H

#include <Memory.h>

#include "define.h"

class Memory
{
private:
	// 요구 사항 일부
	// - 내부적으로 프로그램을 로딩할 메모리 공간(PROGRAM_TEXT영역)을 216 * 2바이트로 할당한다.
	// - 데이터를 읽고 쓸수 있는 공간(PROGRAM_HEAP영역)을 216 * 2바이트로 할당한다.

	// Memory를 다른 두영역으로 나누지 않고 하나의 영역으로 범위를 잡았습니다.
	// Text 영역과 Heap 영역 나눈다면 문제에서 요구하는 각 영역의 시작 주소 및 증가되는 주소를 파악하기 힘드므로
	// 하나의 영역으로 선언한 후 각 영역의 사이즈로 구분하여 처리했습니다.
	BYTE *memoryArea;
	INT16 programSize;

public:
	Memory();
	~Memory();

	INT16 peek(INT32 addres);
	void locate(INT16 *program, INT16 size);
	INT16 fetch(INT16 PC);
	INT16 load(INT16 address);
	void store(INT16 address, INT16 data);

	// Memory 확인용 함수.
	BYTE *getProgramTextArea();
	BYTE *getProgramHeapArea();
};

#endif