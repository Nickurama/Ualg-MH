#pragma once

#include <string>
#include "metaheuristic/node.hpp"
#include "problems/maxsat/bit_array.hpp"

namespace Problems
{
	class MaxsatNode : public Metaheuristic::Node<BitArray>
	{
	private:
		MaxsatNode();
	public:
		~MaxsatNode() override = default;

		double fitness() const override;
		double heuristic() const override;
		double cost() const override;
	};
}

#include "problems/maxsat/maxsat_node.cpp"
