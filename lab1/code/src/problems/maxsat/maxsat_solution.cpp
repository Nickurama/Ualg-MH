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
	os << "solutions ordered { x1 x2 x3 ... xn}\n";
	for (BitArray b : solutions)
	{
		os << b << '\n';
	}
	return os.str();
}
