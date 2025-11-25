#pragma once

#include <cstdint>
// #include <vector>
#include <random>

namespace Metaheuristic
{
	class RandomNumberGenerator
	{
	private:
		static uint32_t m_seed;
		static std::minstd_rand m_rng;

	public:
		static void setSeed(uint32_t seed);
		static void setRandomSeed();
		static uint64_t seed();
		static std::minstd_rand& randomEngine();
		static uint64_t getULong();
		static uint32_t getUInt();
		static uint64_t getULongRange(uint64_t start, uint64_t end);	
		static uint32_t getUIntRange(uint32_t start, uint32_t end);	
		static bool roll(double p_accept);
	};
}
