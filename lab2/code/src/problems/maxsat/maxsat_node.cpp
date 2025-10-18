#include "problems/maxsat/maxsat_node.hpp"
#include <iostream>

using namespace Problems;

const MaxsatProblem* MaxsatNode::maxsat_problem = nullptr;

MaxsatNode::MaxsatNode() :
	m_fitness_cache(0.0),
	m_satisfiable_clauses()
{

}

double MaxsatNode::fitness() const
{
	if (m_fitness_cache == 0.0)
	{
		const BitArray& self_value = value();
		const BitArray& parent_value = parent()->value();

		if (isRoot())
		{
			std::cout << "calculating raw fitness\n";
			m_fitness_cache = MaxsatNode::maxsat_problem->evaluate(self_value, m_satisfiable_clauses);

			return m_fitness_cache;
		}

		std::cout << "calculating specific fitness\n";
		std::vector<size_t> differences = self_value.getDifferences(parent_value);

		uint64_t parent_specific_fitness = MaxsatNode::maxsat_problem->evaluateSpecific(self_value, differences);
		uint64_t self_specific_fitness = MaxsatNode::maxsat_problem->evaluateSpecific(parent_value, differences);

		m_fitness_cache = (uint64_t)parent()->fitness() + (self_specific_fitness - parent_specific_fitness);
		std::cout << "done!\n";
	}

	return m_fitness_cache;
}

void MaxsatNode::setProblem(const MaxsatProblem& problem)
{
	MaxsatNode::maxsat_problem = &problem;
}

// double MaxsatNode::heuristic() const
// {
// }
//
// double MaxsatNode::cost() const
// {
// }
