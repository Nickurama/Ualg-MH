#include "problems/maxsat/maxsat_problem.hpp"
#include "problems/maxsat/maxsat_node.hpp"

#include <iostream>

using namespace Problems;

MaxsatProblem::MaxsatProblem(CnfExpression&& expression, size_t size) :
	m_size(size),
	m_expression(std::move(expression)),
	m_neighbor_generator(),
	m_root_nodes(genRootNodes())
{
}

std::vector<std::unique_ptr<Node<BitArray>>> MaxsatProblem::genRootNodes() const
{
	// TODO
	return { };
}

const std::vector<std::unique_ptr<Node<BitArray>>>& MaxsatProblem::getRootNodes()
{
	BitArray root_val(m_size);
	std::unique_ptr<Node<BitArray>> node = MaxsatNode::createRoot<MaxsatNode>(root_val);
	node->fitness();
	return m_root_nodes;
}

NeighborGenerator<BitArray>& MaxsatProblem::getNeighborGenerator()
{
	return m_neighbor_generator;
}

void MaxsatProblem::evaluate(const std::vector<Node<BitArray>*> nodes)
{
	// TODO
	std::cout << nodes[0] << "\n";
}

bool MaxsatProblem::shouldTerminate(const std::vector<Node<BitArray>*> nodes) const
{
	// TODO
	std::cout << nodes[0] << "\n";
	return false;
}

bool MaxsatProblem::hasSolution() const
{
	// TODO
	return false;
}
