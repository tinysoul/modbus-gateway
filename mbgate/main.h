/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.h
 * Author: 
 *
 * Created on 29 ноября 2018 г., 14:15
 */

#ifndef MAIN_H
#define MAIN_H

#include <thread>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 


struct Data
{    
    int serial_id;            
    int uart_timeout;      
    int uart_baudrate;      
    int socket_id;            
    int socket_timeout;      
    
    pthread_t thread_id;    
    pthread_mutex_t mutex_id; 
};

#define version 1.23



#endif /* MAIN_H */

