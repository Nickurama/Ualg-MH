#pragma once
#include "metaheuristic/node.hpp"

using namespace Metaheuristic;

template<Hashable T>
Node<T> *Node<T>::parent() const
{
	return m_parent;
}

template<Hashable T>
const T &Node<T>::value() const
{
	return *m_value;
}

template<Hashable T>
bool Node<T>::operator!=(const Node<T> &other) const
{
	return !(*this == other);
}

// default implementation
template<Hashable T>
size_t Node<T>::hash() const
{
	return std::hash<T>(m_value);
}
