#include <iostream>
#include <memory>
#include <chrono>

#include "algorithms/next_ascent_hillclimb.hpp"
#include "algorithms/variable_neighbourhood_ascent_hillclimb.hpp"
#include "metaheuristic/algorithm.hpp"
#include "metaheuristic/problem.hpp"
#include "metaheuristic/rng.hpp"
#include "metaheuristic/solution.hpp"
#include "metaheuristic/solver.hpp"
#include "metaheuristic/node.hpp"
#include "io/file_io.hpp"
#include "algorithms/naive_algorithm.hpp"
#include "problems/maxsat/cnf_reader.hpp"
#include "problems/maxsat/maxsat_node.hpp"
#include "problems/maxsat/maxsat_problem.hpp"
#include "problems/maxsat/maxsat_solution.hpp"


using namespace Problems;
using namespace Metaheuristic;
using namespace Algorithms;

std::unique_ptr<Algorithm<BitArray>> getAlgorithm(int argc, char *argv[]);
std::string getInputFilename(int argc, char *argv[]);
