/**
 * @file SSI0.c
 *
 * @brief Source code for the SSI0 driver.
 *
 * This file contains the function definitions for the SSI0 driver.
 *
 * @note For more information regarding the SSI module, refer to the
 * Synchronous Serial Interface (SSI) section of the TM4C123GH6PM Microcontroller Datasheet.
 *   - Link: https://www.ti.com/lit/gpn/TM4C123GH6PM
 *
 * @note Assumes that the system clock (50 MHz) is used.
 *
 * @author
 */

#include "SSI0.h"

void SSI0_Init(void)
{
SYSCTL -> RCGCSSI |= 0x01;
	
	SYSCTL -> RCGCGPIO |= 0x01;
	
	GPIOA -> AFSEL |= 0x3C;
	

	
	GPIOA -> PCTL &= ~0x00FFFF00;
	
	GPIOA -> PCTL |= 0x00222200;
	
	GPIOA -> DEN |= 0x3C;
	
	SSI0-> CR1 &= ~0x02;
	
	SSI0 -> CR1 &= ~0x01;
	
	SSI0 -> CR1 &=~ 0x04;
	
	SSI0 -> CC &= ~0xF;
	
	SSI0 -> CPSR = 50;
	
	SSI0 -> CR0 &= ~ 0xFF00;
	
	SSI0 -> CR0 |= 0x0080;
	
	SSI0 -> CR0 |= 0x0040;
	
	SSI0 -> CR0 &= ~ 0x0030;
	
	SSI0 -> CR0 |= 0x000F;
	
	SSI0 -> CR1 |= 0x02;
	
}

uint16_t SSI0_Input_Data(void)
{
	while ((SSI0-> SR & SSI0_RX_FIFO_NOT_EMPTY_BIT_MASK) ==0);
	
	
	return (uint16_t) ( SSI0->DR);
}

void SSI0_Output_Data(uint16_t data)
{
	while ((SSI0->SR & SSI0_TX_FIFO_EMPTY_BIT_MASK) == 0);
	
	SSI0 -> DR = data;
}

uint16_t PMOD_ALS_READ(void)
{
	SSI0_Output_Data(0xAAAA);
	
	uint16_t pmod_als_raw_data = SSI0_Input_Data();
	
	uint8_t light_level = (pmod_als_raw_data >>5) & 0xFF;
	
	return light_level;
}
