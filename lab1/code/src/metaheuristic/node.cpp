#include "metaheuristic/node.hpp"

using namespace Metaheuristic;

template<Hashable T>
Node<T>::Node(const Node<T> *parent, T value) :
	m_parent(parent),
	m_value(std::move(value)),
	m_neighbors(nullptr),
	m_hasFitness(false),
	m_hash(DEFAULT_HASH_VALUE)
{ }

template<Hashable T>
Node<T>::Node(const T value) :
	Node(nullptr, value)
{ }

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
std::span<const std::unique_ptr<Node<T>>> Node<T>::neighbors() const
{
	if (m_neighbors == nullptr)
	{
		m_neighbors = generateNeighbors();
	}
	return m_neighbors;
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
bool Node<T>::operator==(const Node<T> &other) const
{
	if (typeid(*this) != typeid(other)) return false;
	return m_value == other.m_value;
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
