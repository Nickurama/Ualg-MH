#pragma once

#include "metaheuristic/solution.hpp"
#include "problems/maxsat/bit_array.hpp"
#include "problems/maxsat/maxsat_problem.hpp"
#include <cstdint>
#include <vector>

namespace Problems
{
	class MaxsatSolution : public Solution<BitArray>
	{
	private:
		const MaxsatProblem& m_problem;
	public:
		MaxsatSolution(const BitArray& value, const MaxsatProblem& problem);
		~MaxsatSolution() = default;
		std::string output() const override;
	};
}
