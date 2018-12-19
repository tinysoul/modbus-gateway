/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   connection_handler.cpp
 * Author: 
 * 
 * Created on 30 ноября 2018 г., 8:39
 */

#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h>   //for threading , link with lpthread
#include "connection_handler.h"
#include "crc.h"
#include "main.h"
#include "ethernet.h"
#include <semaphore.h>
#include <iostream>
#include "serial.h"
#include <syslog.h> 



extern sem_t semaphore; 
extern int debug_mode;

uint8_t ethernetReadBuffer[300];
uint8_t ethernetWriteBuffer[300];
uint8_t serialReadBuffer[300];
uint8_t serialWriteBuffer[300];    


int crc = 0;
int serial_size = 0;
int eth_read_size = 0;    
int respond_uart_size = 0;
int result = 0;
int bytes_available = 0;
int expected_number_of_bytes = 0;
int serial_byte_to_write = 0;    


void* connection_handler(void* parameters)
{
    

    struct Data* data = (struct Data*)parameters;    
   
    std::cout << "Start thread \r" << std::endl;        
    syslog(LOG_NOTICE | LOG_PID, "Start thread");              
    
    while( true )
    {        
        
////////Receive a message from Ethernet-client <--

        eth_read_size = readSocket( data->socket_id, ethernetReadBuffer, sizeof(ethernetReadBuffer) );           
    
        
                
        if (eth_read_size == 0 || eth_read_size == -1)
        {            
            closeSocket(data->socket_id);    
            if (eth_read_size == 0) 
            {
                std::cout << "Client disconnect socket\r" << std::endl;                
                syslog(LOG_NOTICE | LOG_PID, "Client disconnect socket");              
            }
            if (eth_read_size == -1) 
            {
                std::cout << "Socket timeout \r" << std::endl;                
                syslog(LOG_WARNING | LOG_PID, "Socket timeout");              
            }
            
            std::cout << "Socket closed \r" << std::endl;                
            syslog(LOG_NOTICE | LOG_PID, "Socket closed");              
            
            std::cout << "Thread exit \r" << std::endl;              
            syslog(LOG_NOTICE | LOG_PID, "Thread exit");              
            
            pthread_exit(0);
        }
        
        //Transfer PDU to uart 
        for(int i = 0; i < sizeof(serialWriteBuffer)-6; i++) serialWriteBuffer[i] = ethernetReadBuffer[i+6];
        
        //Calculate byte for write operation to uart
        serial_byte_to_write = ((ethernetReadBuffer[4] >> 8) + ethernetReadBuffer[5]) + 2;
        
        //Calculate CRC for transmission by UART
        

        if (serialWriteBuffer[1] == 0x10)
        {
            expected_number_of_bytes = ((serialWriteBuffer[4] >> 8) + serialWriteBuffer[5]) * 2;
            
            crc = CRC16( (uint8_t*) &serialWriteBuffer, 11 );        
            serialWriteBuffer[11] = crc;
            serialWriteBuffer[12] = crc >> 8;                
        }
        else 
        {
            expected_number_of_bytes = ((serialWriteBuffer[4] >> 8) + serialWriteBuffer[5]) * 2;
            
            crc = CRC16( (uint8_t*) &serialWriteBuffer, 6 );        
            serialWriteBuffer[6] = crc;
            serialWriteBuffer[7] = crc >> 8;                    
        }        
        
        
        //Debug
        //for(int i = 0; i < 12; i++) printf("%x ", ethernetReadBuffer[i]);            
        //std::cout << "read from ethernet: " << eth_read_size << "\r" << std::endl;                        

        
            
            
        
//////////Transmit a message to UART -->
         
        //tcflush(data->serial_id, TCOFLUSH | TCIFLUSH);              
        

        result = sendData( data->serial_id, serialWriteBuffer, serial_byte_to_write );

        if(debug_mode == 1)
        {
            //Debug
            for(int i = 0; i < serial_byte_to_write; i++) printf("%x ", serialWriteBuffer[i]);            
            std::cout << "--> write to uart: " << result << "\r" << std::endl;                        
        }

        //tcflush(data->serial_id, TCOFLUSH | TCIFLUSH);              
        //tcdrain(data->serial_id);
        //usleep(500000);
            
            
        
            
        
//////////Receive a message from UART-client <--
         
        //ioctl(data->serial_id, FIONREAD, &bytes_available);                      


        serial_size = readData( data->serial_id, &serialReadBuffer[0], expected_number_of_bytes+5, data->uart_timeout );
                

        if(debug_mode == 1)
        {
            //Debug
            for(int i = 0; i < serial_size; i++) printf("%x ", serialReadBuffer[i]);            
            std::cout << "<-- read from uart: " << serial_size << "\r" << std::endl;                                               
        }
                               
       

        //Modbus TCP Transaction ID
        ethernetWriteBuffer[0] = ethernetReadBuffer[0];
        ethernetWriteBuffer[1] = ethernetReadBuffer[1];
        //Modbus TCP Protocol ID
        ethernetWriteBuffer[2] = 0x00;
        ethernetWriteBuffer[3] = 0x00;    
        
        if (serial_size > 0) respond_uart_size = serial_size - 2;  //Calculate size of packet without CRC
        //else if (serial_size == 0) respond_uart_size = 3;          //Size of packet for error message

        //Copy serial data to eth
        //for(int i = 0; i < respond_uart_size; i++) ethernetWriteBuffer[i+6] = serialReadBuffer[i]; 
        
        //Find start of the normal frame if the recieved packet was broken
        if(serialReadBuffer[0] != serialWriteBuffer[0] && serialReadBuffer[1] != serialWriteBuffer[1]) 
        {
            for(int i = 0; i < respond_uart_size-1; i++) 
            {
                if (serialReadBuffer[i] == serialWriteBuffer[0] && serialReadBuffer[i+1] == serialWriteBuffer[1])
                {
                    for(int j = 0; j < respond_uart_size; j++) ethernetWriteBuffer[j+6] = serialReadBuffer[j+i]; 
                    
                    if(debug_mode == 1)
                    std::cout << "\n!!! Recieved broken frame, the shift is: " << i << " byte\r\n" << std::endl;                                               
                }                 
            }
        }
        else
        {
            for(int i = 0; i < respond_uart_size; i++) ethernetWriteBuffer[i+6] = serialReadBuffer[i]; 
        }
            
    
        //Modbus TCP Length
        ethernetWriteBuffer[4] = respond_uart_size >> 8; 
        ethernetWriteBuffer[5] = respond_uart_size;         

        
                               

//////////Send the message to Ethernet-client -->

        if (serial_size > 3)            
        result = send( data->socket_id, &ethernetWriteBuffer[0], respond_uart_size + 6, 0 );                            

        
        //Debug
        //for(int i = 0; i < respond_uart_size+6; i++) printf("%x ", ethernetWriteBuffer[i]);            
        //std::cout << "<-- write to ethernet: " << result << "\r" << std::endl;                                               
        
        
//        //Clear the buffers
//        for(int i = 0; i < sizeof(ethernetWriteBuffer); i++) 
//        {
//            ethernetWriteBuffer[i] = 0;
//            ethernetReadBuffer[i] = 0;
//            serialReadBuffer[i] = 0;
//            serialWriteBuffer[i] = 0;
//        }
        
        
    }         
}; 

