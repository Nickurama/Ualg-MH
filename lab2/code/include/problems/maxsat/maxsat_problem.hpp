#pragma once

#include "metaheuristic/problem.hpp"
#include "problems/maxsat/bit_array.hpp"
#include "problems/maxsat/cnf_expression.hpp"
#include "problems/maxsat/maxsat_neighbor_generator.hpp"

namespace Problems
{
	class MaxsatProblem : public Metaheuristic::Problem<BitArray, std::vector<BitArray>>
	{
	private:
		const size_t m_size;
		const uint64_t m_max_iter;
		const CnfExpression m_expression;
		const std::vector<std::unique_ptr<Node<BitArray>>> m_root_nodes;
		MaxsatNeighborGenerator m_neighbor_generator;
		std::vector<BitArray> m_solutions;
		uint64_t m_iterations;
		bool m_should_stop;

		std::vector<std::unique_ptr<Node<BitArray>>> genRootNodes() const;
		bool shouldTerminate() const;
		constexpr uint64_t getMaxIterations(uint32_t k) const;
		void evaluate(const Node<BitArray>* node);

	public:
		MaxsatProblem(CnfExpression&& expression, size_t size); // ownership transfer
		~MaxsatProblem() = default;

		const std::vector<std::unique_ptr<Node<BitArray>>>& getRootNodes() override;
		NeighborGenerator<BitArray>& getNeighborGenerator() override;
		void evaluate(const std::vector<Node<BitArray>*>& nodes) override;
		uint64_t evaluate(const BitArray& bits) const;
		bool shouldTerminate(const std::vector<Node<BitArray>*>& nodes) const override;
		bool hasSolution() const override;
		std::unique_ptr<const Solution<std::vector<BitArray>>> getSolution() override;
		std::unique_ptr<const Solution<std::vector<BitArray>>> getCurrentSolution() override;
	};
}
