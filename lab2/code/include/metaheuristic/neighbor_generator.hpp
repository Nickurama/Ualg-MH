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
		virtual std::vector<Node<T>*> getAllNeighbors(const Node<T>& node);

		// randomness
		virtual std::vector<Node<T>*> getRandomNeighbors(const Node<T>& node, int k);
		virtual Node<T>* getRandomNeighbor(const Node<T>& node);
		virtual Node<T>* getRandomNode();

		// iterative
		virtual bool hasNextNeighbor(Node<T>);
		virtual Node<T>* getNextNeighbor(Node<T>& node);

		// genetic
		virtual Node<T>* mutate(const Node<T>& node, double rate);
		virtual Node<T>* crossover(const Node<T>& first, const Node<T>& second);
	};
}

#include "metaheuristic/neighbor_generator.ipp"
