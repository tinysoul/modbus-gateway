/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   serial.cpp
 * Author: 
 * 
 * Created on 23 ноября 2018 г., 14:22
 */

#include<iostream>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>  
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/time.h>
#include <chrono>
#include "serial.h"
#include "main.h"
#include <pthread.h>


/*----------------------------------------------------------------------------
 Открыть COM порт
 COM_name: путь к устройству, например: /dev/ttyS0 или  /dev/ttyUSB0 - для USB
 speed: скорость, например: B9600, B57600, B115200
 ----------------------------------------------------------------------------*/
int openPort(const char *COM_name, speed_t speed)
{
    
        int F_ID = open(COM_name, O_RDWR | O_NOCTTY );
        if (F_ID == -1)
        {
                char *errmsg = strerror(errno);
                printf("!!! UART open port error %s\n", errmsg);                
                return -1;
        }
        else
        {
            std::cout << "UART port open: " << F_ID << "\r\n" << std::endl;   
        }
        struct termios options; /*структура для установки порта*/
        
        tcgetattr(F_ID, &options); /*читает пораметры порта*/

        //options.c_cflag &= ~CBAUD;    //Remove current BAUD rate
        //options.c_cflag |= BOTHER;
        
        //ioctl( F_ID, TIOCGSERIAL, &options );
  	//options.flags |= ASYNC_LOW_LATENCY;
  	//ioctl( F_ID, TIOCSSERIAL, &options );
        
        cfsetispeed(&options, speed); /*установка read скорости порта*/
        cfsetospeed(&options, speed); /*установка write скорости порта*/
                
        options.c_cc[VTIME] = 5; /*Время ожидания байта 100 мс. */
        options.c_cc[VMIN] = 0; /*минимальное число байт для чтения*/


        options.c_cflag &= ~PARENB; /*бит четности не используется*/
        options.c_cflag &= ~CSTOPB; /*1 стоп бит */
        options.c_cflag &= ~CSIZE;  /*Размер байта*/
        options.c_cflag |= CS8;  /*8 бит*/

        options.c_lflag = 0;
        options.c_oflag &= ~OPOST;  /*Обязательно отключить постобработку*/



         //
         // Input flags - Turn off input processing
         //
         // convert break to null byte, no CR to NL translation,
         // no NL to CR translation, don't mark parity errors or breaks
         // no input parity check, don't strip high bit off,
         // no XON/XOFF software flow control
         //
         options.c_iflag &= ~(IGNBRK | BRKINT | ICRNL |
                             INLCR | PARMRK | INPCK | ISTRIP | IXON);
         
         //
         // Output flags - Turn off output processing
         //
         // no CR to NL translation, no NL to CR-NL translation,
         // no NL to CR translation, no column 0 CR suppression,
         // no Ctrl-D suppression, no fill characters, no case mapping,
         // no local output processing
         //
         // config.c_oflag &= ~(OCRNL | ONLCR | ONLRET |
         //                     ONOCR | ONOEOT| OFILL | OLCUC | OPOST);
         options.c_oflag = 0;        
         
         //
         // No line processing
         //
         // echo off, echo newline off, canonical mode off, 
         // extended input processing off, signal chars off
         //
         options.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);         
        
        
        
        tcsetattr(F_ID, TCSANOW, &options); /*сохранения параметров порта*/

        return F_ID;
}


int readData(int F_ID, unsigned char *buff, int size, int timeout_value)
{
        fd_set set;
        struct timeval timeout;    
        int n = 0;
        int total = 0;
        
        
        FD_ZERO(&set); /* clear the set */
        FD_SET(F_ID, &set); /* add our file descriptor to the set */
        
        timeout.tv_sec = 0;
        timeout.tv_usec = timeout_value;
        
        
        
        
        if (F_ID > 0)
        {
            
            n = select(F_ID + 1, &set, NULL, NULL, &timeout);                                

            if (n == -1)
            {
                char *errmsg = strerror(errno);
                printf("!!! read uart error: %s \r\n", errmsg);
                
            }
            else if(n == 0)
            {         
                std::cout << "!!! UART read timeout " << "\r" << std::endl; 
            }
            else
            {                
                while (total < size)
                {
                    n = read(F_ID, buff + total, size - total); /* there was data to read */                
                    total += n;

                    if(n == -1 || n == 0) { break; }                                        
                }                
            }
        
        }
        
        return total;
        //return (n==-1 ? -1 : total);
}
/*----------------------------------------------------------------------------
 Отправить в COM порт данные
 buff - буфер данных для отправки
 len - количество отправляемых байт
 ----------------------------------------------------------------------------*/
int sendData(int F_ID, unsigned char* buff, int len)
{       
        int n = write(F_ID, buff, len);
         
        if (n < 0)
        {
                char *errmsg = strerror(errno);
                printf("send: %s \r\n", errmsg);
        }
        
        
                
        return n;
}
/*----------------------------------------------------------------------------
 Закрыть COM порт
 ----------------------------------------------------------------------------*/
void closeCom(int F_ID)
{
        close(F_ID);
        F_ID = -1;
        return;
}

/*----------------------------------------------------------------------------
 Установить RTS
 ----------------------------------------------------------------------------*/
void setRTS(int F_ID)
{
        int status;
        ioctl(F_ID, TIOCMGET, &status);
        status |= TIOCM_RTS;
        ioctl(F_ID, TIOCMSET, &status);
}
/*----------------------------------------------------------------------------
Очистить RTS
 ----------------------------------------------------------------------------*/
void clrRTS(int F_ID)
{
        int status;
        ioctl(F_ID, TIOCMGET, &status);
        status &= ~TIOCM_RTS;
        ioctl(F_ID, TIOCMSET, &status);
}

/*----------------------------------------------------------------------------
Конвертирование параметра скорости в тип speed_t
 ----------------------------------------------------------------------------*/
speed_t get_baud(int baud)
{
    switch (baud) {
    case 9600:
        return B9600;
    case 19200:
        return B19200;
    case 38400:
        return B38400;
    case 57600:
        return B57600;
    case 115200:
        return B115200;
    case 230400:
        return B230400;
    case 460800:
        return B460800;
    case 500000:
        return B500000;
    case 576000:
        return B576000;
    case 921600:
        return B921600;
    case 1000000:
        return B1000000;
    case 1152000:
        return B1152000;
    case 1500000:
        return B1500000;
    case 2000000:
        return B2000000;
    case 2500000:
        return B2500000;
    case 3000000:
        return B3000000;
    case 3500000:
        return B3500000;
    case 4000000:
        return B4000000;
    default: 
        return -1;
    }
}