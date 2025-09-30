#pragma once

#include "problems/maxsat/maxsat_problem.hpp"
#include <string>
namespace Problems
{
	class CnfReader
	{
	private:
		std::vector<char> m_contents;
		size_t m_i;

		char curr();
		void skipTillEndline();
	public:
		CnfReader(const std::string& filename);
		MaxsatProblem read();
	};
}
