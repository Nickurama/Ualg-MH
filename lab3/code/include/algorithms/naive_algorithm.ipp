#pragma once
#include "algorithms/naive_algorithm.hpp"
#include <iostream>

using namespace Algorithms;

template<typename T>
void NaiveAlgorithm<T>::evaluate(const std::vector<Node<T>*>&)
{
	// naive algorithm needs no evaluation
	return;
}

template<typename T>
bool NaiveAlgorithm<T>::shouldTerminate(const std::vector<Node<T>*>&) const
{
	// not dictated by the naive algorithm
	return false;
}

template<typename T>
// std::vector<Node<T>*> NaiveAlgorithm<T>::getNeighbors(const std::vector<Node<T>*>& nodes, NeighborGenerator<T>& gen)
void NaiveAlgorithm<T>::getNeighbors(const std::vector<Node<T>*>& nodes, NeighborGenerator<T>& gen, std::vector<Node<T>*>& neighbors)
{
	// naive algorithm always chooses the next node
	neighbors.emplace_back(gen.getNextNeighbor(*nodes[0]));
}

template<typename T>
void NaiveAlgorithm<T>::chooseNodes(std::vector<Node<T>*>& nodes, const std::vector<Node<T>*>& neighbors)
{
	// naive algorithm doesn't concern itself with choosing
	nodes[0] = neighbors[0];
}

template<typename T>
uint64_t NaiveAlgorithm<T>::restarts() const
{
	return 0;
}

template<typename T>
uint64_t NaiveAlgorithm<T>::evaluations() const
{
	return 0;
}
