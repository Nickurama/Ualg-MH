#include <iostream>
#include <memory>
#include <chrono>

#include "algorithms/next_ascent_hillclimb.hpp"
#include "algorithms/variable_neighbourhood_ascent_hillclimb.hpp"
#include "metaheuristic/algorithm.hpp"
#include "metaheuristic/problem.hpp"
#include "metaheuristic/rng.hpp"
#include "metaheuristic/solution.hpp"
#include "metaheuristic/solver.hpp"
#include "metaheuristic/node.hpp"
#include "io/file_io.hpp"
#include "algorithms/naive_algorithm.hpp"
#include "problems/maxsat/cnf_reader.hpp"
#include "problems/maxsat/maxsat_node.hpp"
#include "problems/maxsat/maxsat_problem.hpp"
#include "problems/maxsat/maxsat_solution.hpp"
#include "input_reader.hpp"

using namespace Problems;
using namespace Metaheuristic;
using namespace Algorithms;

int main(int argc, char *argv[])
{
	// problem setup
	CnfReader cnfReader(getInputFilename(argc, argv));
	std::unique_ptr<MaxsatProblem> problem = cnfReader.read();
	std::unique_ptr<Algorithm<BitArray>> algorithm = getAlgorithm(argc, argv);
	Solver<BitArray, BitArray> solver(*problem, *algorithm);

	// rng setup
	RandomNumberGenerator::setRandomSeed();
	// RandomNumberGenerator::setSeed(1974712772);
	std::cout << "seed: " << RandomNumberGenerator::seed() << "\n";

	// solve
	std::unique_ptr<const Solution<BitArray>> solution = solver.solve();

	// print
	std::cout << solution->output();
	std::cout << "restarts: " << algorithm->restarts() << "\n";
	std::cout << "iterations: " << solver.iterations() << "\n";
	std::cout << "evaluations: " << algorithm->evaluations() << "\n";
	std::cout << "optimal: " << (problem->hasSolution() ? "yes" : "no") << "\n";
	std::cout << "elapsed: " << duration_cast<std::chrono::milliseconds>(solution->duration()).count() << "ms\n";
	// IO::FileIO::write(solution->output(), output_filename);

	return 0;
}
