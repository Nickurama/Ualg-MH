
using namespace Metaheuristic;

template<typename NodeType, typename SolutionType>
const Solution<SolutionType> Solver<NodeType, SolutionType>::solve(Problem<NodeType, SolutionType> problem, Algorithm<NodeType> algorithm)
{
	Solution<SolutionType> solution;
	std::vector<std::unique_ptr<Node<NodeType>>> nodes = problem.getRootNodes();
	NeighborGenerator<NodeType> neighborGenerator = problem.getNeighborGenerator();

	// note: some problems require problem knowledge to understand if the algorithm should terminate.
	// some other problems just require the algorithm to acknowledge it has found a solution.
	// problem solutions take priority to algorithm solutions.
	// with this, we achieve encapsulation in which the problem doesn't have to know what algorithm is
	// solving it, and likewise, the algorithm doesn't know what problem it is solving

	// that said, it could also be that an algorithm has terminated, but the problem also has a solution, in which case
	// it should 

	// problem.considerNodes(nodes);
	problem.evaluate(nodes);
	while (problem.shouldTerminate(nodes) || algorithm.shouldTerminate(nodes))
	{
		// generate neighbors
		std::vector<std::unique_ptr<Node<NodeType>>> neighbors = algorithm.getNeighbors(nodes, neighborGenerator);
		// pick nodes to be used
		nodes = algorithm.chooseNodes(nodes, neighbors);
		// give nodes for problem to consider if a solution has been found or for problem-based solutions
		problem.evaluate(nodes);
		// algorithm.considerNodes(nodes);
		// problem.considerNodes(nodes);
	}

	if (problem.hasSolution())
	{
		solution = problem.getSolution();
	}
	else
	{
		solution = algorithm.getCurrentSolution();
	}

	return solution;
}

