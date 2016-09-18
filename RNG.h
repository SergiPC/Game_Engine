// ----------------------------------------------------
// Random Number Generator   --------------------------
// ----------------------------------------------------

#pragma once

#include "SDL\include\SDL.h"
#include <iostream>
#include <random>
#include <chrono>

// mersenne_twister_engine.
class RNG
{
private:

	Uint64 seed;
	Uint32 multiplier;
	Uint32 module;
	Uint32 increment;
	Uint32 current_number;

public:
	
	// Constructors.
	RNG();
	RNG(Uint64 _seed, Uint32 _multiplier = 69621, Uint32 _module = 0xffffffff, Uint32 _increment = 0)
	{
		SeedGenerator(_seed, _multiplier, _module, _increment);
	}

	// Time-dependent seed.
	void SeedGenerator(Uint64 _seed, Uint32 _multiplier = 69621, Uint32 _module = 0xffffffff, Uint32 _increment = 0);

	// Create the new random number
	Uint32 NewRand();

	// Returns a float in the range [0, 1].
	float FloatOne();

	// Returns an integer in the range [_from, _to].
	float FloatBetween(float _from, float _to);

	// Returns an integer in the range [_from, _to].
	int IntBetween(int _from, int _to);
};