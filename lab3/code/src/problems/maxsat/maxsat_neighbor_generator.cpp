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

Node<BitArray>* MaxsatNeighborGenerator::getHammingNeighbor(const Node<BitArray>& node, uint32_t distance)
{
	std::vector<uint64_t> pool;
	pool.reserve(node.value().size());

	for (size_t i = 0; i < node.value().size(); i++)
	{
		pool[i] = i;
	}

	BitArray result = node.value();

	for (uint32_t i = 0; i < distance; i++)
	{
		uint64_t random_index = RandomNumberGenerator::getULongRange(0, pool.size());
		uint64_t chosen = pool[random_index];
		result.flip(chosen);

		pool.clear();
		std::vector<uint64_t> new_pool;
		new_pool.reserve(pool.size() - 1);
		size_t j = 0;
		for (size_t i = 0; i < pool.size(); i++)
		{
			if (i == random_index)
			{
				continue;
			}

			new_pool[j++] = pool[i];
		}
		pool = new_pool;
	}

	return &node.createChild<MaxsatNode>(std::move(result));
}

Node<BitArray>* MaxsatNeighborGenerator::getHammingNeighborUnderDistance(const Node<BitArray>& node, uint32_t distance)
{
	BitArray flipped_bits(node.value().size());
	BitArray result = node.value();

	for (uint32_t i = 0; i < distance; i++)
	{
		uint64_t random_index = RandomNumberGenerator::getULongRange(0, result.size());
		if (!flipped_bits.get(random_index))
		{
			flipped_bits.flip(random_index);
			result.flip(random_index);
		}
	}

	return &node.createChild<MaxsatNode>(std::move(result));
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
