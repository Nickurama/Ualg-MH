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
	m_variable_clause_relation(m_expression.size()),
	m_neighbor_generator(*this),
	m_iterations(0),
	m_should_stop(false),
	m_rolling_solution(m_root_nodes[0]->value()),
	m_rolling_fitness(evaluate(m_rolling_solution))
{
	MaxsatNode::setProblem(const_cast<MaxsatProblem&>(*this));

	for (size_t clause = 0; clause < m_expression.size(); clause++)
	{

		std::vector<int32_t> clause_variables = m_expression.getRelatedVariablesToClause(clause);
		for (int32_t clause_variable : clause_variables)
		{
			uint32_t variable = std::abs(clause_variable);
			m_variable_clause_relation[variable].emplace_back(clause);
		}
	}
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

uint64_t MaxsatProblem::evaluate(const BitArray& bits, BitArray& satisfiableClauses) const
{
	return m_expression.evaluateNum(bits, satisfiableClauses);
}

uint64_t MaxsatProblem::evaluateSpecific(const BitArray& bits, const std::vector<size_t>& variableIndices) const
{
	uint64_t counter = 0;
	BitArray trueEvaluatingClauses(m_expression.size());

	for (size_t variable : variableIndices)
	{
		const std::vector<uint32_t>& clauses = m_variable_clause_relation[variable];

		for (uint32_t clause : clauses)
		{
			if (!trueEvaluatingClauses[clause] && m_expression.evaluateClauseAt(bits, clause))
			{
				trueEvaluatingClauses.set(clause, 1);
				counter++;
			}
		}
	}

	return counter;
}

constexpr uint64_t MaxsatProblem::getMaxIterations(uint32_t k) const
{
	return k > 63 ? ~0ul : 1ul << k;
}

uint64_t MaxsatProblem::maxFitness() const
{
	return m_expression.size();
}

size_t MaxsatProblem::size() const
{
	return m_size;
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
