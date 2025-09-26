#pragma once

#include "metaheuristic/node.hpp"
#include <memory>
#include <vector>

namespace Metaheuristic
{
	template<typename T>
	class INeighborGenerator
	{
	public:
		// pure virtual class
		INeighborGenerator(const INeighborGenerator&) = delete;
		INeighborGenerator& operator=(const INeighborGenerator&) = delete;
		INeighborGenerator(const INeighborGenerator&&) = delete;
		INeighborGenerator& operator=(const INeighborGenerator&&) = delete;
		virtual ~INeighborGenerator() {};

		// state-space
		virtual std::vector<std::unique_ptr<Node<T>>> getAllNeighbors(const Node<T>& node) = 0;

		// randomness
		virtual std::vector<std::unique_ptr<Node<T>>> getRandomNeighbors(const Node<T>& node, int k) = 0;
		virtual std::unique_ptr<Node<T>> getRandomNeighbor(const Node<T>& node) = 0;
		virtual std::unique_ptr<Node<T>> getRandomNode() = 0;

		// iterative
		virtual bool hasNextNeighbor(Node<T>) = 0;
		virtual std::unique_ptr<Node<T>> getNextNeighbor(Node<T>) = 0;

		// genetic
		virtual std::unique_ptr<Node<T>> mutate(const Node<T>& node, double rate) = 0;
		virtual std::unique_ptr<Node<T>> crossover(const Node<T>& first, const Node<T>& second) = 0;
	};
}
