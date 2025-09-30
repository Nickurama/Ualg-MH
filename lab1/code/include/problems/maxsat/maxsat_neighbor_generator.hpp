#pragma once

#include "metaheuristic/neighbor_generator.hpp"
#include "metaheuristic/node.hpp"
#include "metaheuristic/problem.hpp"
#include "problems/maxsat/bit_array.hpp"
#include "problems/maxsat/cnf_clause.hpp"

using namespace Metaheuristic;

namespace Problems
{
	class MaxsatNeighborGenerator : public Metaheuristic::NeighborGenerator<BitArray>
	{
	public:
		MaxsatNeighborGenerator();

		Node<BitArray>* getNextNeighbor(Node<BitArray>& node) override;
	};
}
