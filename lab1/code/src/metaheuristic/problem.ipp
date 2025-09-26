#pragma once
#include "metaheuristic/problem.hpp"

using namespace Metaheuristic;

template<typename T, typename G>
Problem<T, G>::Problem(T root_value)
	:m_rootNode(Node<T>(root_value))
{

}

template<typename T, typename G>
std::vector<std::unique_ptr<Node<T>>> Problem<T, G>::getRootNodes()
{

}
