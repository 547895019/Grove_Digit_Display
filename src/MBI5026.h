/*
 * MBI5026.h
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

#ifndef MBI5026_h
#define MBI5026_h
#include <inttypes.h>
#include <Arduino.h>

#include "Digit_Display.h"


class MBI5026 : public Digit_Display 
{
  public:


    MBI5026(uint8_t, uint8_t,uint8_t,uint8_t = 4);
	
	void writeByte(int8_t wr_data);
	void latch(void);
	
    virtual void  refresh(uint8_t BitAddr,int8_t wr_data)//write 8bit data
	{
		uint8_t i;
	  dataBuffer[BitAddr] = wr_data;
	   for(i=0;i < dataBufferSize;i ++)
	  {
		writeByte(dataBuffer[i]);        //
	  }
	  latch();           //       //	
	}
    virtual void  refresh(int8_t wr_data[],int8_t wr_size)
	{
	  uint8_t i;
	  for(i=0;i < wr_size;i ++)
	  {
		dataBuffer[i] = wr_data[i];        //
	  }
	  for(i=0;i < wr_size;i ++)
	  {
		writeByte(dataBuffer[i]);        //
	  }
	  latch();           //       //	
	}
	~MBI5026() {
		delete [] dataBuffer;
	};
  private:
    uint8_t Clkpin;
    uint8_t Datapin;
	uint8_t Latchpin;
	int8_t *dataBuffer;
	uint8_t dataBufferSize;
};
#endif
