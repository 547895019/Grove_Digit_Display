/*
 * TM1637.h
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

#ifndef TM1637_h
#define TM1637_h
#include <inttypes.h>
#include <Arduino.h>

#include "Digit_Display.h"
//************definitions for TM1637*********************
#define ADDR_AUTO  0x40
#define ADDR_FIXED 0x44

#define STARTADDR  0xc0

/**************definitions for brightness***********************/
#define  BRIGHT_DARKEST 0
#define  BRIGHT_TYPICAL 2
#define  BRIGHTEST      7

class TM1637 : public Digit_Display 
{
  public:
    uint8_t Cmd_SetData;
    uint8_t Cmd_SetAddr;
    uint8_t Cmd_DispCtrl;

    TM1637(uint8_t, uint8_t,uint8_t = 4);
    virtual int  refresh(uint8_t bitAddr,int8_t wr_data)//write 8bit data
	{
	  start();          //start signal sent to TM1637 from MCU
	  writeByte(ADDR_FIXED);//
	  stop();           //
	  start();          //
	  writeByte(BitAddr|STARTADDR);//
	  writeByte(wr_data);//
	  stop();            //
	  start();          //
	  writeByte(Cmd_DispCtrl);//
	  stop();           //
	}
    virtual int  refresh(int8_t wr_data[],int8_t wr_size)
	{
	  start();          //start signal sent to TM1637 from MCU
	  writeByte(ADDR_AUTO);//
	  stop();           //
	  start();          //
	  writeByte(Cmd_SetAddr);//
	  for(i=0;i < wr_size;i ++)
	  {
		writeByte(wr_data[i]);        //
	  }
	  stop();           //
	  start();          //
	  writeByte(Cmd_DispCtrl);//
	  stop();           //	
	}
    void set(uint8_t = BRIGHT_TYPICAL,uint8_t = ADDR_AUTO,uint8_t = STARTADDR);//To take effect the next time it displays.

  private:
    uint8_t Clkpin;
    uint8_t Datapin;
};
#endif