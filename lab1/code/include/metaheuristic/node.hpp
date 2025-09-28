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
		const Node<T> *m_parent; // non-owning
		T m_value;
		const std::vector<std::unique_ptr<Node<T>>> m_children;

		// private constructor
		Node(const Node<T> *parent, T value);
	
	protected:
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
		const T& value();

		// virtual functions
		virtual double fitness() const = 0;
		virtual double heuristic() const = 0;
		virtual double cost() const = 0;

		// virtual defaulted functions
		virtual size_t hash() const; // hash of value (in the default implementation)
		virtual bool operator==(const Node<T> &other) const; // should be true even if different parents, just equal values. (in the default implementation)

		// constructors
		static std::unique_ptr<Node<T>> createRoot(T value); // transfers ownership to the caller
		Node<T>& createChild(T value); // ownership goes to the parent
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
