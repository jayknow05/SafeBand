/* 
 * File:   eeprom.h
 * Author: Justin
 *
 * Created on December 2, 2017, 11:57 AM
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
uint8_t ReadByteEeprom(uint8_t data, uint16_t start_address);
uint8_t ReadEeprom(uint8_t * data, uint16_t length, uint16_t start_address);
uint8_t WriteEeprom(uint8_t * data, uint16_t length, uint16_t start_address);

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

