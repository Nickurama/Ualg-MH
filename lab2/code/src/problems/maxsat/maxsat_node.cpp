#include "problems/maxsat/maxsat_node.hpp"
#include <iostream>

using namespace Problems;

double MaxsatNode::fitness() const
{
	return maxsat_problem->evaluate(value());
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
