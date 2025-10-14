#pragma once

#include <string>
#include "metaheuristic/node.hpp"
#include "problems/maxsat/bit_array.hpp"
#include "problems/maxsat/maxsat_problem.hpp"

namespace Problems
{
	class MaxsatNode : public Metaheuristic::Node<BitArray>
	{
	private:
		static const MaxsatProblem* maxsat_problem;

	public:
		~MaxsatNode() override = default;

		static void setProblem(const MaxsatProblem& problem);

		double fitness() const override;
		// double heuristic() const override;
		// double cost() const override;
	};
}
