/*
 * TLSampleMethodTouchRead.cpp - Capacitive sensing implementation using
 * TouchRead method for TouchLibrary for Arduino Teensy 3.x
 * 
 * https://github.com/AdmarSchoonen/CVDSensor
 * Copyright (c) 2016 - 2017 Admar Schoonen
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "CVDSensor.h"
#include "TLSampleMethodTouchRead.h"

int TLSampleMethodTouchRead(struct CvdStruct * data, uint8_t nSensors, uint8_t ch,
		bool inv)
{
	int sample;
	
	/*
	 * touchRead() is only available on Teensy 3.x:
	 *
	 * Teensy 3.0: MK20DX128
	 * Teensy 3.1: MK20DX256
	 * Teensy LC:  MKL26Z64
	 * Teensy 3.2: MK20DX256
	 * Teensy 3.5: MK64FX512
	 * Teensy 3.6: MK64FX1M0
	*/

	#if !(defined(__MK20DX128__) || defined(__MK20DX256__) || \
		defined(__MKL26Z64__) || defined(__MK64FX512) || \
		defined(__MK64FX1M0__))

	/* Error! Not a Teensy! */
	sample = 0;

	#else
	struct CvdStruct * dCh;
	int ch_pin;

	if (inv) {
		/* Pseudo differential measurements are not supported */
		sample = 0;
	} else {
		dCh = &(data[ch]);
		ch_pin = dCh->pin;
		sample = touchRead(ch_pin);
	}

	#endif

	return sample;
}