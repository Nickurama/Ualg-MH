#pragma once

#include "metaheuristic/solution.hpp"
#include <cstdint>

namespace Problems
{
	class MaxsatSolution : public Solution<uint32_t>
	{
	public:
		MaxsatSolution(uint32_t value);
		~MaxsatSolution() = default;
		void print() override;
	};
}
