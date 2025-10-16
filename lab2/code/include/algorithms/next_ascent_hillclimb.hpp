#pragma once
#include "metaheuristic/algorithm.hpp"

namespace Algorithms
{
	template<typename T>
	class NAHillclimb: public Metaheuristic::Algorithm<T>
	{
	private:
		uint32_t m_hamming_distance;
		bool m_should_terminate;
		uint32_t m_multistarts;
		bool m_restart;
		std::vector<std::unique_ptr<Node<T>>> m_initial_nodes;
		uint64_t m_restarts;
		uint64_t m_evaluations;

	public:
		NAHillclimb(uint32_t hamming_distance, uint32_t multistarts);
		~NAHillclimb() = default;

		void evaluate(const std::vector<Node<T>*>& nodes) override;
		bool shouldTerminate(const std::vector<Node<T>*>& nodes) const override;
		void getNeighbors(const std::vector<Node<T>*>& nodes, NeighborGenerator<T>& gen, std::vector<Node<T>*>& neighbors) override;
		void chooseNodes(std::vector<Node<T>*>& nodes, const std::vector<Node<T>*>& neighbors) override;
		uint64_t restarts() const;
		uint64_t evaluations() const;
	};
}

#include "algorithms/next_ascent_hillclimb.ipp"
