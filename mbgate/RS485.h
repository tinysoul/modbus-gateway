/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RS485.h
 * Author: savchenkors
 *
 * Created on 12 декабря 2018 г., 14:36
 */

#ifndef RS485_H
#define RS485_H

#include <linux/serial.h>

int set_rs485(int fd);

#endif /* RS485_H */

