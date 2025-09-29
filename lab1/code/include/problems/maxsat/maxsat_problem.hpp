#pragma once

#include "metaheuristic/problem.hpp"
#include "problems/maxsat/bit_array.hpp"
#include "problems/maxsat/cnf_expression.hpp"
#include "problems/maxsat/maxsat_neighbor_generator.hpp"

namespace Problems
{
	class MaxsatProblem : public Metaheuristic::Problem<BitArray, int>
	{
	private:
		size_t m_size;
		CnfExpression m_expression;
		MaxsatNeighborGenerator m_neighbor_generator;
		const std::vector<std::unique_ptr<Node<BitArray>>> m_root_nodes;

		std::vector<std::unique_ptr<Node<BitArray>>> genRootNodes() const;

	public:
		MaxsatProblem(CnfExpression&& expression, size_t size); // ownership transfer
		~MaxsatProblem() = default;

		// virtual functions
		const std::vector<std::unique_ptr<Node<BitArray>>>& getRootNodes();
		NeighborGenerator<BitArray>& getNeighborGenerator();
		void evaluate(const std::vector<Node<BitArray>*> nodes);
		bool shouldTerminate(const std::vector<Node<BitArray>*> nodes) const;
		bool hasSolution() const;
	};
}
