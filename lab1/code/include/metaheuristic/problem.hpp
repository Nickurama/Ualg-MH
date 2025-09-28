#pragma once

#include "node.hpp"
#include "metaheuristic/neighbor_generator.hpp"

namespace Metaheuristic
{
	template<typename NodeType, typename ProblemType>
	class Problem
	{
	public:
		Problem() = delete;
		virtual ~Problem() = default;

		// virtual functions
		virtual std::vector<std::unique_ptr<Node<NodeType>>> getRootNodes() = 0;
		virtual NeighborGenerator<NodeType>& getNeighborGenerator() const = 0;
		virtual void evaluate(std::vector<std::unique_ptr<Node<NodeType>>> &nodes) = 0;
		virtual bool shouldTerminate(std::vector<std::unique_ptr<Node<NodeType>>> &nodes) const = 0;
		virtual bool hasSolution() const = 0;
	};
}
