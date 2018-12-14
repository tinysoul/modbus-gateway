/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ethernet.h
 * Author: 
 *
 * Created on 23 ноября 2018 г., 14:23
 */

#ifndef ETHERNET_H
#define ETHERNET_H

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <main.h> 
    
    
int createSocket(int port);
void closeSocket(int fd);
int readSocket(int F_ID, unsigned char *buff, int size);
int sendall(int s, unsigned char* buf, int len, int flags);


#endif /* ETHERNET_H */

