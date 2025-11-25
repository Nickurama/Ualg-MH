#pragma once

#include "metaheuristic/algorithm.hpp"
#include "metaheuristic/problem.hpp"
#include "metaheuristic/solution.hpp"
#include "metaheuristic/neighbor_generator.hpp"
#include <memory>

namespace Metaheuristic
{
	template<typename NodeType, typename SolutionType>
	class Solver
	{
	private:
		Problem<NodeType, SolutionType>& m_problem;
		Algorithm<NodeType>& m_algorithm;
		NeighborGenerator<NodeType>& m_neighborGenerator;
		std::vector<Node<NodeType>*> m_nodes;
		uint64_t m_iterations;

	public:
		Solver(Problem<NodeType, SolutionType>& problem, Algorithm<NodeType>& algorithm);
		~Solver() = default;
		Solver(const Solver&) = default;
		Solver& operator=(const Solver&) = default;
		Solver(const Solver&&) = delete;
		Solver& operator=(const Solver&&) = delete;

		std::unique_ptr<const Solution<SolutionType>> solve();
		uint64_t iterations() const;
	};
}

#include <metaheuristic/solver.ipp>
