#include "includes.h"
#include "NorFlash.h"

void Font_Read_8x16_ASCII( uint8_t  *pString, uint8_t  *pdat )
{
    uint16_t ASCIICode;
	uint32_t addr = 0x04B7C0;

	ASCIICode = pString[0];
	if( ASCIICode >= 0x20 && ASCIICode <= 0x7E )
	{
        addr = addr + ((ASCIICode - 0x20) << 4);
	}

	SpiFlash_ReadBytes( addr, pdat, 16);
}

void Font_Read_6x12_ASCII( uint8_t  *pString, uint8_t  *pdat )
{
    uint16_t ASCIICode;
	uint32_t addr = 0x076d40;

	ASCIICode = pString[0];

	if( ASCIICode >= 0x20 && ASCIICode <= 0x7E )
	{
        addr = addr + ((ASCIICode - 0x20) * 12);
	}

	SpiFlash_ReadBytes( addr, pdat, 12 );
}


void Font_Read_5x7_ASCII( uint8_t  *pString, uint8_t  *pdat )
{
    uint16_t ASCIICode;
	uint32_t addr = 0x04bfc0;

	ASCIICode = pString[0];

	if( ASCIICode >= 0x20 && ASCIICode <= 0x7E )
	{
        addr = addr + ((ASCIICode - 0x20) << 3);
	}

	SpiFlash_ReadBytes( addr, pdat, 5 );
}