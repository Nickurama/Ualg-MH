#include "problems/maxsat/maxsat_solution.hpp"

#include <iostream>

using namespace Problems;

MaxsatSolution::MaxsatSolution(uint32_t value) :
	Solution<uint32_t>(value)
{
}

void MaxsatSolution::print() const
{
	std::cout << value() << "\n";
}
