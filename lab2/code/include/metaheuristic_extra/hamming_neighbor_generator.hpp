#pragma once

#include "metaheuristic/neighbor_generator.hpp"
#include "metaheuristic/node.hpp"
#include <memory>
#include <vector>

namespace MetaheuristicExtra
{
	template<Hashable T>
	class HammingNeighborGenerator
	{
	protected:
		HammingNeighborGenerator() = default;

	public:
		// pure virtual class
		HammingNeighborGenerator(const HammingNeighborGenerator&) = delete;
		HammingNeighborGenerator& operator=(const HammingNeighborGenerator&) = delete;
		HammingNeighborGenerator(const HammingNeighborGenerator&&) = delete;
		HammingNeighborGenerator& operator=(const HammingNeighborGenerator&&) = delete;
		virtual ~HammingNeighborGenerator() {};

		// hamming distances
		virtual std::vector<Node<T>*> getHammingNeighbors(const Node<T>& node, uint32_t distance);
	};
}

#include "metaheuristic_extra/hamming_neighbor_generator.ipp"
