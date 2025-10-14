#pragma once
#include "algorithms/next_ascent_hillclimb.hpp"

using namespace Algorithms;

template<typename T>
NAHillclimb<T>::NAHillclimb(uint32_t hamming_distance) :
	m_hamming_distance(hamming_distance),
	m_should_terminate(false)
{
}

template<typename T>
void NAHillclimb<T>::evaluate(const std::vector<Node<T>*>&)
{
	// no need for evaluation
	return;
}

template<typename T>
bool NAHillclimb<T>::shouldTerminate(const std::vector<Node<T>*>&) const
{
	return m_should_terminate;
}

template<typename T>
void NAHillclimb<T>::getNeighbors(const std::vector<Node<T>*>& nodes, NeighborGenerator<T>& gen, std::vector<Node<T>*>& neighbors)
{
	neighbors.clear();
	gen.getHammingNeighbors(const_cast<Node<T>&>(*nodes[0]), m_hamming_distance, neighbors);
}

template<typename T>
void NAHillclimb<T>::chooseNodes(std::vector<Node<T>*>& nodes, const std::vector<Node<T>*>& neighbors)
{
	Node<T>* curr = nodes[0];
	nodes.clear();

	double curr_fitness = curr->fitness();
	for (Node<T>* neighbor : neighbors)
	{
		if (neighbor->fitness() > curr_fitness)
		{
			nodes[0] = neighbor;
			break;
		}
	}

	m_should_terminate = true;
}
