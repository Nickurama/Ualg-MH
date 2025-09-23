#include "node.hpp"

template<typename T>
Node<T>::Node(std::unique_ptr<T> value)
	:m_value(std::move(value))
{
}

template<typename T>
Node<T> *Node<T>::parent() const
{
	return m_parent;
}

template<typename T>
T Node<T>::value() const
{
	return m_value;
}

template<typename T>
const std::vector<std::unique_ptr<Node<T>>> Node<T>::children() const
{
	return m_children;
}
