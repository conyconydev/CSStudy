

#ifndef DEFINE_H
#define DEFINE_H

#include <stdio.h>

// type define
#define BYTE unsigned char
#define WORD unsigned short
#define INT16 WORD
#define INT32 unsigned int

#define MEMORY_SIZE 0x20000
#define PROGRAM_TEXT_AREA_SIZE MEMORY_SIZE/2
#define PROGRAM_HEAP_AREA_SIZE PROGRAM_TEXT_AREA_SIZE

#define PROGRAM_TEXT_START_ADDR 0
#define PROGRAM_HEAP_START_ADDR PROGRAM_TEXT_AREA_SIZE

// macro function
#define BUFF_SIZE(buff, unit_size) (sizeof(buff)/sizeof(unit_size))

#endif