#include "metaheuristic/solver.hpp"

using namespace Metaheuristic;

template<typename NodeType, typename SolutionType>
Solver<NodeType, SolutionType>::Solver(Problem<NodeType, SolutionType>& problem, Algorithm<NodeType>& algorithm) :
	m_problem(problem),
	m_algorithm(algorithm),
	m_neighborGenerator(problem.getNeighborGenerator()),
	m_nodes(problem.getRootNodes())
{
}

template<typename NodeType, typename SolutionType>
std::unique_ptr<const Solution<SolutionType>> Solver<NodeType, SolutionType>::solve()
{
	m_problem.evaluate(m_nodes);
	m_algorithm.evaluate(m_nodes);
	while (m_problem.shouldTerminate(m_nodes) || m_algorithm.shouldTerminate(m_nodes))
	{
		// generate neighbors
		std::vector<std::unique_ptr<Node<NodeType>>> neighbors = m_algorithm.getNeighbors(m_nodes, m_neighborGenerator);
		// pick nodes to be used
		m_nodes = m_algorithm.chooseNodes(m_nodes, neighbors);
		// give nodes to execute inner logic and to see if a solution has been found solutions
		m_problem.evaluate(m_nodes);
		m_algorithm.evaluate(m_nodes);
	}

	return m_problem.hasSolution() ? std::move(m_problem.getSolution()) : m_problem.getCurrentSolution();
	// return m_problem.hasSolution() ? std::move(m_problem.getSolution()) : std::move(m_algorithm.getCurrentSolution());
}

