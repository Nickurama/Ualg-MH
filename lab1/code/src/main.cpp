#include <iostream>
#include <memory>

#include "algorithm.hpp"
#include "naiveAlgorithm.hpp"
#include "problem.hpp"
#include "cnfReader.hpp"
#include "solution.hpp"
#include "solver.hpp"
#include "fileWriter.hpp"

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

	std::unique_ptr<Algorithm> algorithm = std::make_unique<NaiveAlgorithm>();

	Problem problem = CnfReader::read(input_filename);
	// Solution solution = Solver.solve(problem, algorithm);
	// FileWriter::write(solution.output(), output_filename);
}
