#pragma once

#include "metaheuristic/neighbor_generator.hpp"
#include "metaheuristic/node.hpp"
#include "metaheuristic/solution.hpp"
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
		virtual ~Algorithm() = default;

		virtual void evaluate(const std::vector<Node<T>*>& nodes) = 0;
		virtual bool shouldTerminate(const std::vector<Node<T>*>& nodes) const = 0;
		// should put neighbors in "neighbors" parameter. neighbors should be an empty vector.
		virtual void getNeighbors(const std::vector<Node<T>*>& nodes, NeighborGenerator<T>& gen, std::vector<Node<T>*>& neighbors) = 0;
		// should put chosen nodes in "nodes" parameter. nodes is not guaranteed to be empty.
		virtual void chooseNodes(std::vector<Node<T>*>& nodes, const std::vector<Node<T>*>& neighbors) = 0;
		// virtual std::unique_ptr<const Solution<S>> getCurrentSolution() = 0;
	};
}
