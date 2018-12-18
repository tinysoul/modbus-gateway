/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   crc.h
 * Author: 
 *
 * Created on 29 ноября 2018 г., 13:20
 */

#ifndef CRC_H
#define CRC_H

#include <stdint.h>
    
//uint16_t CRC16(const uint8_t *pcBlock, uint32_t len);
uint16_t CRC16(uint8_t *adr_buffer, uint32_t byte_cnt);
uint16_t CRC16_F(const uint8_t *pcBlock, uint32_t len);


#endif /* CRC_H */

