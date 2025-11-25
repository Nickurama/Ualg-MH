#pragma once

#include "metaheuristic/neighbor_generator.hpp"
#include "metaheuristic/node.hpp"
#include "metaheuristic/problem.hpp"
#include "problems/maxsat/bit_array.hpp"
#include "problems/maxsat/cnf_clause.hpp"

using namespace Metaheuristic;

namespace Problems
{
	class MaxsatProblem; // forward declaration

	class MaxsatNeighborGenerator : public NeighborGenerator<BitArray>
	{
	private:
		MaxsatProblem& m_problem;

		void getHammingNeighbors(BitArray& curr, uint32_t distance, std::vector<Node<BitArray>*>& neighbors, size_t start, const Node<BitArray>& root);

	public:
		MaxsatNeighborGenerator(MaxsatProblem& p);

		Node<BitArray>* getNextNeighbor(Node<BitArray>& node) override;
		void getHammingNeighbors(const Node<BitArray>& node, uint32_t distance, std::vector<Node<BitArray>*>& neighbors) override;
		Node<BitArray>* getHammingNeighbor(const Node<BitArray>& node, uint32_t distance) override;
		Node<BitArray>* getHammingNeighborUnderDistance(const Node<BitArray>& node, uint32_t distance) override;
		std::unique_ptr<Node<BitArray>> getRandomNode() override;
	};
}
