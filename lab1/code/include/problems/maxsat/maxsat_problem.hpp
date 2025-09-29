#pragma once

#include "metaheuristic/problem.hpp"
#include "problems/maxsat/bit_array.hpp"
#include "problems/maxsat/cnf_clause.hpp"
#include "problems/maxsat/maxsat_neighbor_generator.hpp"

namespace Problems
{
	class MaxsatProblem : public Metaheuristic::Problem<BitArray, int>
	{
	private:
		size_t m_size;
		std::vector<CnfClause> m_clauses;
		MaxsatNeighborGenerator m_neighbor_generator;
		const std::vector<std::unique_ptr<Node<BitArray>>> m_root_nodes;

		std::vector<std::unique_ptr<Node<BitArray>>> genRootNodes() const;

	public:
		MaxsatProblem(std::vector<CnfClause>&& clauses, size_t size); // ownership transfer
		~MaxsatProblem() = default;

		// virtual functions
		const std::vector<std::unique_ptr<Node<BitArray>>>& getRootNodes();
		NeighborGenerator<BitArray>& getNeighborGenerator();
		void evaluate(const std::vector<Node<BitArray>*> nodes);
		bool shouldTerminate(const std::vector<Node<BitArray>*> nodes) const;
		bool hasSolution() const;
	};
}
