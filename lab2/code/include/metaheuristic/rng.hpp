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
	};
}
