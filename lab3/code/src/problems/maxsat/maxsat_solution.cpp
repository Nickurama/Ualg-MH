#include "problems/maxsat/maxsat_solution.hpp"

#include <iostream>
#include <sstream>

using namespace Problems;

// MaxsatSolution::MaxsatSolution(std::vector<BitArray> value) :
MaxsatSolution::MaxsatSolution(const BitArray& value, const MaxsatProblem& problem) :
	Solution<BitArray>(value),
	m_problem(problem)

{
}

std::string MaxsatSolution::output() const
{
	std::ostringstream os;
	const BitArray& solution = value();

	os << "solution: ";
	os << solution << '\n';
	os << "fitness: (" << m_problem.evaluate(solution) << "/" << m_problem.maxFitness() << ")\n";

	return os.str();
}
