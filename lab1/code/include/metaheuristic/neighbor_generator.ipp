#pragma once
#include "metaheuristic/neighbor_generator.hpp"

template<Hashable T>
std::vector<std::unique_ptr<Node<T>>> NeighborGenerator<T>::getAllNeighbors(const Node<T>&)
{
	throw std::runtime_error("function not implemented.");
}

template<Hashable T>
std::vector<std::unique_ptr<Node<T>>> NeighborGenerator<T>::getRandomNeighbors(const Node<T>&, int)
{
	throw std::runtime_error("function not implemented.");
}

template<Hashable T>
std::unique_ptr<Node<T>> NeighborGenerator<T>::getRandomNeighbor(const Node<T>&)
{
	throw std::runtime_error("function not implemented.");
}

template<Hashable T>
std::unique_ptr<Node<T>> NeighborGenerator<T>::getRandomNode()
{
	throw std::runtime_error("function not implemented.");
}

template<Hashable T>
bool NeighborGenerator<T>::hasNextNeighbor(Node<T>)
{
	throw std::runtime_error("function not implemented.");
}

template<Hashable T>
std::unique_ptr<Node<T>> NeighborGenerator<T>::getNextNeighbor(Node<T>&)
{
	throw std::runtime_error("function not implemented.");
}

template<Hashable T>
std::unique_ptr<Node<T>> NeighborGenerator<T>::mutate(const Node<T>&, double)
{
	throw std::runtime_error("function not implemented.");
}

template<Hashable T>
std::unique_ptr<Node<T>> NeighborGenerator<T>::crossover(const Node<T>&, const Node<T>&)
{
	throw std::runtime_error("function not implemented.");
}
