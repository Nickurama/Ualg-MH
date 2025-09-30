#pragma once
#include "algorithms/naive_algorithm.hpp"

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
std::vector<Node<T>*> NaiveAlgorithm<T>::getNeighbors(const std::vector<Node<T>*>& nodes, NeighborGenerator<T>& gen)
{
	// naive algorithm always chooses the next node
	Node<T>* firstNode = nodes[0];
	Node<T>* nextNeighbor = gen.getNextNeighbor(*firstNode);
	std::vector<Node<T>*> vect;
	vect.emplace_back(nextNeighbor);
	// vect.emplace_back(gen.getNextNeighbor(nodes[0]));
	vect.emplace_back();
	return vect;
	// return { std::make_unique<Node<T>>(std::move(gen.getNextNeighbor(nodes[0]))) };
}

template<typename T>
const std::vector<Node<T>*> NaiveAlgorithm<T>::chooseNodes(const std::vector<Node<T>*>&, const std::vector<Node<T>*>& neighbors)
{
	// naive algorithm doesn't concern itself with choosing
	return { std::move(neighbors[0]) };
}
