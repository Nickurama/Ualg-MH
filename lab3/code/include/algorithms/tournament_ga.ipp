#pragma once
#include "algorithms/tournament_ga.hpp"
#include "metaheuristic/rng.hpp"
#include <algorithm>
#include <iostream>

using namespace Algorithms;

// max_evals only applies for multistart
template<typename T>
TournamentGA<T>::TournamentGA(uint32_t hamming_distance, double initial_temperature, std::function<double(double)> cooling_schedule, uint64_t max_evals) :
	m_hamming_distance(hamming_distance),
	m_should_terminate(false),
	m_initial_temperature(initial_temperature),
	m_temperature(initial_temperature),
	m_cooling_schedule(cooling_schedule),
	m_initial_node(nullptr),
	m_evaluations(0),
	m_max_evals(max_evals),
	m_first(false)
{
}

template<typename T>
void TournamentGA<T>::evaluate(const std::vector<Node<T>*>&)
{
	if (m_first)
	{
		return;
	}

	m_temperature = m_cooling_schedule(m_temperature);

	if (m_evaluations > m_max_evals)
	{
		m_should_terminate = true;
	}
}

template<typename T>
bool TournamentGA<T>::shouldTerminate(const std::vector<Node<T>*>&) const
{
	return m_should_terminate;
}

template<typename T>
void TournamentGA<T>::getNeighbors(const std::vector<Node<T>*>& nodes, NeighborGenerator<T>& gen, std::vector<Node<T>*>& neighbors)
{
	if (m_first)
	{
		m_first = false;
		m_initial_node = std::move(gen.getRandomNode());
		neighbors.emplace_back(m_initial_node.get());
		return;
	}

	neighbors.clear();

	// const Node<T>& node = *nodes[0]; // const_cast<Node<T>&>(*nodes[0])
	//
	// const Node<T> neighbor = gen.getHammingNeighbor(node, m_hamming_distance);

	Node<T>* neighbor = gen.getHammingNeighborUnderDistance(*nodes[0], m_hamming_distance);
	neighbors.emplace_back(neighbor);
}

template<typename T>
void TournamentGA<T>::chooseNodes(std::vector<Node<T>*>& nodes, const std::vector<Node<T>*>& neighbors)
{
	Node<T>* node = nodes[0];
	Node<T>* neighbor = neighbors[0];

	m_evaluations += 2;
	double node_fitness = node->fitness();
	double neighbor_fitness = neighbor->fitness();

	if (neighbor_fitness > node_fitness)
	{
		nodes.clear();
		nodes.emplace_back(neighbor);
		return;
	}

	// double exponent = - (node_fitness - neighbor_fitness) / m_temperature;
	double exponent = (neighbor_fitness - node_fitness) / m_temperature;
	double p_accept = std::exp(exponent);

	if (RandomNumberGenerator::roll(p_accept))
	{
		nodes.clear();
		nodes.emplace_back(neighbor);
	}
}

template<typename T>
uint64_t TournamentGA<T>::restarts() const
{
	return 0;
}

template<typename T>
uint64_t TournamentGA<T>::evaluations() const
{
	return m_evaluations;
}
