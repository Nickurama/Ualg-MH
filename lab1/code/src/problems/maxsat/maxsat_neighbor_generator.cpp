#include "problems/maxsat/maxsat_neighbor_generator.hpp"
#include <iostream>

using namespace Problems;

MaxsatNeighborGenerator::MaxsatNeighborGenerator()
{

}

std::vector<std::unique_ptr<Node<BitArray>>> MaxsatNeighborGenerator::getAllNeighbors(const Node<BitArray>& node)
{
	// TODO
	std::cout << (node.value())[0] << "\n";
	return { };
}

std::vector<std::unique_ptr<Node<BitArray>>> MaxsatNeighborGenerator::getRandomNeighbors(const Node<BitArray>& node, int k)
{
	// TODO
	std::cout << node.value()[0] + k << "\n";
	return { };
}

std::unique_ptr<Node<BitArray>> MaxsatNeighborGenerator::getRandomNeighbor(const Node<BitArray>& node)
{
	// TODO
	std::cout << node.value()[0] << "\n";
	return { };
}

std::unique_ptr<Node<BitArray>> MaxsatNeighborGenerator::getRandomNode()
{
	// TODO
	return { };
}

bool MaxsatNeighborGenerator::hasNextNeighbor(Node<BitArray>)
{
	// TODO
	return false;
}

std::unique_ptr<Node<BitArray>> MaxsatNeighborGenerator::getNextNeighbor(Node<BitArray>& node)
{
	// TODO
	std::cout << node.value()[0] << "\n";
	return { };
}

std::unique_ptr<Node<BitArray>> MaxsatNeighborGenerator::mutate(const Node<BitArray>& node, double rate)
{
	// TODO
	std::cout << node.value()[0] + rate << "\n";
	return { };
}

std::unique_ptr<Node<BitArray>> MaxsatNeighborGenerator::crossover(const Node<BitArray>& first, const Node<BitArray>& second)
{
	// TODO
	std::cout << first.value()[0] + second.value()[0] << "\n";
	return { };
}
