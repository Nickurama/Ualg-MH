#include "problems/maxsat/maxsat_problem.hpp"
#include "problems/maxsat/maxsat_node.hpp"
#include "problems/maxsat/maxsat_solution.hpp"
#include <iostream>

using namespace Problems;

// WARNING: NOT MAXSAT, THE PROBLEM IS ACTUALLY JUST DEFINED AS LISTING THE NUMBER OF SOLUTIONS.
MaxsatProblem::MaxsatProblem(CnfExpression&& expression, size_t size) :
	m_size(size),
	m_max_iter(getMaxIterations(m_size)),
	m_expression(std::move(expression)),
	m_root_nodes(genRootNodes()),
	m_neighbor_generator(),
	m_iterations(0),
	m_should_stop(false),
	m_rolling_solution(m_root_nodes[0]->value()),
	m_rolling_fitness(evaluate(m_rolling_solution))
{
	MaxsatNode::setProblem(const_cast<MaxsatProblem&>(*this));
}

std::vector<std::unique_ptr<Node<BitArray>>> MaxsatProblem::genRootNodes() const
{
	std::vector<std::unique_ptr<Node<BitArray>>> vect;
	vect.emplace_back(MaxsatNode::createRoot<MaxsatNode>(BitArray(m_size)));
	return vect;
}

const std::vector<std::unique_ptr<Node<BitArray>>>& MaxsatProblem::getRootNodes()
{
	return m_root_nodes;
}

NeighborGenerator<BitArray>& MaxsatProblem::getNeighborGenerator()
{
	return m_neighbor_generator;
}

void MaxsatProblem::evaluate(const std::vector<Node<BitArray>*>& nodes)
{
	if (nodes.empty())
	{
		m_should_stop = true;
		return;
	}

	for (const Node<BitArray>* node : nodes)
	{
		evaluate(node);
	}

	m_iterations++;
}

void MaxsatProblem::evaluate(const Node<BitArray>* node)
{
	uint64_t evals = m_expression.evaluateNum(node->value());
	if (evals == m_expression.size())
	{
		m_solution = node->value();
		m_should_stop = true;
	}
	else if (evals > m_rolling_fitness)
	{
		m_rolling_solution = node->value();
		m_rolling_fitness = evaluate(m_rolling_solution);
	}
}

uint64_t MaxsatProblem::evaluate(const BitArray& bits) const
{
	return m_expression.evaluateNum(bits);
}

constexpr uint64_t MaxsatProblem::getMaxIterations(uint32_t k) const
{
	return k > 63 ? ~0ul : 1ul << k;
}

uint64_t MaxsatProblem::maxFitness() const
{
	return m_expression.size();
}

// no matter what algorithm is being used, if it goes over this, the problem deems that it should be stopped
bool MaxsatProblem::shouldTerminate() const
{
	return (m_iterations >= m_max_iter) || m_should_stop;
}

bool MaxsatProblem::shouldTerminate(const std::vector<Node<BitArray>*>&) const
{
	return shouldTerminate();
}

bool MaxsatProblem::hasSolution() const
{
	return shouldTerminate();
}

std::unique_ptr<const Solution<BitArray>> MaxsatProblem::getSolution()
{
	return std::make_unique<MaxsatSolution>(m_solution, const_cast<MaxsatProblem&>(*this));
}

std::unique_ptr<const Solution<BitArray>> MaxsatProblem::getCurrentSolution()
{
	return std::make_unique<MaxsatSolution>(m_rolling_solution, const_cast<MaxsatProblem&>(*this));
}
