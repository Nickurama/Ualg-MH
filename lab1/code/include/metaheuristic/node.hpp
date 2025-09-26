#pragma once

#include <memory>
#include <span>
#include <vector>

constexpr size_t DEFAULT_HASH_VALUE = ~0ul;

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
		mutable std::vector<std::unique_ptr<Node<T>>> m_neighbors; // lazy initialization
		mutable double m_fitness; // lazy initialization
		mutable bool m_hasFitness;
		mutable size_t m_hash; // lazy initialization
	
	protected:
		// constructors
		Node(const Node<T> *parent, const T value) :
			m_parent(parent),
			m_value(std::move(value)),
			m_neighbors(),
			m_hasFitness(false),
			m_hash(DEFAULT_HASH_VALUE)
		{ }

		Node(const T value) : // root node constructor
			Node(nullptr, value)
		{ }

		// virtual functions
		virtual std::vector<std::unique_ptr<Node<T>>> generateNeighbors() const = 0;
		virtual double calcFitness() const = 0;
		virtual double calcCost() const = 0; // TODO

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
		std::span<const std::unique_ptr<Node<T>>> neighbors() const; // lazy initialization
		double fitness() const; // lazy initialization
		bool operator==(const Node<T> &other) const // should be true even if different parents, just equal values
		{
			if (typeid(*this) != typeid(other)) return false;
			return m_value == other.m_value;
		}

		bool operator!=(const Node<T> &other) const;
		size_t hash() const; // hash of value
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
