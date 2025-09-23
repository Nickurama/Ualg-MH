#pragma once

#include <memory>
#include <vector>
#include <span>

template<typename T>
class Node
{
private:
	Node<T> *m_parent;
	std::unique_ptr<T> m_value;
	std::vector<std::unique_ptr<Node<T>>> m_children;

public:
	Node(std::unique_ptr<T> value);
	inline Node<T> *parent() const;
	inline T value() const;
	inline const std::vector<std::unique_ptr<Node<T>>> children() const;
};
