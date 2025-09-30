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

	BitArray ba(120);
	std::cout << ba[119] << '\n';
	ba.set(119, true);
	std::cout << ba[119] << '\n';
	ba.flip(119);
	std::cout << ba[119] << '\n';
	ba.flip(119);

	std::unique_ptr<Node<BitArray>> n = MaxsatNode::createRoot<MaxsatNode>(std::move(ba));
	std::cout << n->value()[119] << '\n';

	std::vector<int32_t> test = {1, -3};
	CnfClause i(std::move(test));
	std::vector<CnfClause> clauses = { i };
	MaxsatProblem p(std::move(clauses), 3);
	p.getRootNodes();





	BitArray b(65);
	for (int i = 0; i < 65; i++)
	{
		b.set(i, 1);
	}
	b.set(64, 0);
	for (int i = 0; i < 65; i++)
	{
		std::cout << b[64 - i];
	}
	std::cout << '\n';
	b.increment();
	for (int i = 0; i < 65; i++)
	{
		std::cout << b[64 - i];
	}
	std::cout << '\n';

	BitArray c(16);
	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 16; i++)
		{
			std::cout << c[15 - i];
		}
		std::cout << '\n';
		++c;
	}

	// std::unique_ptr<Metaheuristic::Algorithm> algorithm = std::make_unique<Algorithms::NaiveAlgorithm>();

	// Problems::MaxsatNode node0("owo");
	// Problems::MaxsatNode node1("owo");
	// std::cout << (node0 == node1) << "\n";

	MaxsatProblem problem = CnfReader::read(input_filename);
	NaiveAlgorithm<BitArray> algorithm = NaiveAlgorithm<BitArray>();
	Solver<BitArray, uint32_t> solver(problem, algorithm);
	std::unique_ptr<const Solution<uint32_t>> solution = solver.solve();
	solution->print();
	// FileWriter::write(solution.output(), output_filename);
}
