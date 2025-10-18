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

using namespace Problems;
using namespace Metaheuristic;
using namespace Algorithms;

// constexpr const char * DEFAULT_OUTPUT_FILE_NAME = "solved.out";

int main(int argc, char *argv[])
{
	// input handling
	int argnum = argc - 1;
	if (argnum < 1)
	{
		std::cout << "Usage: maxsat <input_file> <hamming_distance> <multistart>" << std::endl;
	}
	std::string input_filename = argv[1];
	uint32_t hamming_distance = 1;
	uint32_t multistart = 0;
	try
	{
		if (argnum >= 2)
			hamming_distance = std::stoi(argv[2]);
	}
	catch (std::exception&)
	{
		std::cout << "Usage: maxsat <input_file> <hamming_distance> <multistart>" << std::endl;
		std::cout << "hamming_distance should be an integer\n";
		std::exit(1);
	}
	try
	{
		if (argnum >= 3)
			multistart = std::stol(argv[3]);
	}
	catch (std::exception&)
	{
		std::cout << "Usage: maxsat <input_file> <hamming_distance> <multistart>" << std::endl;
		std::cout << "multistart should be a long\n";
		std::exit(1);
	}


	// solver
	CnfReader cnfReader(input_filename);
	RandomNumberGenerator::setRandomSeed();
	// RandomNumberGenerator::setSeed(1974712772);

	std::cout << "seed: " << RandomNumberGenerator::seed() << "\n";
	std::unique_ptr<MaxsatProblem> problem = cnfReader.read();
	// NaiveAlgorithm<BitArray> algorithm = NaiveAlgorithm<BitArray>();
	// NAHillclimb<BitArray> algorithm = NAHillclimb<BitArray>(hamming_distance, multistart);
	VNAHillclimb<BitArray> algorithm = VNAHillclimb<BitArray>(hamming_distance, multistart);
	Solver<BitArray, BitArray> solver(*problem, algorithm);

	auto start = std::chrono::high_resolution_clock::now();

	std::unique_ptr<const Solution<BitArray>> solution = solver.solve();

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = duration_cast<std::chrono::milliseconds>(end - start);

	std::cout << solution->output();
	std::cout << "restarts: " << algorithm.restarts() << "\n";
	std::cout << "iterations: " << solver.iterations() << "\n";
	std::cout << "evaluations: " << algorithm.evaluations() << "\n";
	std::cout << "optimal: " << (problem->hasSolution() ? "yes" : "no") << "\n";
	std::cout << "elapsed: " << duration.count() << "ms\n";
	// IO::FileIO::write(solution->output(), output_filename);




	// 2 parts:
	// * I know which clauses have what variables
	// 1 - variables that changed (in comparison to? parent!) -> what clauses are affected?
	// 2 - variables that didn't change -> does not matter?

	// step 0: parent should keep track of which clauses evaluated to true
	// step 1: detect what changes from parent/child
	// step 2: check what clauses are affected
	// step 3: recompute clauses
	// step 4: compute fitness of child based on clause recomputations
}
