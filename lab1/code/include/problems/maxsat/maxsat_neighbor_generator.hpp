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

		// state-space
		// std::vector<std::unique_ptr<Node<BitArray>>> getAllNeighbors(const Node<BitArray>& node) override;
		//
		// // randomness
		// std::vector<std::unique_ptr<Node<BitArray>>> getRandomNeighbors(const Node<BitArray>& node, int k) override;
		// std::unique_ptr<Node<BitArray>> getRandomNeighbor(const Node<BitArray>& node) override;
		// std::unique_ptr<Node<BitArray>> getRandomNode() override;
		//
		// // iterative
		// bool hasNextNeighbor(Node<BitArray>) override;
		Node<BitArray>& getNextNeighbor(Node<BitArray>& node) override;
		//
		// // genetic
		// std::unique_ptr<Node<BitArray>> mutate(const Node<BitArray>& node, double rate) override;
		// std::unique_ptr<Node<BitArray>> crossover(const Node<BitArray>& first, const Node<BitArray>& second) override;
	};
}
