#include "problems/maxsat/maxsat_solution.hpp"

#include <iostream>
#include <sstream>

using namespace Problems;

MaxsatSolution::MaxsatSolution(std::vector<BitArray> value) :
	Solution<std::vector<BitArray>>(value)
{
}

std::string MaxsatSolution::output() const
{
	const std::vector<BitArray>& solutions = value();
	std::ostringstream os;
	os << "satisfiable solutions: " << std::to_string(solutions.size()) << '\n';
	for (BitArray b : solutions)
	{
		os << b << '\n';
	}
	return os.str();
}
