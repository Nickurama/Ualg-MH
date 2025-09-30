#pragma once
#include "metaheuristic/algorithm.hpp"

namespace Algorithms
{
	template<typename T>
	class NaiveAlgorithm : public Metaheuristic::Algorithm<T>
	{
	private:
	public:
		NaiveAlgorithm() = default;
		~NaiveAlgorithm() = default;

		void evaluate(const std::vector<Node<T>*>& nodes);
		bool shouldTerminate(const std::vector<Node<T>*>& nodes) const;
		std::vector<std::unique_ptr<Node<T>>> getNeighbors(const std::vector<Node<T>*>& nodes, NeighborGenerator<T>& gen);
		const std::vector<Node<T>*> chooseNodes(const std::vector<Node<T>*>& nodes, const std::vector<Node<T>*>& neighbors);
	};
}
