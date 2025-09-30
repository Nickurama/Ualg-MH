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
T Solution<T>::value() const
{
	return m_value;
}

template<typename T>
std::string Solution<T>::output() const
{
	throw std::runtime_error("function not implemented.");
}
