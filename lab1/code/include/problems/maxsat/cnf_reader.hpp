#pragma once

#include "problems/maxsat/maxsat_problem.hpp"
#include <string>
namespace Problems
{
	class CnfReader
	{
	public:
		static MaxsatProblem read(const std::string& filename);
	};
}
