/*
 * MBI5026.cpp
 * A library for the 4 digit display
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Frankie.Chu
 * Create Time: 9 April,2012
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "MBI5026.h"
#include <Arduino.h>

MBI5026::MBI5026(uint8_t Clk, uint8_t Data, uint8_t Latch,uint8_t Bits)
{
  Clkpin = Clk;
  Datapin = Data;
  Latchpin = Data;
  pinMode(Clkpin,OUTPUT);
  pinMode(Datapin,OUTPUT);
  pinMode(Latchpin,OUTPUT);
  init(Bits);
  dataBufferSize = Bits;
  dataBuffer = new int8_t[dataBufferSize];
}

void MBI5026::writeByte(int8_t wr_data)
{
  uint8_t i;
  for(i=0;i<8;i++)        //sent 8bit data
  {
    digitalWrite(Clkpin,LOW);
    if(wr_data & 0x01)digitalWrite(Datapin,HIGH);//LSB first
    else digitalWrite(Datapin,LOW);
	wr_data >>= 1;
	bitDelay();
    digitalWrite(Clkpin,HIGH);
	bitDelay();
  }
  
}
//send start signal to MBI5026
void MBI5026::latch(void)
{
  digitalWrite(Latchpin,LOW);//send start signal to MBI5026
  digitalWrite(Latchpin,HIGH);
  digitalWrite(Latchpin,LOW);
}


