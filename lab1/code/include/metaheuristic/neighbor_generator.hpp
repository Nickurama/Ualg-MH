#pragma once

#include "metaheuristic/node.hpp"
#include <memory>
#include <vector>

namespace Metaheuristic
{
	template<Hashable T>
	class NeighborGenerator
	{
	protected:
		NeighborGenerator() = default;

	public:
		// pure virtual class
		NeighborGenerator(const NeighborGenerator&) = delete;
		NeighborGenerator& operator=(const NeighborGenerator&) = delete;
		NeighborGenerator(const NeighborGenerator&&) = delete;
		NeighborGenerator& operator=(const NeighborGenerator&&) = delete;
		virtual ~NeighborGenerator() {};

		// state-space
		virtual std::vector<std::unique_ptr<Node<T>>> getAllNeighbors(const Node<T>& node);

		// randomness
		virtual std::vector<std::unique_ptr<Node<T>>> getRandomNeighbors(const Node<T>& node, int k);
		virtual std::unique_ptr<Node<T>> getRandomNeighbor(const Node<T>& node);
		virtual std::unique_ptr<Node<T>> getRandomNode();

		// iterative
		virtual bool hasNextNeighbor(Node<T>);
		virtual std::unique_ptr<Node<T>> getNextNeighbor(Node<T>& node);

		// genetic
		virtual std::unique_ptr<Node<T>> mutate(const Node<T>& node, double rate);
		virtual std::unique_ptr<Node<T>> crossover(const Node<T>& first, const Node<T>& second);
	};
}

#include "metaheuristic/neighbor_generator.ipp"
