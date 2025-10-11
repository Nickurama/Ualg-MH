#pragma once
#include "metaheuristic_extra/hamming_neighbor_generator.hpp"

using namespace MetaheuristicExtra;

template<Hashable T>
std::vector<Node<T>*> HammingNeighborGenerator<T>::getHammingNeighbors(const Node<T>&, uint32_t)
{
	throw std::runtime_error("function not implemented.");
}
