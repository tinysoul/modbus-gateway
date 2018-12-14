/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   serial.h
 * Author: 
 *
 * Created on 23 ноября 2018 г., 14:22
 */

#ifndef SERIAL_H
#define SERIAL_H

#include<iostream>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>  
#include <sys/ioctl.h>
#include <unistd.h>


int openPort(const char *COM_name, speed_t speed);
int readData(int F_ID, unsigned char *buff, int size, int timeout);
int sendData(int F_ID, unsigned char* buff, int len);
void closeCom(int F_ID);    


//int F_ID;
void setRTS(int F_ID);
void clrRTS(int F_ID);

speed_t get_baud(int baud);


#endif /* SERIAL_H */

