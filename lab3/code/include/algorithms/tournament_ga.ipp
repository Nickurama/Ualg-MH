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
	// WARNING new_gen is constant, therefore can't emplace
	// TODO copying every iteration is overly inefficient for no reason

	// initialization
	if (m_first)
	{
		m_first = false;

		m_initial_nodes.reserve(m_pop_size);
		old_gen.reserve(m_pop_size);
		new_gen.reserve(m_pop_size);
		for (size_t i = 0; i < m_pop_size; i++)
		{
			m_initial_nodes[i] = std::move(generator.getRandomNode());
			old_gen.emplace_back(m_initial_nodes[i].get());
		}

		return;
	}

	// recombination

	// pick two parents at random
	for (uint32_t i = 0; i < m_recombination_amount; i++)
	{
		uint64_t i0 = RandomNumberGenerator::getULongRange(0, old_gen.size());
		uint64_t i1 = RandomNumberGenerator::getULongRange(0, old_gen.size());
		while (i1 == i0)
		{
			i1 = RandomNumberGenerator::getULongRange(0, old_gen.size());
		}

		Node<T>* parent_0 = old_gen[i0];
		Node<T>* parent_1 = old_gen[i1];

		Node<T>* child = generator.crossover(*parent_0, *parent_1, m_num_crossover_points);
		new_gen.emplace_back(child);
	}

	// pick n positions from 1-size
	// picking i position means >=i is part of the second section
	// x x x

	// make an ordered array with the chosen positions
	// at each position it flips the parent to copy

	// mutation
	for (size_t i = 0; i < new_gen.size(); i++)
	{
		new_gen[i] = generator.mutate(new_gen[i], m_mutation_chance);
	}

	// reset iteration
	std::copy(new_gen.begin(), new_gen.end(), old_gen.begin());
	new_gen.clear();
}

template<typename T>
void TournamentGA<T>::chooseNodes(std::vector<Node<T>*>& new_gen, const std::vector<Node<T>*>& old_gen)
{
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
