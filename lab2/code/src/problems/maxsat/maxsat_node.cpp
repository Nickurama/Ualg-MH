#include "problems/maxsat/maxsat_node.hpp"
#include <iostream>

using namespace Problems;

const MaxsatProblem* MaxsatNode::maxsat_problem = nullptr;

MaxsatNode::MaxsatNode() :
	m_fitness_cache(0.0)
{

}

double MaxsatNode::fitness() const
{
	if (m_fitness_cache == 0.0)
	{
		m_fitness_cache = MaxsatNode::maxsat_problem->evaluate(value());
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
