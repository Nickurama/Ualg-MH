#include "problems/maxsat/cnf_reader.hpp"
#include "io/file_io.hpp"

using namespace Problems;

static MaxsatProblem read(const std::string& filename)
{
	std::vector<char> contents = IO::FileIO::read(filename);
}
