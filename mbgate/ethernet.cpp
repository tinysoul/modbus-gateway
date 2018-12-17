/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ethernet.cpp
 * Author: 
 * 
 * Created on 23 ноября 2018 г., 14:23
 */

#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h>   //for threading , link with lpthread
#include "ethernet.h"
#include "crc.h"
#include "main.h"
#include <iostream>

int socket_desc, client_sock , c;
struct sockaddr_in server , client;  

extern int max_client;



int createSocket(int port, int socket_timeout)
{

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    
    if (socket_desc == -1)
    {
        std::cout << "\r\n!!! Could not create socket \r\n" << std::endl;   
        return -1;        
    }
    else
    {
        //std::cout << "Socket created: "<< socket_desc << "\r\n" << std::endl;   
        std::cout << "\r\nSocket created "<< "\r\n" << std::endl;   
    }

    struct timeval timeout;      
    timeout.tv_sec = socket_timeout;
    timeout.tv_usec = 0;
    
    
    
    if (setsockopt (socket_desc, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)        
    {
        std::cout << "!!! setsockopt failed \r" << std::endl;           
    }

    if (setsockopt (socket_desc, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
    {
        std::cout << "!!! setsockopt failed \r" << std::endl;           
    }
    
         
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( port );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {        
        std::cout << "!!! Bind failed \r\n" << std::endl;           
        
        return -1;
    }    
    
    std::cout << "Bind done \r\n" << std::endl;           
    
     
    //Listen
    listen(socket_desc , max_client);
     
    //Accept and incoming connection
    std::cout << "Waiting for incoming connections...  \r\n" << std::endl;               
    c = sizeof(struct sockaddr_in);
    
    
    return 0;    
};


void closeSocket(int fd)
{
    shutdown(fd, SHUT_RDWR);
    close(fd);
};


int readSocket(int F_ID, unsigned char *buff, int size)
{
    fd_set set;
    struct timeval timeout;    
    int n = 0;
    int total = 0;
    int r = 0;
            

    r = recv(F_ID, buff, size, 0); /* there was data to read */
    
//    FD_ZERO(&set); /* clear the set */
//    FD_SET(F_ID, &set); /* add our file descriptor to the set */
//
//    timeout.tv_sec = 5;
//    timeout.tv_usec = 0;

//    n = select(F_ID + 1, &set, NULL, NULL, &timeout);
//    n = 1;
//
//    if (n == -1)
//    {
//            char *errmsg = strerror(errno);
//            printf("read: %s \r\n", errmsg);
//    }
//    else if(n == 0)
//    {         
//            std::cout << "!!! ETHERNET read timeout " << "\r" << std::endl; 
//    }
//    else
//    {
//            r = recv(F_ID, buff, size, 0); /* there was data to read */
//            while (total < size)
//            {
//                n = recv(F_ID, buff + total, size - total, 0); /* there was data to read */                
//                total += n;
//
//                if(n == -1 || n == 0) { break; }                                        
//            }           
//    }

//    return total;    
    return r;        
};

//int sendall(int s, unsigned char* buf, int len, int flags)
//{
//    int total = 0;
//    int n;
//
//    while(total < len)
//    {
//        n = send(s, buf+total, len-total, flags);
//        if(n == -1) { break; }
//        total += n;
//    }
//
//    return (n==-1 ? -1 : total);
//}

