#pragma once
#include "algorithms/variable_neighbourhood_ascent_hillclimb.hpp"
#include "metaheuristic/rng.hpp"
#include <algorithm>
#include <iostream>

using namespace Algorithms;

template<typename T>
VNAHillclimb<T>::VNAHillclimb(uint32_t max_hamming_distance, uint32_t multistarts, uint64_t max_evals) :
	NAHillclimb<T>(1, multistarts, max_evals),
	m_max_hamming_distance(max_hamming_distance)
{
}

template<typename T>
void VNAHillclimb<T>::evaluate(const std::vector<Node<T>*>&)
{
	if (this->m_max_evals > 0 && this->m_evaluations > this->m_max_evals && this->m_initial_multistarts > 0)
	{
		this->m_should_terminate = true;
		return;
	}

	if (!this->m_should_terminate)
	{
		this->m_hamming_distance = 1;
		return;
	}

	if (this->m_hamming_distance < m_max_hamming_distance)
	{
		this->m_hamming_distance++;
		this->m_should_terminate = false;
		return;
	}

	if (this->m_multistarts > 0)
	{
		this->m_should_terminate = false;
		this->m_multistarts--;
		this->m_restart = true;
	}
}
