#pragma once
#include "algorithms/next_ascent_hillclimb.hpp"

using namespace Algorithms;

template<typename T>
void NAHillclimb<T>::evaluate(const std::vector<Node<T>*>&)
{
	// TODO implement
	return;
}

template<typename T>
bool NAHillclimb<T>::shouldTerminate(const std::vector<Node<T>*>&) const
{
	// not dictated by the next ascent hillclimb algorithm
	return false;
}

template<typename T>
void NAHillclimb<T>::getNeighbors(const std::vector<Node<T>*>& nodes, NeighborGenerator<T>& gen, std::vector<Node<T>*>& neighbors)
{
	// hamming distance of 1
	// TODO select hamming distance in constructor
	// TODO loop for every node
	std::vector<Node<T>*> neigh = gen.getHammingNeighbors(nodes[0], 1); // TODO change getHammingNeighbors() to include neighbors vector in argument
																			// and just pass the neighbors vector
	// TODO emplace back to neighbors every other vector.
	// neighbors.emplace_back(gen.getNextNeighbor(*nodes[0]));
}

template<typename T>
void NAHillclimb<T>::chooseNodes(std::vector<Node<T>*>& nodes, const std::vector<Node<T>*>& neighbors)
{
	nodes.clear();
	// TODO choose a node and emplace it onto nodes
}
