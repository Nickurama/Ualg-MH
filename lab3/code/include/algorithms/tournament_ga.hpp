#pragma once
#include "metaheuristic/algorithm.hpp"
#include <functional>

namespace Algorithms
{
	template<typename T>
	class TournamentGA: public Metaheuristic::Algorithm<T>
	{
	protected:
		bool m_should_terminate;
		std::vector<std::unique_ptr<Node<T>>> m_initial_nodes;
		uint64_t m_pop_size;
		uint64_t m_num_crossover_points;
		double m_mutation_chance;
		uint64_t m_match_individual_number;
		uint64_t m_evaluations;
		uint64_t m_max_evals;
		bool m_first;

	public:
		TournamentGA(uint64_t pop_size, uint64_t num_crossover_points, double mutation_chance, uint64_t match_individual_number, uint64_t max_evals);
		virtual ~TournamentGA() = default;

		virtual void evaluate(const std::vector<Node<T>*>& nodes) override;
		virtual bool shouldTerminate(const std::vector<Node<T>*>& nodes) const override;
		virtual void getNeighbors(const std::vector<Node<T>*>& nodes, NeighborGenerator<T>& gen, std::vector<Node<T>*>& neighbors) override;
		virtual void chooseNodes(std::vector<Node<T>*>& nodes, const std::vector<Node<T>*>& neighbors) override;
		virtual uint64_t restarts() const override;
		virtual uint64_t evaluations() const override;
	};
}

#include "algorithms/tournament_ga.ipp"
