#ifndef __DEKU_RNG_H__
#define __DEKU_RNG_H__

#include "Globals.h"
#include "SDL\include\SDL.h"

#define RAND_MAX 4000
#define RAND_MIN 0

class DekuRNG
{
public:

	// Constructor
	DekuRNG();
	void Start();
	float RandZeroAndOne();
	void RandMinMax();


private:
	
};
#endif //__DEKU_RNG_H__