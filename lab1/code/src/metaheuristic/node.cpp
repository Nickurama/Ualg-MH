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
double Node<T>::fitness() const
{
	if (!m_hasFitness)
	{
		m_hasFitness = true;
		m_fitness = calcFitness();
	}
	return m_fitness;
}

template<Hashable T>
bool Node<T>::operator!=(const Node<T> &other) const
{
	return !(*this == other);
}

template<Hashable T>
size_t Node<T>::hash() const
{
	if (m_hash == DEFAULT_HASH_VALUE)
	{
		m_hash = std::hash<T>(m_value);
	}
	return m_hash;
}
