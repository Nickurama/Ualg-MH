#include "problems/maxsat/maxsat_neighbor_generator.hpp"
#include "problems/maxsat/maxsat_node.hpp"

using namespace Problems;

MaxsatNeighborGenerator::MaxsatNeighborGenerator()
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

std::vector<Node<BitArray>*> MaxsatNeighborGenerator::getHammingNeighbors(const Node<BitArray>& node, uint32_t distance)
{
	// iterate through all distance-wise permutations
	std::vector<Node<BitArray>*> neighbors;
	size_t bits = node.value().size();
	neighbors.reserve(bits); // WARNING should be bits^distance no?
	BitArray init_curr = node.value();
	getHammingNeighbors(init_curr, distance, neighbors, 0, node);
	return neighbors;
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
			neighbors.emplace_back(&root.createChild<MaxsatNode>(std::move(n)));
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

// size: 5, hamming distance: 3
// initial: 0 0 0 0 0

// 1 0 0 0 0 - start 1 ----
// 1 1 0 0 0 - start 2
// 1 1 1 0 0
// 1 1 0 1 0
// 1 1 0 0 1

// 1 0 1 0 0 - start 3
// 1 0 1 0 0
// 1 0 0 1 0
// 1 0 0 0 1

// 1 0 0 1 0 - start 4
// 1 0 0 1 1

// 1 0 0 0 1 - start 5
// 0 1 0 0 0 - start 2 ----
// 0 1 1 0 0 - start 3
// 0 1 1 1 0
// 0 1 1 0 1

// ...

// 0 0 0 1 0 - start 4 ----
// 0 0 0 1 1 - start 5
// error
// 0 0 1 0 0 - start 4 ----
// ...
// 0 0 0 0 1 - start 5
// error


// std::vector<std::unique_ptr<Node<BitArray>>> MaxsatNeighborGenerator::getAllNeighbors(const Node<BitArray>& node)
// {
// 	// TODO
// }
//
// std::vector<std::unique_ptr<Node<BitArray>>> MaxsatNeighborGenerator::getRandomNeighbors(const Node<BitArray>& node, int k)
// {
// 	// TODO
// }
//
// std::unique_ptr<Node<BitArray>> MaxsatNeighborGenerator::getRandomNeighbor(const Node<BitArray>& node)
// {
// 	// TODO
// }
//
// std::unique_ptr<Node<BitArray>> MaxsatNeighborGenerator::getRandomNode()
// {
// 	// TODO
// }
//
// bool MaxsatNeighborGenerator::hasNextNeighbor(Node<BitArray>)
// {
// 	// TODO
// }
// std::unique_ptr<Node<BitArray>> MaxsatNeighborGenerator::mutate(const Node<BitArray>& node, double rate)
// {
// 	// TODO
// }
//
// std::unique_ptr<Node<BitArray>> MaxsatNeighborGenerator::crossover(const Node<BitArray>& first, const Node<BitArray>& second)
// {
// 	// TODO
// }
