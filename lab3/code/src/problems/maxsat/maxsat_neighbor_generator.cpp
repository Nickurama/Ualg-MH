#include "problems/maxsat/maxsat_neighbor_generator.hpp"
#include "metaheuristic/rng.hpp"
#include "problems/maxsat/maxsat_node.hpp"
#include <iostream>

using namespace Problems;

MaxsatNeighborGenerator::MaxsatNeighborGenerator(MaxsatProblem& p) :
	m_problem(p)
{
}

Node<BitArray>* MaxsatNeighborGenerator::getNextNeighbor(Node<BitArray>& node)
{
	// dangerous! but very efficient.
	const_cast<BitArray&>(node.value()).increment();
	return &node;
	// BitArray next_arr = node.value(); // copies
	// next_arr.increment();
	// return &node.createChild<MaxsatNode>(std::move(next_arr));
}

void MaxsatNeighborGenerator::getHammingNeighbors(const Node<BitArray>& node, uint32_t distance, std::vector<Node<BitArray>*>& neighbors)
{
	// iterate through all distance-wise permutations
	size_t bits = node.value().size();
	neighbors.reserve(bits); // WARNING should be bits^distance no?
	BitArray init_curr = node.value();
	getHammingNeighbors(init_curr, distance, neighbors, 0, node);
}

void MaxsatNeighborGenerator::getHammingNeighbors(BitArray& curr, uint32_t distance, std::vector<Node<BitArray>*>& neighbors, size_t start, const Node<BitArray>& root)
{
	size_t bits = curr.size();

	if (distance <= 1) // base case
	{
		for (size_t i = start; i < bits; i++)
		{
			BitArray n = curr; // copies
			n.flip(i);
			Node<BitArray>* node = &root.createChild<MaxsatNode>(std::move(n));
			neighbors.emplace_back(node);
		}
		return;
	}

	for (size_t i = start; i < bits - distance + 1; i++)
	{
		curr.flip(i);
		getHammingNeighbors(curr, distance - 1, neighbors, i, root);
		curr.flip(i);
	}
}

std::unique_ptr<Node<BitArray>> MaxsatNeighborGenerator::getRandomNode()
{
	std::vector<uint64_t> init;
	init.reserve(m_problem.size() / 64);
	for (size_t i = 0; i < m_problem.size(); i += 64)
	{
		init.emplace_back(RandomNumberGenerator::getULong());
	}

	return MaxsatNode::createRoot<MaxsatNode>(BitArray(m_problem.size(), init));
}
