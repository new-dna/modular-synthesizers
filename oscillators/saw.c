/*
 * saw.c
 *
 * 	Created on: Oct 6, 2017
 *  Author: Nick McCarty
 * 
 */

 /* This is a basic saw wave oscillator using a FIR (low-pass) */
#include <stdio.h>
#include "saw.h"



//Member Functions
void Saw_initialize(Saw *saw) {
	saw->valIndex = 0;
	saw->paramIndex = 0;
	saw->outval = 0.0;
	//Initialize Filter

	uint8_t i;
	saw->filt.currIndex = 0;

	for (i=0; i<8; i++)
		saw->filt.tabs[i] = 0.0;

	saw->filt.params[0] = 0.01;
	saw->filt.params[1] = 0.05;
	saw->filt.params[2] = 0.12;
	saw->filt.params[3] = 0.32;
	saw->filt.params[4] = 0.32;
	saw->filt.params[5] = 0.12;
	saw->filt.params[6] = 0.05;
	saw->filt.params[7] = 0.01;

	saw->noteHz = 0.0;
	saw->amp = 500.0;

}


uint16_t Saw_getValue(Saw *saw) {
	float outval = 0.0;
	float val = 0.0;


	//compute new value from filter
	val = saw->curVal + saw->noteHz;


	//Limit bounds
	if (val > 1.0)
		val -= 2.0;

	saw->curVal = val;
	saw->valIndex = saw->filt.currIndex;
	saw->filt.tabs[saw->valIndex] = val;

	for (saw->paramIndex=0; saw->paramIndex<8; saw->paramIndex++)
	{
		outval += (saw->filt.params[saw->paramIndex]) * (saw->filt.tabs[(saw->valIndex+saw->paramIndex)&0x07]);
	}

	saw->valIndex++;
	saw->valIndex &= 0x07;

	saw->filt.currIndex = saw->valIndex;
	return (uint16_t)((int16_t)(saw->amp*outval));


}
