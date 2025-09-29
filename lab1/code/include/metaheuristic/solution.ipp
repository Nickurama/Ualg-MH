#pragma once
#include "metaheuristic/solution.hpp"

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
