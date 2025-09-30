#include "problems/maxsat/cnf_reader.hpp"
#include "io/file_io.hpp"

using namespace Problems;

CnfReader::CnfReader(const std::string& filename) :
	m_i(0)
{
	m_contents = IO::FileIO::read(filename);
}

char CnfReader::curr()
{
	return m_contents[m_i];
}

void CnfReader::skipTillEndline()
{
	while (curr() != EOF || curr() != '\n')
	{
		m_i++;
	}
}

// TODO: do the same but with enums
std::unique_ptr<MaxsatProblem> CnfReader::read()
{
	// while(m_i < m_contents.size())
	// {
	// 	processLine();
	//
	// 	// processLine
	// 	switch(curr())
	// 	{
	// 		case EOF:
	// 			m_i = m_contents.size(); // stops while loop
	// 			stopReading();
	// 			break;
	// 		case 'c': // comment
	// 			skipTillEndline();
	// 			break;
	// 		case 'p': // problem statement
	// 			readProblem();
	// 			break;
	// 		case '-':
	// 		case isNumber(curr()): //curr >= 48 && curr <= 57/
	// 			break;
	// 		default:
	// 			throw std::runtime_error("unvalid file format.");
	// 			break;
	// 	}
	// 	// processLine
	// }

	std::vector<int32_t> x = { -1, 2, 3 };
	// x1 x2 x3 result
	// 0  0  0  1
	// 0  0  1  1
	// 0  1  0  1
	// 0  1  1  1
	// 1  0  0  0
	// 1  0  1  1
	// 1  1  0  1
	// 1  1  1  1
	CnfClause clause(std::move(x));
	std::vector clauses = { clause };
	CnfExpression expr(std::move(clauses));
	return std::make_unique<MaxsatProblem>(std::move(expr), 3);
}
