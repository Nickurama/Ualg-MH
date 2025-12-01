#include "problems/maxsat/maxsat_neighbor_generator.hpp"
#include "metaheuristic/rng.hpp"
#include "problems/maxsat/maxsat_node.hpp"
#include <set>
#include <iostream>

using namespace Problems;

MaxsatNeighborGenerator::MaxsatNeighborGenerator(MaxsatProblem& p) :
	m_problem(p),
	m_random_pool()
{
	m_random_pool.reserve(m_problem.size());
	for (size_t i = 1; i < m_problem.size(); i++)
	{
		m_random_pool.emplace_back(i);
	}
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

Node<BitArray>* MaxsatNeighborGenerator::mutate(const Node<BitArray>& node, double rate)
{
	size_t num_bits = node.value().size();
	BitArray mutated_bit_array = node.value();
	for (size_t i = 0; i < num_bits; i++)
	{
		if (RandomNumberGenerator::roll(rate))
		{
			mutated_bit_array.flip(i);
		}
	}
	
	return &node.createChild<MaxsatNode>(std::move(mutated_bit_array));
}

Node<BitArray>* MaxsatNeighborGenerator::crossover(const Node<BitArray>& first, const Node<BitArray>& second, int k)
{
	// picking i position means >=i is part of the second section

	// picking k random ordered non-repeating indices from [1-size[
	std::set<uint64_t> pool;
	for (int i = 0; i < k; i++)
	{
		uint64_t rng_i = RandomNumberGenerator::getULongRange(0, m_random_pool.size() - i);
		uint64_t curr = m_random_pool[rng_i];

		m_random_pool[rng_i] = m_random_pool[m_random_pool.size() - i - 1];
		m_random_pool[m_random_pool.size() - i - 1] = curr;

		pool.emplace(curr);
	}

	// laying them in an array
	std::vector<uint64_t> pool_arr;
	pool_arr.reserve(k);
	for (uint64_t indice : pool)
	{
		pool_arr.emplace_back(indice);
	}

	const BitArray& first_arr = first.value();
	const BitArray& second_arr = second.value();
	BitArray child_arr(first_arr.size());
	size_t pool_arr_i = 0;
	size_t pool_arr_size = pool_arr.size();
	bool flip = false;
	for (size_t i = 0; i < first_arr.size(); i++)
	{
		if (pool_arr_i < pool_arr_size && i == pool_arr[pool_arr_i])
		{
			flip = !flip;
			pool_arr_i++;
		}

		child_arr.set(i, flip ? second_arr[i] : first_arr[i]);
	}

	return &first.createChild<MaxsatNode>(std::move(child_arr));
}
