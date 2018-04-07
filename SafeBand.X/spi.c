/*
 * SPI driver for PIC16F1459 and PIC24FJ32GB002
 *
 * Copyright (C) 2013 Alan Ott <alan@signal11.us>
 *                    Signal 11 Software
 *
 * 2013-02-08
 *
 *  M-Stack is free software: you can redistribute it and/or modify it under
 *  the terms of the GNU Lesser General Public License as published by the
 *  Free Software Foundation, version 3; or the Apache License, version 2.0
 *  as published by the Apache Software Foundation.  If you have purchased a
 *  commercial license for this software from Signal 11 Software, your
 *  commerical license superceeds the information in this header.
 *
 *  M-Stack is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 *  License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this software.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  You should have received a copy of the Apache License, verion 2.0 along
 *  with this software.  If not, see <http://www.apache.org/licenses/>.
 */

#include "spi.h"
#include "board.h"

#if defined(__XC8) || defined (__XC16__) || defined (__XC32__)
	#include <xc.h>
#else
	#error "Compiler not supported"
#endif

#define MIN(x,y) (((x)<(y))?(x):(y))

/* The device uses mode 0,0. SDI/SDO leads SCK, and SCK is idle LOW.
   CKP = 0, CKE = 1 */

void init_spi1(void)
{
    spi1_sclk = _RPOUT_SCK1OUT;
    spi1_mosi = _RPOUT_SDO1;
    _SDI1R = spi1_miso;    

    SPI1CON1Lbits.CKE = 1; /* Data is valid before clock edge on SCK */
    SPI1CON1Lbits.SSEN = 0; /* Slave Select (chip select) is manual (GPIO) */
    SPI1CON1bits.MSTEN = 1; /* 1= SPIn is master mode. */
    SPI1CON2bits.FRMEN = 0; /* Framed support is disabled (do it manually)*/
    SPI1CON1Lbits.ENHBUF = 0; /* Enhanced Buffer Disabled */
    SPI1CON1Lbits.MODE = 0;
    SPI1STATLbits.SPIROV = 0; /* Clear overflow indication */
    //SPI1BRGLbits.BRG = 0;
    SPI1BRGL = 0;
    SPI1BRGH = 0;
    SPI1CON1bits.SPIEN = 1; /* Enable SPI */
}

uint8_t spi_transfer(uint8_t out)
{
    SPI1BUFL = out;
    while (!SPI1STATLbits.SPIRBF);
     
    return SPI1BUFL; 
}

uint8_t spi_transfer_block(uint8_t *out_buf, uint8_t *in_buf, uint8_t len)
{
	uint16_t i;
	if (in_buf && out_buf) {
		for (i = 0; i < len; i++) {
			in_buf[i] = spi_transfer(out_buf[i]);
		}
	}
	else if (!in_buf && out_buf) {
		for (i = 0; i < len; i++) {
			spi_transfer(out_buf[i]);
		}
	}
	else if (in_buf && !out_buf) {
		for (i = 0; i < len; i++) {
			in_buf[i] = spi_transfer(0xFF);
		}
	}
	else if (!in_buf && !out_buf) {
		/* No in or out buffer; just move the clock line. */
		for (i = 0; i < len; i++) {
			spi_transfer(0xFF);
		}
	}

	return 0;
}
