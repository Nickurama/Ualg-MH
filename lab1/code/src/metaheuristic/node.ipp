#pragma once
#include "metaheuristic/node.hpp"

using namespace Metaheuristic;

template<Hashable T>
Node<T>::Node(const Node<T> *parent, const T value) :
	m_parent(parent),
	m_value(std::move(value)),
	m_children()
{

}

template<Hashable T>
Node<T>::Node(const Node<T> *parent, T&& value) :
	m_parent(parent),
	m_value(std::move(value)),
	m_children()
{

}

template<Hashable T>
std::unique_ptr<Node<T>> Node<T>::createRoot(T value)
{
	return std::unique_ptr<Node<T>>(new Node<T>(nullptr, value));
}

template<Hashable T>
std::unique_ptr<Node<T>> Node<T>::createRoot(T&& value)
{
	return std::unique_ptr<Node<T>>(new Node<T>(nullptr, std::move(value)));
}

template<Hashable T>
Node<T>& Node<T>::createChild(T&& value)
{
	std::unique_ptr<Node<T>> child = std::make_unique<Node<T>>(this, std::move(value));
	Node<T>& childRef = *child;
	m_children.emplace_back(std::move(child));
	return childRef;
}

template<Hashable T>
Node<T>& Node<T>::createChild(T value)
{
	std::unique_ptr<Node<T>> child = std::make_unique<Node<T>>(this, value);
	Node<T>& childRef = *child;
	m_children.emplace_back(std::move(child));
	return childRef;
}

template<Hashable T>
const T& Node<T>::value()
{
	return m_value;
}

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
	return std::hash<T>{}(m_value);
}

template<Hashable T>
double Node<T>::fitness() const
{
	throw std::runtime_error("function not implemented.");
}

template<Hashable T>
double Node<T>::heuristic() const
{
	throw std::runtime_error("function not implemented.");
}

template<Hashable T>
double Node<T>::cost() const
{
	throw std::runtime_error("function not implemented.");
}

template<Hashable T>
bool Node<T>::operator==(const Node<T> &other) const
{
	return m_value == other.m_value;
}
