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
		mutable double m_fitness_cache;
		mutable BitArray m_satisfiable_clauses;

	public:
		MaxsatNode();
		~MaxsatNode() override = default;

		static void setProblem(const MaxsatProblem& problem);

		double fitness() const override;
		// double heuristic() const override;
		// double cost() const override;
	};
}
