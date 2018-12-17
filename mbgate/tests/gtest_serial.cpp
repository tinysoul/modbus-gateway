/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gtest_serial.cpp
 * Author: 
 *
 * Created on 17 декабря 2018 г., 16:34
 */

#include <stdlib.h>
#include <iostream>
#include "serial.h"
#include "gtest/gtest.h"

/*
 * Simple C++ Test Suite
 */


TEST(SerialTest, testOpenPort) 
{	
    const char* COM_name = "/dev/virtualcom1";    
    speed_t speed = B9600;        
    int F_ID = -1;
    
    system("(socat -dd -dd pty,link=/dev/virtualcom1,raw,echo=0  pty,link=/dev/virtualcom2,raw,echo=0 ) &");    
    sleep(5);
    system("chmod 777 /dev/virtualcom1"); 
    F_ID = openPort(COM_name, speed);    
    closeCom(F_ID);    
    
    EXPECT_NE(F_ID, -1);
}

TEST(SerialTest, testSendData) 
{
    int len = 10;
    int result = 0;    
    const char* buff = "0123456789";    
    const char* COM_name = "/dev/virtualcom1";    
    speed_t speed = B9600;        
    int F_ID = -1;
    
    system(" (socat -dd -dd pty,link=/dev/virtualcom1,raw,echo=0  pty,link=/dev/virtualcom2,raw,echo=0 ) &");        
    sleep(5);
    system("chmod 777 /dev/virtualcom1");    
    
    F_ID = openPort(COM_name, speed);
    
    result = sendData(F_ID, (unsigned char*) buff, len);
        
    closeCom(F_ID);
    
    EXPECT_EQ(len, result);    
}

TEST(SerialTest, testReadData) 
{
    int len = 10;
    int result_1 = 0;    
    int result_2 = 0;    
    const char* buff = "0123456789";    
    unsigned char read_buff[len];    
    const char* COM_name1 = "/dev/virtualcom1";    
    const char* COM_name2 = "/dev/virtualcom2";
    speed_t speed = B9600;        
    int F_ID_1 = -1;
    int F_ID_2 = -1;
    
    system(" (socat -dd -dd pty,link=/dev/virtualcom1,raw,echo=0  pty,link=/dev/virtualcom2,raw,echo=0 ) &");        
    sleep(5);
    system("chmod 777 /dev/virtualcom1");    
    system("chmod 777 /dev/virtualcom2");    
    
    F_ID_1 = openPort(COM_name1, speed);
    F_ID_2 = openPort(COM_name2, speed);
    
    result_1 = sendData(F_ID_1, (unsigned char*) buff, len);    
    result_2 = readData(F_ID_2, read_buff, len, 1000000);
    
    closeCom(F_ID_1);
    closeCom(F_ID_2);    
    
    system("pkill socat");
    
    EXPECT_EQ(len, result_2);    
}

//int main(int argc, char *argv[])
//{
//	::testing::InitGoogleTest(&argc, argv);
//	return RUN_ALL_TESTS();
//}



