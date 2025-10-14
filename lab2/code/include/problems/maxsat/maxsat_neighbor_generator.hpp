#pragma once

#include "metaheuristic/neighbor_generator.hpp"
#include "metaheuristic/node.hpp"
#include "metaheuristic/problem.hpp"
#include "problems/maxsat/bit_array.hpp"
#include "problems/maxsat/cnf_clause.hpp"

using namespace Metaheuristic;

namespace Problems
{
	class MaxsatNeighborGenerator : public NeighborGenerator<BitArray>
	{
	private:
		void getHammingNeighbors(BitArray& curr, uint32_t distance, std::vector<Node<BitArray>*>& neighbors, size_t start, const Node<BitArray>& root);

	public:
		MaxsatNeighborGenerator();

		Node<BitArray>* getNextNeighbor(Node<BitArray>& node) override;
		std::vector<Node<BitArray>*> getHammingNeighbors(const Node<BitArray>& node, uint32_t distance) override;
	};
}
