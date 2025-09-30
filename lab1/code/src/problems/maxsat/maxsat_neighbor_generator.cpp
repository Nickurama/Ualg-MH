#include "problems/maxsat/maxsat_neighbor_generator.hpp"
#include "problems/maxsat/maxsat_node.hpp"

using namespace Problems;

MaxsatNeighborGenerator::MaxsatNeighborGenerator()
{

}

Node<BitArray>& MaxsatNeighborGenerator::getNextNeighbor(Node<BitArray>& node)
{
	BitArray next_arr = node.value(); // copies
	next_arr.increment();
	return node.createChild<MaxsatNode>(std::move(next_arr));
}


// std::vector<std::unique_ptr<Node<BitArray>>> MaxsatNeighborGenerator::getAllNeighbors(const Node<BitArray>& node)
// {
// 	// TODO
// }
//
// std::vector<std::unique_ptr<Node<BitArray>>> MaxsatNeighborGenerator::getRandomNeighbors(const Node<BitArray>& node, int k)
// {
// 	// TODO
// }
//
// std::unique_ptr<Node<BitArray>> MaxsatNeighborGenerator::getRandomNeighbor(const Node<BitArray>& node)
// {
// 	// TODO
// }
//
// std::unique_ptr<Node<BitArray>> MaxsatNeighborGenerator::getRandomNode()
// {
// 	// TODO
// }
//
// bool MaxsatNeighborGenerator::hasNextNeighbor(Node<BitArray>)
// {
// 	// TODO
// }
// std::unique_ptr<Node<BitArray>> MaxsatNeighborGenerator::mutate(const Node<BitArray>& node, double rate)
// {
// 	// TODO
// }
//
// std::unique_ptr<Node<BitArray>> MaxsatNeighborGenerator::crossover(const Node<BitArray>& first, const Node<BitArray>& second)
// {
// 	// TODO
// }
