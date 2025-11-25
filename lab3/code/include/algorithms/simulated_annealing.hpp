#pragma once
#include "metaheuristic/algorithm.hpp"
#include <functional>

namespace Algorithms
{
	template<typename T>
	class SimulatedAnnealing: public Metaheuristic::Algorithm<T>
	{
	protected:
		uint32_t m_hamming_distance;
		bool m_should_terminate;
		double m_initial_temperature;
		double m_temperature;
		std::function<double(double)> m_cooling_schedule;
		std::unique_ptr<Node<T>> m_initial_node;
		uint64_t m_evaluations;
		uint64_t m_max_evals;
		bool m_first;

	public:
		SimulatedAnnealing(uint32_t hamming_distance, double initial_temperature, std::function<double(double)> cooling_schedule, uint64_t max_evals);
		virtual ~SimulatedAnnealing() = default;

		virtual void evaluate(const std::vector<Node<T>*>& nodes) override;
		virtual bool shouldTerminate(const std::vector<Node<T>*>& nodes) const override;
		virtual void getNeighbors(const std::vector<Node<T>*>& nodes, NeighborGenerator<T>& gen, std::vector<Node<T>*>& neighbors) override;
		virtual void chooseNodes(std::vector<Node<T>*>& nodes, const std::vector<Node<T>*>& neighbors) override;
		virtual uint64_t restarts() const override;
		virtual uint64_t evaluations() const override;
	};
}

#include "algorithms/simulated_annealing.ipp"
