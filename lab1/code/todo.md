# General
- [ ] Make template implementation in header
- [ ] Make tpp files
- [ ] Node calcCost()
- [ ] Node virtual calcHeuristic() just calls calcFitness() by default
- [ ] Node heuristic() and cost()
- [ ] change Metaheuristic namespace to Core

# Pseudocode
Node[] nodes = problem.getRootNodes()
Solution<T> solution;
while (algorithm.shouldTerminate(nodes) || problem.shouldTerminate(nodes))
{
    neighbors = { };
    for (node in nodes)
    {
        neighbors.add(problem.genNeighbors(node));
    }
    nodes = algorithm.chooseNodes(neighbors);
}

if (problem.hasSolution())
{
    solution = problem.getSolution();
}
else
{
    solution = algorithm.getCurrentSolution();
}





# Solution

# Problem
describes the problem and encodes it.

# Node

# Algorithm


# Solver













# Problems

## 1
-----------------------------------
### Problem
asks the Node to generate it's neighbors, but if there's only a single source of
node generation through the Node, it means the node has to know how the algorithm
works (besides the problem itself ofc), since it has to know what neighbors the 
algorithm expects. I.e. if it's a genetic algorithm it should generate random
neighbors

### Solution
make node have several ways of generating neighbors.
the base class has virtual public versions of these that throw exceptions saying
it doesn't support those, derived classes that don't implement them will just throw
that exception.

problem.getAllNeighbors(node)
problem.getRandomNeighbor(node)
problem.getRandomNeighbors(node, k)
problem.getRandomNode()
problem.hasNextNeighbor(node)
problem.getNextNeighbor(node)
problem.mutate(node, rate)
problem.crossover(node, other_node)

## 2
-----------------------------------
### Problem
how am I going to count the number of solutions?
Boolean: algorithm needs to ask problem if it has found the solution
Value: algorithm needs to count

### Solution
the loop terminates if either the problem or the algorithm thinks it should terminate
with the current node(s). It might be that the problem is already solved, and because
of abstraction the algorithm doesn't know, or it could be that the algorithm has reached
it's limitation without finding the solution, at which point it should also speak out that
it needs to stop (or reached the end of the algorithm, etc...).

## 3
-----------------------------------
### Problem
how does algorithm call the node's generate neighbors function? it shouldn't
have access to those tools.

### Solution
There is no solver. Algorithm is given the problem and solves it.
this might be bad because if it's a NaiveSearch for example, it should
be enforced to ask the Problem class if it should stop, with this much
power it could break things if the person didn't do that.
Therefore the Algorithm class could be asked "get me a neighbour pool for
this problem, given this node". This also leads to the problem where
the algorithm needs to be given a Problem to solve (constructor?
setProblem()?) maybe the most elegant solution would be to make an interface class
StateSpace or NodeGenerator, that has the classes for generating neighbours,
and give said problem's NodeGenerator to the algorithm as a algorithm.setNodeGenerator()
function, given by the Problem.getNodeGenerator().

## 4
-----------------------------------
### Problem
How does, say, A* get heuristic or cost without knowing the problem?

### Solution
problem.getCost(node) // node has parent
problem.getHeuristic(node)


# Output types
- boolean (satisfibility problems)
- integer/double/string (solving problems)
- configuration (optimization problems)
- path (search problems)
