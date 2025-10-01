#pragma once
#include "metaheuristic/node.hpp"
#include <queue>
#include <stack>

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
Node<T>::Node()
{
}

template<Hashable T>
Node<T>::~Node()
{
	if (m_parent != nullptr) return;

	std::stack<std::unique_ptr<Node<T>>> nodes;
	for (std::unique_ptr<Node<T>>& child : m_children)
	{
		nodes.push(std::move(child));
	}

	while (!nodes.empty())
	{
		std::unique_ptr<Node<T>> current = std::move(nodes.top());
		nodes.pop();

		for (std::unique_ptr<Node<T>>& child : current->m_children)
		{
			nodes.push(std::move(child));
		}

		current->m_children.clear();
	}
}

template<Hashable T>
template<DerivedFrom<Node<T>> NodeDerivation>
std::unique_ptr<Node<T>> Node<T>::createRoot(T&& value)
{
	std::unique_ptr<Node<T>> result(new NodeDerivation());
	result->m_parent = nullptr;
	result->m_value = std::make_unique<T>(std::move(value));
	result->m_children = std::vector<std::unique_ptr<Node<T>>>();
	return result;
}

template<Hashable T>
template<DerivedFrom<Node<T>> NodeDerivation>
Node<T>& Node<T>::createChild(T&& value)
{
	std::unique_ptr<Node<T>> child(new NodeDerivation());
	child->m_parent = this;
	child->m_value = std::make_unique<T>(std::move(value));
	child->m_children = std::vector<std::unique_ptr<Node<T>>>();
	Node<T>& childRef = *child;
	m_children.emplace_back(std::move(child));
	return childRef;
}

template<Hashable T>
const T& Node<T>::value() const
{
	return *m_value;
}

template<Hashable T>
Node<T> *Node<T>::parent() const
{
	return m_parent;
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
	return std::hash<T>{}(*m_value);
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
