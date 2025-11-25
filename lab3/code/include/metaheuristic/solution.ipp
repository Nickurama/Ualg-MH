#pragma once
#include "metaheuristic/solution.hpp"
#include <stdexcept>

using namespace Metaheuristic;

template<typename T>
Solution<T>::Solution(T value) :
	m_value(value),
	m_duration()
{

}

template<typename T>
const T& Solution<T>::value() const
{
	return m_value;
}

template<typename T>
std::string Solution<T>::output() const
{
	throw std::runtime_error("function not implemented.");
}

template<typename T>
void Solution<T>::setDuration(std::chrono::high_resolution_clock::duration duration)
{
	m_duration = duration;
}

template<typename T>
std::chrono::high_resolution_clock::duration Solution<T>::duration() const
{
	return m_duration;
}
