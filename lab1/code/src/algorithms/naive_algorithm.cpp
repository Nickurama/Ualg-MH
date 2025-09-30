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
std::vector<std::unique_ptr<Node<T>>> NaiveAlgorithm<T>::getNeighbors(const std::vector<Node<T>*>&, NeighborGenerator<T>& gen)
{
	// naive algorithm always chooses the next node
	return { std::move(gen.getNextNeighbor()) };
}

template<typename T>
const std::vector<Node<T>*> NaiveAlgorithm<T>::chooseNodes(const std::vector<Node<T>*>&, const std::vector<Node<T>*>& neighbors)
{
	// naive algorithm doesn't concern itself with choosing
	return { std::move(neighbors[0]) };
}
