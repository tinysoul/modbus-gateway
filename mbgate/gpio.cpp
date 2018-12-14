/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gpio.cpp
 * Author: 
 * 
 * Created on 12 декабря 2018 г., 11:19
 */

#include "gpio.h"

#define IMX_GPIO_NR(port, index)    ((((port)-1)*32)+((index)&31))



led_t Led ={IMX_GPIO_NR(1, 13)};

void InitLed(led_t* led)
{
  int fd;
  int gpio = led->gpio;


  fd = open("/sys/class/gpio/export", O_WRONLY);

  sprintf(led->buf, "%d", gpio);

  write(fd, led->buf, strlen(led->buf));

  close(fd);

  //Set out direction
  sprintf(led->buf, "/sys/class/gpio/gpio%d/direction", gpio);

  fd = open(led->buf, O_WRONLY);

  /* Set out direction */
  write(fd, "out", 3);

  close(fd);

  sprintf(led->path_value, "/sys/class/gpio/gpio%d/value",led->gpio);
}

void LedOn(led_t* led)
{
  int fd=0;

  /* LED ON */

  fd = open(led->path_value, O_WRONLY);

  /* Set GPIO high status */
  write(fd, "1", 1);

  close(fd);
  printf("LED ON\n");
}

void LedOff(led_t* led)
{
  int fd=0;
  /* LED OFF */

  fd = open(led->path_value, O_WRONLY);


  /* Set GPIO low status */
  write(fd, "0", 1);

  close(fd);
  printf("LED OFF\n");
}

