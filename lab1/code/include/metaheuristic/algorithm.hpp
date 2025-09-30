#pragma once

#include "metaheuristic/neighbor_generator.hpp"
#include "metaheuristic/node.hpp"
#include <vector>

namespace Metaheuristic
{
	template<typename T>
	class Algorithm
	{
	private:

	protected:
		Algorithm() = default;

	public:
		// pure virtual class
		Algorithm(const Algorithm&) = delete;
		Algorithm& operator=(const Algorithm&) = delete;
		Algorithm(const Algorithm&&) = delete;
		Algorithm& operator=(const Algorithm&&) = delete;
		virtual ~Algorithm() {};

		virtual void evaluate(const std::vector<Node<T>*>& nodes) = 0;
		virtual bool shouldTerminate(const std::vector<Node<T>*>& nodes) const = 0;
		virtual std::vector<std::unique_ptr<Node<T>>> getNeighbors(const std::vector<Node<T>*>& nodes, NeighborGenerator<T>& gen) = 0;
		virtual const std::vector<Node<T>*> chooseNodes(const std::vector<Node<T>*>& nodes, const std::vector<Node<T>*>& neighbors) = 0;
	};
}

#include "metaheuristic/algorithm.ipp"
