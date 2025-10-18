#pragma once
#include "metaheuristic/algorithm.hpp"
#include "algorithms/next_ascent_hillclimb.hpp"

namespace Algorithms
{
	template<typename T>
	class VNAHillclimb: public NAHillclimb<T>
	{
	protected:
		uint32_t m_max_hamming_distance;

	public:
		VNAHillclimb(uint32_t max_hamming_distance, uint32_t multistarts);
		virtual ~VNAHillclimb() = default;

		virtual void evaluate(const std::vector<Node<T>*>&);
	};
}

#include "algorithms/variable_neighbourhood_ascent_hillclimb.ipp"
