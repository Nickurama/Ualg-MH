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
		virtual void getHammingNeighbors(const Node<T>& node, uint32_t distance, std::vector<Node<T>*>& neighbors);
		virtual Node<T>* getHammingNeighbor(const Node<T>& node, uint32_t distance);
		virtual Node<T>* getHammingNeighborUnderDistance(const Node<T>& node, uint32_t distance);

		// randomness
		virtual std::vector<Node<T>*> getRandomNeighbors(const Node<T>& node, int k);
		virtual Node<T>* getRandomNeighbor(const Node<T>& node);
		virtual std::unique_ptr<Node<T>> getRandomNode();

		// iterative
		virtual bool hasNextNeighbor(Node<T>);
		virtual Node<T>* getNextNeighbor(Node<T>& node);

		// genetic
		virtual Node<T>* mutate(const Node<T>& node, double rate);
		virtual Node<T>* crossover(const Node<T>& first, const Node<T>& second, int k);
	};
}

#include "metaheuristic/neighbor_generator.ipp"
