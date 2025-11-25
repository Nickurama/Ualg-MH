#pragma once
#include "algorithms/next_ascent_hillclimb.hpp"
#include "metaheuristic/rng.hpp"
#include <algorithm>
#include <iostream>

using namespace Algorithms;

// max_evals only applies for multistart
template<typename T>
NAHillclimb<T>::NAHillclimb(uint32_t hamming_distance, uint32_t multistarts, uint64_t max_evals) :
	m_hamming_distance(hamming_distance),
	m_should_terminate(false),
	m_multistarts(multistarts),
	m_initial_multistarts(multistarts),
	m_restart(true),
	m_initial_nodes(),
	m_restarts(-1),
	m_evaluations(0),
	m_max_evals(max_evals)
{
}

template<typename T>
void NAHillclimb<T>::evaluate(const std::vector<Node<T>*>&)
{
	if (this->m_max_evals > 0 && this->m_evaluations > this->m_max_evals && this->m_initial_multistarts > 0)
	{
		this->m_should_terminate = true;
		return;
	}

	if (m_should_terminate && m_multistarts > 0)
	{
		m_should_terminate = false;
		m_multistarts--;
		m_restart = true;
	}
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

	if (m_restart)
	{
		m_restarts++;
		m_initial_nodes.emplace_back(gen.getRandomNode());
		neighbors.emplace_back(m_initial_nodes[m_initial_nodes.size() - 1].get());
		return;
	}

	gen.getHammingNeighbors(const_cast<Node<T>&>(*nodes[0]), m_hamming_distance, neighbors);
	std::shuffle(neighbors.begin(), neighbors.end(), RandomNumberGenerator::randomEngine());
}

template<typename T>
void NAHillclimb<T>::chooseNodes(std::vector<Node<T>*>& nodes, const std::vector<Node<T>*>& neighbors)
{
	if (m_restart)
	{
		nodes.clear();
		nodes.emplace_back(neighbors[0]);
		m_restart = false;
		return;
	}

	Node<T>* curr = nodes[0];

	m_evaluations++;
	double curr_fitness = curr->fitness();
	for (Node<T>* neighbor : neighbors)
	{
		m_evaluations++;
		if (neighbor->fitness() > curr_fitness)
		{
			nodes.clear();
			nodes.emplace_back(neighbor);
			return;
		}
	}

	m_should_terminate = true;
}

template<typename T>
uint64_t NAHillclimb<T>::restarts() const
{
	return m_restarts;
}

template<typename T>
uint64_t NAHillclimb<T>::evaluations() const
{
	return m_evaluations;
}
