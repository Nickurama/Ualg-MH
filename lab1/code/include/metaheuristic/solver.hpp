#pragma once

#include "metaheuristic/algorithm.hpp"
#include "metaheuristic/problem.hpp"
#include "metaheuristic/solution.hpp"
#include <memory>
namespace Metaheuristic
{
	template<typename NodeType, typename SolutionType>
	class Solver
	{
	public:
		Solver(const Solver&) = default;
		Solver& operator=(const Solver&) = default;
		Solver(const Solver&&) = delete;
		Solver& operator=(const Solver&&) = delete;

		const Solution<SolutionType> solve(Problem<NodeType, SolutionType> problem, Algorithm<NodeType> algorithm);
	};
}
