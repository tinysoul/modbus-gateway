
#include <cstdlib>
#include<iostream>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>  
#include <sys/ioctl.h>
#include <unistd.h>
#include "serial.h"
#include "ethernet.h"
#include <thread>
#include <vector>
#include <algorithm>
#include <mutex>
#include "main.h"
#include "crc.h"
#include "connection_handler.h"
#include <semaphore.h>
#include <linux/serial.h>
#include "RS485.h"
#include <signal.h>


extern int socket_desc , client_sock , c;
extern struct sockaddr_in server , client;

Data* data = new Data[1];    

pthread_t thread_id;
pthread_t thread_id_2;
pthread_mutex_t mutex;    
sem_t semaphore; 
speed_t baud;

int sock_res = 0;
int i_struct = 0;
char* uart_port;
int uart_baud_rate = 0;
int uart_timeout = 0;
int socket_port = 0;
int socket_timeout = 0;

int max_client = 1;

int debug_mode = 0;


void sig_handler(int signum)
{
    printf("\nReceived signal %d. \n", signum);

//SIGTERM
//SIGSTOP
//SIGINT
//SIGQUIT
    
    if(signum ==2)
    {
        printf("Close TCP socket and UART port.\n\n", signum);
        closeSocket(data[i_struct].socket_id);
        closeCom(data[i_struct].serial_id);
        //pthread_exit(data[i_struct].thread_id);
        exit(0);
    }
    
};



int main(int argc, char** argv) 
{    
    
    //Assign signal handler
    signal(SIGINT, sig_handler);
    

    
    
    if (argc > 1)
    {
        
        if (strcmp(argv[1],"-h")==0) //Help
        {
            std::cout << "\r\nmbgate: Transparent Modbus TCP-RTU Gateway.\r\n" << std::endl;
            std::cout << "Usage: \r" << std::endl;         
            std::cout << "-p UART port;\r" << std::endl;         
            std::cout << "-b UART baud rate;\r" << std::endl;         
            std::cout << "-t UART timeout, ms.;\r" << std::endl;         
            std::cout << "-sp TCP socket port;\r" << std::endl;         
            std::cout << "-st TCP socket timeout, min.;\r"<< std::endl;         
            std::cout << "-d Run with default settings. UART: /dev/ttymxc5, baud rate: 115200, timeout: 500 ms. TCP: socket port: 1100, socket connection timeout: 300 sec. \r\n" << std::endl;         
            std::cout << "Example: mbgate -b 9600 \r\n" << std::endl;  
                    
            return 0;
        }        
        else if (strcmp(argv[1],"-d")==0) //Default
        {
            std::cout <<"\nDefault parameters loaded. UART: /dev/ttymxc5, baud rate: 115200, timeout: 100 ms. Socket port: 1100, timeout: 5 min. \r\n" << std::endl;   
            
            data[i_struct].uart_timeout = 300000; //300 мс.
            data[i_struct].serial_id = openPort("/dev/ttymxc5", B115200);           
            data[i_struct].socket_timeout = 300; //5 мин.            
            sock_res = createSocket(1100, data[i_struct].socket_timeout);            
        }        
        else
        {

            for (int i = 1; i < argc; i++)      
            {    
                if (strcmp(argv[i],"-p")==0) 
                {
                    uart_port = argv[i+1];                
                    std::cout << "Debug: uart_port: " << uart_port << "\r\n" << std::endl;   
                }
                else if (strcmp(argv[i],"-b")==0) 
                {
                    uart_baud_rate = atoi(argv[i+1]);                
                    std::cout << "Debug: uart_baud_rate: " << uart_baud_rate << "\r\n" << std::endl;   
                }
                else if (strcmp(argv[i],"-t")==0) 
                {
                    uart_timeout = atoi(argv[i+1]);                
                    std::cout << "Debug: uart_timeout: " << uart_timeout << "\r\n" << std::endl;   
                }            
                else if (strcmp(argv[i],"-sp")==0) 
                {
                    socket_port = atoi(argv[i+1]);                
                    std::cout << "Debug: socket_port: " << socket_port << "\r\n" << std::endl;   
                }              
                else if (strcmp(argv[i],"-st")==0) 
                {
                    socket_timeout = atoi(argv[i+1]);                
                    std::cout << "Debug: socket_timeout: " << socket_timeout << "\r\n" << std::endl;   
                }
                else if (strcmp(argv[i],"-debug")==0) 
                {   
                    debug_mode = atoi(argv[i+1]);                
                    std::cout << "Debug mode: " << debug_mode << "\r\n" << std::endl;   
                }                                 
            }


            if(uart_timeout != 0)
            {            
                data[i_struct].uart_timeout = uart_timeout; 
            }
            else
            {
                data[i_struct].uart_timeout = 500000; //500 мс.
            }


            if(uart_port == NULL && uart_baud_rate != 0)
            {                
                data[i_struct].serial_id = openPort("/dev/ttymxc5", get_baud(uart_baud_rate));                   
                uart_port = "/dev/ttymxc5";
            }
            else if(uart_port != NULL && uart_baud_rate != 0)
            {                
                data[i_struct].serial_id = openPort(uart_port, get_baud(uart_baud_rate));   
            }
            else if(uart_port != NULL && uart_baud_rate == 0)
            {                
                data[i_struct].serial_id = openPort(uart_port, B115200);   
            }            
            
            

            if (socket_timeout != 0)
            {
                data[i_struct].socket_timeout = socket_timeout; 
            }
            else
            {
                data[i_struct].socket_timeout = 300; //5 мин.
            }
            

            if (socket_port != 0)
            {
                //Create socket (port)    
                sock_res = createSocket(socket_port, data[i_struct].socket_timeout);       
            }
            else
            {
                sock_res = createSocket(1100, data[i_struct].socket_timeout);
            }        
        }
    }
    else
    {
        std::cout << "\nmbgate " << version << ": Transparent Modbus TCP-RTU Gateway. Use -d to run with default parameters. For help, type: mbgate -h \r\n" << std::endl;        

        return 0;
    }
    
    

    //Init RS485 hardware  
    set_rs485(data[i_struct].serial_id);
    
    
    data[i_struct].uart_baudrate = uart_baud_rate;
    
    
            
    while ( true )
    {
        //Accept new socket (Await a connection on socket_desc. When a connection arrives, open a new socket to communicate with it)
        data[i_struct].socket_id = accept( socket_desc, (struct sockaddr *)&client, (socklen_t*)&c ); 


        if (data[i_struct].socket_id > 0)                 
        {                   
            std::cout << "TCP connection accepted: " << data[i_struct].socket_id << "\r\n" << std::endl;
        }
        else
        {
            std::cout << "TCP connection failed. " << data[i_struct].socket_id <<  " Exit. \r"  << std::endl;     
            return 0;
        }


        
        //Create thread
        if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &data[i_struct] ) >= 0 )
        {
            data[i_struct].thread_id = thread_id;      
            
            std::cout << "Handler assigned \r\n" << std::endl;
            
            pthread_join(data[i_struct].thread_id, NULL);        
        }
        else 
        {
            std::cout << "Could not create thread \r\n" << std::endl;
            return 1;
        }

        
        
    }
    
    return 0;
}

