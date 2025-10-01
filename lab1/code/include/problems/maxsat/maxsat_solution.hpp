#pragma once

#include "metaheuristic/solution.hpp"
#include "problems/maxsat/bit_array.hpp"
#include <cstdint>
#include <vector>

namespace Problems
{
	class MaxsatSolution : public Solution<std::vector<BitArray>>
	{
	public:
		MaxsatSolution(std::vector<BitArray> value);
		~MaxsatSolution() = default;
		std::string output() const override;
	};
}
