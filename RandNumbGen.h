// ----------------------------------------------------
// Random Number Generator   --------------------------
// ----------------------------------------------------

#pragma once

#include <iostream>
#include <random>
#include <chrono>

// mersenne_twister_engine
template<class VALUE>
class RandNumbGen
{
private:

	VALUE current_rand_number;

public:
	
	// Constructors
	RandNumbGen()
	{}

	// Time-dependent seed
	void SeedGenerator()
	{
		std::mt19937_64 rng;
		uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
		rng.seed(ss);
	}

	// Distribution between two float
	float RandOne()
	{
		// Initialize the random number generator with time-dependent seed
		SeedGenerator();

		std::uniform_real_distribution<float> unif(0.0f, 1.0f);
		
		// Ready to generate random numbers
		current_rand_number = unif(rgn);
		
		return current_rand_number;
	}

	// Distribution between two float
	VALUE RandBetween(const VALUE& _from, const VALUE& _to)
	{
		// Initialize the random number generator with time-dependent seed
		SeedGenerator();

		std::uniform_real_distribution<VALUE> unif(_from, _to);

		// Ready to generate random numbers
		current_rand_number = unif(rgn);

		return current_rand_number;
	}
};