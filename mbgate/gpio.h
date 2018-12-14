/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gpio.h
 * Author: 
 *
 * Created on 12 декабря 2018 г., 11:19
 */

#ifndef GPIO_H
#define GPIO_H

typedef struct
{
  int gpio;
  char path_value[100];
  char buf[100];
}led_t;

void InitLed(led_t* led);
void LedOn(led_t* led);
void LedOff(led_t* led);

#endif /* GPIO_H */

