#include <iostream>
#include <memory>

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

constexpr const char * DEFAULT_OUTPUT_FILE_NAME = "solved.out";

int main(int argc, char *argv[])
{
	int argnum = argc - 1;
	if (argnum < 2)
	{
		std::cout << "Usage: maxsat <input_file> <algorithm>" << std::endl;
		std::cout << "Usage: maxsat <input_file> <algorithm> <output_file>" << std::endl;
	}
	std::string input_filename = argv[1];
	std::string algorithm_name = argv[2];
	std::string output_filename = argnum >= 3 ? argv[3] : DEFAULT_OUTPUT_FILE_NAME;

	CnfReader cnfReader(input_filename);
	std::unique_ptr<MaxsatProblem> problem = cnfReader.read();
	NaiveAlgorithm<BitArray> algorithm = NaiveAlgorithm<BitArray>();
	Solver<BitArray, uint32_t> solver(*problem, algorithm);
	std::unique_ptr<const Solution<uint32_t>> solution = solver.solve();
	std::cout << solution->output() << "\n";
	// IO::FileIO::write(solution->output(), output_filename);
}
