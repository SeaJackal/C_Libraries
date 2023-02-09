#ifndef BIT_ACCESS_
#define BIT_ACCESS_

#include <stdint.h>

#define GET_NULL_BIT(A) A & 0b00000001
#define GET_FIRST_BIT(A) A & 0b00000010
#define GET_SECOND_BIT(A) A & 0b00000100
#define GET_THIRD_BIT(A) A & 0b00001000
#define GET_FOURTH_BIT(A) A & 0b00010000
#define GET_FIFTH_BIT(A) A & 0b00100000
#define GET_SIXTH_BIT(A) A & 0b01000000
#define GET_SEVENTH_BIT(A) A & 0b10000000

#define SET_NULL_BIT_0(A) A = A&0b11111110
#define SET_FIRST_BIT_0(A) A = A&0b11111101
#define SET_SECOND_BIT_0(A) A = A&0b11111011
#define SET_THIRD_BIT_0(A) A = A&0b11110111
#define SET_FOURTH_BIT_0(A) A = A&0b11101111
#define SET_FIFTH_BIT_0(A) A = A&0b11011111
#define SET_SIXTH_BIT_0(A) A = A&0b10111111
#define SET_SEVENTH_BIT_0(A) A = A&0b01111111

#define SET_NULL_BIT_1(A) A = A|0b00000001
#define SET_FIRST_BIT_1(A) A = A|0b00000010
#define SET_SECOND_BIT_1(A) A = A|0b00000100
#define SET_THIRD_BIT_1(A) A = A | 0b00001000
#define SET_FOURTH_BIT_1(A) A = A | 0b00010000
#define SET_FIFTH_BIT_1(A) A = A | 0b00100000
#define SET_SIXTH_BIT_1(A) A = A | 0b01000000
#define SET_SEVENTH_BIT_1(A) A = A | 0b10000000

uint8_t getBit(uint8_t byte, uint8_t bit_number);
uint8_t setBitNull(uint8_t byte, uint8_t bit_number);
uint8_t setBitOne(uint8_t byte, uint8_t bit_number);

#endif