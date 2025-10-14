#pragma once
#include "metaheuristic/solver.hpp"
#include <iostream>
#include <chrono>

using namespace Metaheuristic;

template<typename NodeType, typename SolutionType>
Solver<NodeType, SolutionType>::Solver(Problem<NodeType, SolutionType>& problem, Algorithm<NodeType>& algorithm) :
	m_problem(problem),
	m_algorithm(algorithm),
	m_neighborGenerator(problem.getNeighborGenerator()),
	m_nodes()
{
	const std::vector<std::unique_ptr<Node<NodeType>>>& root_nodes = problem.getRootNodes();
	for (size_t i = 0; i < root_nodes.size(); i++)
	{
		m_nodes.emplace_back(root_nodes[i].get());
	}
}

template<typename NodeType, typename SolutionType>
std::unique_ptr<const Solution<SolutionType>> Solver<NodeType, SolutionType>::solve()
{
	m_problem.evaluate(m_nodes);
	m_algorithm.evaluate(m_nodes);
	std::vector<Node<NodeType>*> neighbors;
	while (!m_problem.shouldTerminate(m_nodes) && !m_algorithm.shouldTerminate(m_nodes))
	{
		// generate neighbors
		neighbors.clear();
		std::cout << m_nodes.size() << "n\n";
		m_algorithm.getNeighbors(m_nodes, m_neighborGenerator, neighbors);
		std::cout << m_nodes.size() << "n\n";
		// pick nodes to be used
		m_algorithm.chooseNodes(m_nodes, neighbors);
		std::cout << m_nodes.size() << "n\n";
		// give nodes to execute inner logic and to see if a solution has been found solutions
		m_problem.evaluate(m_nodes);
		std::cout << m_problem.shouldTerminate(m_nodes) << '\n';
		std::cout << m_algorithm.shouldTerminate(m_nodes) << '\n';
	}

	return m_problem.hasSolution() ? std::move(m_problem.getSolution()) : std::move(m_problem.getCurrentSolution());
	// return m_problem.hasSolution() ? std::move(m_problem.getSolution()) : std::move(m_algorithm.getCurrentSolution());
}

