/*
 * Digit_Display.h
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

#ifndef Digit_Display_h
#define Digit_Display_h

#include <inttypes.h>
#include <Arduino.h>


/**** definitions for the clock point of the digit tube *******/
#define POINT_ON   1
#define POINT_OFF  0

class Digit_Display
{
  public:
    boolean _PointFlag;     //_PointFlag=1:the clock point on
    void init(uint8_t = 4);        //To clear the display
    virtual int  refresh(uint8_t BitAddr,int8_t wr_data) = 0;//write 8bit data
    virtual int  refresh(int8_t wr_data[],int8_t wr_size) = 0;//write all data
    void display(int8_t DispData[]);
    void display(uint8_t BitAddr,int8_t DispData);
    void clearDisplay(void);
    void point(boolean PointFlag);//whether to light the clock point ":".To take effect the next time it displays.
    void coding(int8_t DispData[]);
    int8_t coding(int8_t DispData);
    void bitDelay(void);
	virtual ~Digit_Display() {};
  private:
	uint8_t Digitbits;

};
#endif
