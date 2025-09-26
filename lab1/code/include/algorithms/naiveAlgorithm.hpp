#pragma once
#include "metaheuristic/algorithm.hpp"

namespace Algorithms
{
	class NaiveAlgorithm : public Metaheuristic::Algorithm<int>
	{
	private:
	public:
		NaiveAlgorithm();
		~NaiveAlgorithm();
	};
}
