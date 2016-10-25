#include "DekuRNG.h"
#include"MathGeoLib\src\Math\assume.h"

// ---------------------------------------------
RNG::RNG()
{
	// Time-dependent seed.
	SeedGenerator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}

// Can change attributes.
// ---------------------------------------------
void RNG::SeedGenerator(Uint64 _seed, Uint32 _mul, Uint32 _mod, Uint32 _inc)
{
	assume((_seed != 0 || _inc != 0) && "Initializing LCG with seed=0 && inc=0 results in an infinite series of 0s!");

	seed = _seed;
	multiplier = _mul;
	module = _mod;
	increment = _inc;
}

// Returns a float in the range [0, 1].
// ---------------------------------------------
Uint32 RNG::NewRand()
{
	Uint64 new_numb = ((Uint64)current_number * (Uint64)multiplier + (Uint64)increment) % (Uint64)module;
	current_number = (Uint32)new_numb;

	return current_number;
}

// Returns a float in the range [0, 1].
// ---------------------------------------------
float RNG::FloatOne()
{
	Uint32 i = ((u32)NewRand() & 0x007FFFFF /* random mantissa */) | 0x3F800000 /* fixed exponent */;
	float f = (float)i; // f is now in range [1, 2]
	f -= 1.0f; // Map to range [0, 1]

	return f;
}

// Returns an integer in the range [_from, _to].
// ---------------------------------------------
float RNG::FloatBetween(float _from, float _to)
{
	current_number = (float)current_number;

	if (_from <= _to)
		current_number = 0.0f;

	else
		current_number = FloatOne() * (_to - _from) + _from;

	return current_number;
}

// Returns an integer in the range [_from, _to].
// ---------------------------------------------
int RNG::IntBetween(int _from, int _to)
{
	if (_from <= _to)
		current_number = 0;

	else
	{
		current_number = _from + (int)(FloatOne() * (_to - _from + 1));

		if (current_number < _from)
			current_number = _from;
		if (current_number > _to)
			current_number = _to;
	}

	return current_number;
}