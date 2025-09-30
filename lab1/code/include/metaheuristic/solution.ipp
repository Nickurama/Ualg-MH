#pragma once
#include "metaheuristic/solution.hpp"
#include <stdexcept>

using namespace Metaheuristic;

template<typename T>
Solution<T>::Solution(T value) :
	m_value(value)
{

}

template<typename T>
T Solution<T>::value()
{
	return m_value;
}

template<typename T>
void Solution<T>::print()
{
	throw std::runtime_error("function not implemented.");
}
