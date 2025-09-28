#pragma once

#include "metaheuristic/problem.hpp"
#include "problems/maxsat/bit_array.hpp"

namespace Problems
{
	class MaxsatProblem : public Metaheuristic::Problem<BitArray, int>
	{
	public:
		MaxsatProblem();
		~MaxsatProblem() = default;

		// virtual functions
		const std::vector<std::unique_ptr<Node<BitArray>>>& getRootNodes();
		NeighborGenerator<BitArray>& getNeighborGenerator() const;
		void evaluate(const std::vector<Node<BitArray>*> nodes);
		bool shouldTerminate(const std::vector<Node<BitArray>*> nodes) const;
		bool hasSolution() const;
	};
}
