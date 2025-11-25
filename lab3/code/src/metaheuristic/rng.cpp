#include "metaheuristic/rng.hpp"
#include <ctime>

using namespace Metaheuristic;

uint32_t RandomNumberGenerator::m_seed = 0;
std::minstd_rand RandomNumberGenerator::m_rng(0);

void RandomNumberGenerator::setSeed(uint32_t seed)
{
	m_seed = seed;
	m_rng = std::minstd_rand(seed);
}

void RandomNumberGenerator::setRandomSeed()
{
	setSeed(std::random_device{}());
}

uint64_t RandomNumberGenerator::seed()
{
	return m_seed;
}
std::minstd_rand& RandomNumberGenerator::randomEngine()
{
	return m_rng;
}

uint64_t RandomNumberGenerator::getULong()
{
	return (uint64_t)m_rng() | ((uint64_t)m_rng() << 31) | ((uint64_t)m_rng() << 62);
}

uint32_t RandomNumberGenerator::getUInt()
{
	return m_rng();
}

uint64_t RandomNumberGenerator::getULongRange(uint64_t start, uint64_t end)
{
	return start + (RandomNumberGenerator::getULong() % (end - start));
}

uint32_t RandomNumberGenerator::getUIntRange(uint32_t start, uint32_t end)
{
	return start + (RandomNumberGenerator::getUInt() % (end - start));
}

bool RandomNumberGenerator::roll(double p_accept)
{
	double random = static_cast<double>(RandomNumberGenerator::getULong()) / static_cast<double>(std::numeric_limits<unsigned long>::max());
	return random < p_accept;
}
