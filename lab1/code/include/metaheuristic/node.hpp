#pragma once

#include <memory>
#include <span>
#include <vector>

constexpr size_t DEFAULT_HASH_VALUE = ~0ul;

namespace Metaheuristic
{
	template<typename T>
	concept Hashable = requires(T a, T b)
	{
		{ a.hash() } -> std::convertible_to<size_t>;
		{ a == b } -> std::convertible_to<bool>;
	};

	template<Hashable T>
	class Node
	{
	private:
		const Node<T> *m_parent;
		const std::unique_ptr<T> m_value;
		mutable std::vector<std::unique_ptr<Node<T>>> m_neighbors; // lazy initialization
		mutable double m_fitness; // lazy initialization
		mutable bool m_hasFitness;
		mutable size_t m_hash; // lazy initialization
	
	protected:
		// constructors
		Node<T>(const std::unique_ptr<T> value); // root node constructor
		Node<T>(const Node<T> *parent, const std::unique_ptr<T> value);

		// virtual functions
		virtual std::vector<std::unique_ptr<Node<T>>> generateNeighbors() = 0;
		virtual double calcFitness() = 0;

		// copy constructors
		Node<T>(const Node<T> &other) = delete;
		Node<T> &operator=(const Node<T> &other) = delete;

		// move constructors
		Node<T>(Node &&other) = default;
		Node<T> &operator=(Node<T> &&other) = default;

	public:
		virtual ~Node<T>() = default;
		inline Node<T> *parent() const;
		inline const T &value() const;
		std::span<const std::unique_ptr<Node<T>>> neighbors() const; // lazy initialization
		double fitness() const; // lazy initialization
		bool operator==(const Node<T> &other) const; // should be true even if different parents, just equal values
		bool operator!=(const Node<T> &other) const;
		size_t hash() const; // hash of value
	};
}
