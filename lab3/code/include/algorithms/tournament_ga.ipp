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
void TournamentGA<T>::getNeighbors(const std::vector<Node<T>*>& new_gen, NeighborGenerator<T>& generator, std::vector<Node<T>*>& old_gen)
{
	if (m_first)
	{
		m_first = false;

		m_initial_nodes.reserve(m_pop_size);
		neighbors.reserve(m_pop_size);
		for (size_t i = 0; i < m_pop_size; i++)
		{
			m_initial_nodes[i] = std::move(generator.getRandomNode());
			neighbors.emplace_back(m_initial_nodes[i].get());
		}

		return;
	}

	// recombination
	// mutation
}

template<typename T>
void TournamentGA<T>::chooseNodes(std::vector<Node<T>*>& new_gen, const std::vector<Node<T>*>& old_gen)
{
	new_gen.clear();

	// tournament selection, no repeating
	size_t old_gen_size = old_gen.size();
	for (uint32_t i = 0; i < m_selection_amount; i++)
	{
		uint64_t max_fitness = 0;
		Node<T>* match_winner = nullptr;
		for (uint32_t j = 0; j < m_match_indiviual_number; j++)
		{
			// get random individual (from valid range, the ones that haven't been chosen)
			uint64_t random_index = RandomNumberGenerator::getULongRange(0, old_gen_size - j);
			Node<T>* curr = old_gen[random_index];
			m_evaluations++;
			double curr_fitness = curr->fitness();

			// if the individual is the best, save it
			if (curr_fitness > max_fitness)
			{
				max_fitness = curr_fitness;
				match_winner = curr;
			}

			// send the individual to the invalid section
			old_gen[random_index] = old_gen[old_gen_size - j - 1];
			old_gen[old_gen_size - j - 1] = curr;
		}
		new_gen.emplace_back(match_winner);
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
