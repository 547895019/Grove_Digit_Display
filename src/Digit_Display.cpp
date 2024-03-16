/*
 * Digit_Display.cpp
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

#include "Digit_Display.h"
#include <Arduino.h>
static int8_t TubeTab[] = {0x3f,0x06,0x5b,0x4f,
                           0x66,0x6d,0x7d,0x07,
                           0x7f,0x6f,0x77,0x7c,
                           0x39,0x5e,0x79,0x71};//0~9,A,b,C,d,E,F


void Digit_Display::init(void)
{
  clearDisplay();
}

void Digit_Display::digitbits(uint8_t Bits)
{
  Digitbits = Bits;
}


//display function.Write to full-screen.
void Digit_Display::display(int8_t DispData[])
{
  int8_t *SegData = new int8_t[Digitbits];
  uint8_t i;
  for(i = 0;i < Digitbits;i ++)
  {
    SegData[i] = DispData[i];
  }
  coding(SegData);
  refresh(SegData,Digitbits);
  delete [] SegData;
}
//******************************************
void Digit_Display::display(uint8_t BitAddr,int8_t DispData)
{
  int8_t SegData;
  SegData = coding(DispData);
  refresh(BitAddr,SegData);
}

void Digit_Display::clearDisplay(void)
{
  uint8_t i;
  for(i = 0;i < Digitbits;i ++)
  {
	display(i,0x7f);  
  }
}

//Whether to light the clock point ":".
//To take effect the next time it displays.
void Digit_Display::point(boolean PointFlag)
{
  _PointFlag = PointFlag;
}
void Digit_Display::coding(int8_t DispData[])
{
  uint8_t PointData;
  if(_PointFlag == POINT_ON)PointData = 0x80;
  else PointData = 0;
  for(uint8_t i = 0;i < Digitbits;i ++)
  {
    if(DispData[i] == 0x7f)DispData[i] = 0x00;
    else DispData[i] = TubeTab[DispData[i]] + PointData;
  }
}
int8_t Digit_Display::coding(int8_t DispData)
{
  uint8_t PointData;
  if(_PointFlag == POINT_ON)PointData = 0x80;
  else PointData = 0;
  if(DispData == 0x7f) DispData = 0x00 + PointData;//The bit digital tube off
  else DispData = TubeTab[DispData] + PointData;
  return DispData;
}
void Digit_Display::bitDelay(uint32_t delays)
{
	delayMicroseconds(delays);
}
