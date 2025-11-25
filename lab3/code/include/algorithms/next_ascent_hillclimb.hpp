#pragma once
#include "metaheuristic/algorithm.hpp"

namespace Algorithms
{
	template<typename T>
	class NAHillclimb: public Metaheuristic::Algorithm<T>
	{
	protected:
		uint32_t m_hamming_distance;
		bool m_should_terminate;
		uint32_t m_multistarts;
		uint32_t m_initial_multistarts;
		bool m_restart;
		std::vector<std::unique_ptr<Node<T>>> m_initial_nodes;
		uint64_t m_restarts;
		uint64_t m_evaluations;
		uint64_t m_max_evals;

	public:
		NAHillclimb(uint32_t hamming_distance, uint32_t multistarts, uint64_t max_evals);
		virtual ~NAHillclimb() = default;

		virtual void evaluate(const std::vector<Node<T>*>& nodes) override;
		virtual bool shouldTerminate(const std::vector<Node<T>*>& nodes) const override;
		virtual void getNeighbors(const std::vector<Node<T>*>& nodes, NeighborGenerator<T>& gen, std::vector<Node<T>*>& neighbors) override;
		virtual void chooseNodes(std::vector<Node<T>*>& nodes, const std::vector<Node<T>*>& neighbors) override;
		virtual uint64_t restarts() const override;
		virtual uint64_t evaluations() const override;
	};
}

#include "algorithms/next_ascent_hillclimb.ipp"
