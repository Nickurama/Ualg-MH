#pragma once
#include "algorithms/tournament_ga.hpp"
#include "metaheuristic/rng.hpp"
#include <algorithm>
#include <iostream>

using namespace Algorithms;

// max_evals only applies for multistart
template<typename T>
TournamentGA<T>::TournamentGA(uint64_t pop_size, uint64_t num_crossover_points, double mutation_chance, uint64_t match_individual_number, uint64_t max_evals) :
	m_should_terminate(false),
	m_initial_nodes(),
	m_pop_size(pop_size),
	m_num_crossover_points(num_crossover_points),
	m_mutation_chance(mutation_chance),
	m_match_individual_number(match_individual_number),
	m_random_pool(),
	m_evaluations(0),
	m_max_evals(max_evals),
	m_first(true)
{
	m_random_pool.reserve(m_pop_size);
	for (size_t i = 0; i < m_pop_size; i++)
	{
		m_random_pool[i] = i;
	}
}

template<typename T>
void TournamentGA<T>::evaluate(const std::vector<Node<T>*>&)
{
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
	// initialization
	if (m_first)
	{
		m_first = false;

		m_initial_nodes.reserve(m_pop_size);
		old_gen.reserve(m_pop_size);
		for (size_t i = 0; i < m_pop_size; i++)
		{
			m_initial_nodes.emplace_back(std::move(generator.getRandomNode()));
			old_gen.emplace_back(m_initial_nodes[i].get());
		}

		return;
	}

	// recombination
	old_gen.clear();

	// pick two parents at random
	for (uint32_t i = 0; i < m_pop_size; i++)
	{
		uint64_t i0 = RandomNumberGenerator::getULongRange(0, m_pop_size);
		uint64_t i1 = RandomNumberGenerator::getULongRange(0, m_pop_size);
		while (i1 == i0)
		{
			i1 = RandomNumberGenerator::getULongRange(0, m_pop_size);
		}

		Node<T>* parent_0 = new_gen[i0];
		Node<T>* parent_1 = new_gen[i1];

		Node<T>* child = generator.crossover(*parent_0, *parent_1, m_num_crossover_points);
		old_gen.emplace_back(child);
	}

	// mutation
	for (size_t i = 0; i < old_gen.size(); i++)
	{
		old_gen[i] = generator.mutate(*old_gen[i], m_mutation_chance);
	}
}

template<typename T>
void TournamentGA<T>::chooseNodes(std::vector<Node<T>*>& new_gen, const std::vector<Node<T>*>& old_gen)
{
	// tournament selection, no repeating
	new_gen.clear();
	for (uint32_t i = 0; i < m_pop_size; i++)
	{
		uint64_t max_fitness = 0;
		Node<T>* match_winner = nullptr;
		for (uint32_t j = 0; j < m_match_individual_number; j++)
		{
			// get random individual (from valid range, the ones that haven't been chosen)
			uint64_t random_index = m_random_pool[RandomNumberGenerator::getULongRange(0, m_pop_size - j)];
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
			m_random_pool[random_index] = m_random_pool[m_pop_size - j - 1];
			m_random_pool[m_pop_size - j - 1] = random_index;
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
