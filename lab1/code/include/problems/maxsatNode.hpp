#pragma once

#include <string>
#include "metaheuristic/node.hpp"

namespace Problems
{
	class MaxsatNode : public Metaheuristic::Node<std::string>
	{
	protected:
		std::vector<std::unique_ptr<Metaheuristic::Node<std::string>>> generateNeighbors() const override
		{
			return { };
		}

		double calcFitness() const override
		{
			return 0;
		}

	public:
		MaxsatNode(const std::string value) : Metaheuristic::Node<std::string>(value) {};
	};
}
