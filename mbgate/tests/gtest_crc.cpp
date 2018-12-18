/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gtest_crc.cpp
 * Author: 
 *
 * Created on 17 декабря 2018 г., 17:13
 */

#include <stdlib.h>
#include <iostream>
#include "crc.h"
#include "gtest/gtest.h"

/*
 * Simple C++ Test Suite
 */


TEST(CRC_Test, crcTest)
{
    uint8_t arr[] = {0x01, 0x03, 0x07, 0xC8, 0x00, 0x7D};
    
    uint16_t result = CRC16((uint8_t*)&arr, 6);    
        
    EXPECT_EQ(result, 0x6105);
}




