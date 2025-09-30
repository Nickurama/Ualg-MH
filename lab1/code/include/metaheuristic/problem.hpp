#pragma once

#include "metaheuristic/solution.hpp"
#include "node.hpp"
#include "metaheuristic/neighbor_generator.hpp"

namespace Metaheuristic
{
	template<typename NodeType, typename SolutionType>
	class Problem
	{
	protected:
		Problem() = default;

	public:
		virtual ~Problem() = default;

		// virtual functions
		virtual const std::vector<std::unique_ptr<Node<NodeType>>>& getRootNodes() = 0;
		virtual NeighborGenerator<NodeType>& getNeighborGenerator() = 0;
		virtual void evaluate(const std::vector<Node<NodeType>*>& nodes) = 0;
		virtual bool shouldTerminate(const std::vector<Node<NodeType>*>& nodes) const = 0;
		virtual bool hasSolution() const = 0;
		virtual std::unique_ptr<const Solution<SolutionType>> getSolution() = 0;
		virtual std::unique_ptr<const Solution<SolutionType>> getCurrentSolution() = 0;
	};
}
