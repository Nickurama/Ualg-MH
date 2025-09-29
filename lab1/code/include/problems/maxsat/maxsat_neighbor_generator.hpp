#pragma once

#include "metaheuristic/problem.hpp"
#include "problems/maxsat/bit_array.hpp"
#include "problems/maxsat/cnf_clause.hpp"

namespace Problems
{
	class MaxsatNeighborGenerator : public Metaheuristic::NeighborGenerator<BitArray>
	{
	public:
		MaxsatNeighborGenerator();

		// state-space
		std::vector<std::unique_ptr<Node<BitArray>>> getAllNeighbors(const Node<BitArray>& node);

		// randomness
		std::vector<std::unique_ptr<Node<BitArray>>> getRandomNeighbors(const Node<BitArray>& node, int k);
		std::unique_ptr<Node<BitArray>> getRandomNeighbor(const Node<BitArray>& node);
		std::unique_ptr<Node<BitArray>> getRandomNode();

		// iterative
		bool hasNextNeighbor(Node<BitArray>);
		std::unique_ptr<Node<BitArray>> getNextNeighbor(Node<BitArray>);

		// genetic
		std::unique_ptr<Node<BitArray>> mutate(const Node<BitArray>& node, double rate);
		std::unique_ptr<Node<BitArray>> crossover(const Node<BitArray>& first, const Node<BitArray>& second);
	};
}
