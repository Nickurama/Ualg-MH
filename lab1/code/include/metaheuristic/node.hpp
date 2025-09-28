#pragma once

#include <memory>
#include <span>
#include <vector>

template<typename T>
concept Hashable = requires(T a, T b)
{
	{ std::hash<T>{}(a) } -> std::convertible_to<size_t>;
	{ a == b } -> std::convertible_to<bool>;
};

namespace Metaheuristic
{
	template<Hashable T>
	class Node
	{
	private:
		const Node<T> *m_parent;
		const T m_value;
	
	protected:
		// constructors
		Node(const Node<T> *parent, const T value) :
			m_parent(parent),
			m_value(std::move(value))
		{ }

		Node(const T value); // root node constructor

		// copy constructors
		Node(const Node<T> &other) = delete;
		Node<T> &operator=(const Node<T> &other) = delete;

		// move constructors
		Node(Node &&other) = default;
		Node<T> &operator=(Node<T> &&other) = default;

	public:
		virtual ~Node() = default;
		inline Node<T> *parent() const;
		inline const T &value() const;
		bool operator!=(const Node<T> &other) const;

		// virtual functions
		virtual double fitness() const = 0;
		virtual double heuristic() const = 0;
		virtual double cost() const = 0;

		// virtual defaulted functions
		virtual size_t hash() const; // hash of value (in the default implementation)
		virtual bool operator==(const Node<T> &other) const; // should be true even if different parents, just equal values. (in the default implementation)
	};
}

namespace std
{
	template<Hashable T>
	struct hash<Metaheuristic::Node<T>>
	{
		size_t operator()(const Metaheuristic::Node<T> &node) const
		{
			return node.hash();
		}
	};
}

# include "metaheuristic/node.ipp"
