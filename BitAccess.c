#include "BitAccess.h"

uint8_t getBit(uint8_t byte, uint8_t bit_number) 
{
	return (byte & (1 << bit_number));
}
uint8_t setBitNull(uint8_t byte, uint8_t bit_number) 
{
	return (byte & ~(1 << bit_number));
}
uint8_t setBitOne(uint8_t byte, uint8_t bit_number) 
{
	return (byte | (1 << bit_number));
}