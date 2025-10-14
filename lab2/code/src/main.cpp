#include <iostream>
#include <memory>
#include <chrono>

#include "algorithms/next_ascent_hillclimb.hpp"
#include "metaheuristic/algorithm.hpp"
#include "metaheuristic/problem.hpp"
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
	int argnum = argc - 1;
	if (argnum < 1)
	{
		std::cout << "Usage: maxsat <input_file>" << std::endl;
	}
	std::string input_filename = argv[1];
	// std::string algorithm_name = argv[2];
	// std::string output_filename = argnum >= 3 ? argv[3] : DEFAULT_OUTPUT_FILE_NAME;

	CnfReader cnfReader(input_filename);
	std::unique_ptr<MaxsatProblem> problem = cnfReader.read();
	// NaiveAlgorithm<BitArray> algorithm = NaiveAlgorithm<BitArray>();
	int hamming_distance = 1;
	NAHillclimb<BitArray> algorithm = NAHillclimb<BitArray>(hamming_distance);
	Solver<BitArray, BitArray> solver(*problem, algorithm);

	// ERROR ADD CACHING TO FITNESS

	auto start = std::chrono::high_resolution_clock::now();

	std::unique_ptr<const Solution<BitArray>> solution = solver.solve();

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = duration_cast<std::chrono::milliseconds>(end - start);

	std::cout << solution->output() << "\n";
	std::cout << "elapsed: " << duration.count() << "ms\n";
	// IO::FileIO::write(solution->output(), output_filename);
}
