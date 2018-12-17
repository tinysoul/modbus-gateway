/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RS485.cpp
 * Author: savchenkors
 * 
 * Created on 12 декабря 2018 г., 14:36
 */

#include "RS485.h"
#include <linux/serial.h>
#include <sys/ioctl.h>

int set_rs485(int fd)
{
  struct serial_rs485 rs485conf;

  /* Enable RS485 mode: */
  rs485conf.flags |= SER_RS485_ENABLED;

  /* Set logical level for RTS pin equal to 1 when sending: */
  rs485conf.flags |= SER_RS485_RTS_ON_SEND;

  /* Set logical level for RTS pin equal to 1 after sending: */
//  rs485conf.flags |= SER_RS485_RTS_AFTER_SEND;

/* or, set logical level for RTS pin equal to 0 after sending: */
  rs485conf.flags &= ~(SER_RS485_RTS_AFTER_SEND);

  if (ioctl (fd, TIOCSRS485, &rs485conf) < 0) {
      /* Error handling. See errno. */
      return -1;
    }
  return 0;
}
