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

// note: some problems require problem knowledge to understand if the algorithm should terminate.
// some other problems just require the algorithm to acknowledge it has found a solution.
// problem solutions take priority to algorithm solutions.
// with this, we achieve encapsulation in which the problem doesn't have to know what algorithm is
// solving it, and likewise, the algorithm doesn't know what problem it is solving

// that said, it could also be that the algorithm has terminated (has a solution),
// but the problem also has a solution, in which case it should prioritize the problem's solution.
template<typename NodeType, typename SolutionType>
const Solution<SolutionType> Solver<NodeType, SolutionType>::solve()
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

	return m_problem.hasSolution() ? m_problem.getSolution() : m_algorithm.getCurrentSolution();
}

