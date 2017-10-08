/* saw.h
 *
 * 	Created on: Oct 6, 2017
 *  Author: Nick McCarty
 * 
 */


typedef struct {
	float tabs[8];
	float params[8];
	uint8_t currIndex;
} fir_8;

 typedef struct { 

		fir_8 filt;
		uint16_t valIndex;
		uint16_t paramIndex;
		float outval;
		float noteHz;
		float curVal;
		float amp;

 }Saw, *pSaw;

 uint16_t Saw_getValue(Saw *saw);
 void Saw_initialize(Saw *saw);
