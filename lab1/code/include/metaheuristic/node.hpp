#pragma once

#include <memory>
#include <vector>

template<typename T>
concept Hashable = requires(T a, T b)
{
	{ std::hash<T>{}(a) } -> std::convertible_to<size_t>;
	{ a == b } -> std::convertible_to<bool>;
};

template<typename Derived, typename Base>
concept DerivedFrom = std::is_base_of_v<Base, Derived>;

namespace Metaheuristic
{
	template<Hashable T>
	class Node
	{
	private:
		Node<T> *m_parent; // non-owning
		std::unique_ptr<T> m_value;
		std::vector<std::unique_ptr<Node<T>>> m_children;

		// private constructor
		Node(const Node<T> *parent, T value);
		Node(const Node<T> *parent, T&& value);
	
	protected:
		// constructors
		Node();

		// copy constructors
		Node(const Node<T> &other) = delete;
		Node<T> &operator=(const Node<T> &other) = delete;

		// move constructors
		Node(Node &&other) = default;
		Node<T> &operator=(Node<T> &&other) = default;

	public:
		virtual ~Node() = default;
		Node<T> *parent() const;
		const T& value() const;
		bool operator!=(const Node<T> &other) const;

		// virtual functions, meant to be overriden
		virtual double fitness() const;
		virtual double heuristic() const;
		virtual double cost() const;

		// virtual defaulted functions
		virtual size_t hash() const; // hash of value (in the default implementation)
		virtual bool operator==(const Node<T> &other) const; // should be true even if different parents, just equal values. (in the default implementation)

		// constructors
		// template<typename NodeDerivation>
		// template<DerivedFrom<Node<T>> NodeDerivation>
		template<DerivedFrom<Node<T>> NodeDerivation>
		static std::unique_ptr<Node<T>> createRoot(T&& value); // transfers ownership to the caller

		template<DerivedFrom<Node<T>> NodeDerivation>
		Node<T>& createChild(T&& value); // ownership goes to the parent
	};
}

// very helpful concept for classes that use Nodes
template<typename Derived, typename T>
concept NodeDerivation = std::is_base_of_v<Metaheuristic::Node<T>, Derived> && Hashable<T>;

#include "metaheuristic/node.ipp"

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

