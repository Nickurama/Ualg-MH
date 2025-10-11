#pragma once

#include "metaheuristic/neighbor_generator.hpp"
#include "metaheuristic/node.hpp"
#include "metaheuristic/problem.hpp"
#include "metaheuristic_extra/hamming_neighbor_generator.hpp"
#include "problems/maxsat/bit_array.hpp"
#include "problems/maxsat/cnf_clause.hpp"

using namespace Metaheuristic;
using namespace MetaheuristicExtra;

namespace Problems
{
	class MaxsatNeighborGenerator : public NeighborGenerator<BitArray>, public HammingNeighborGenerator<BitArray>
	{
	public:
		MaxsatNeighborGenerator();

		Node<BitArray>* getNextNeighbor(Node<BitArray>& node) override;
		virtual std::vector<Node<BitArray>*> getHammingNeighbors(const Node<BitArray>& node, uint32_t distance) override;
	};
}
