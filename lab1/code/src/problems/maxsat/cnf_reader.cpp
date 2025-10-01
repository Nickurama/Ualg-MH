#include "problems/maxsat/cnf_reader.hpp"
#include "io/file_io.hpp"
#include <format>
#include <iostream>

using namespace Problems;

CnfReader::CnfReader(const std::string& filename) :
	m_contents(),
	m_i(0),
	m_buffer(),
	m_num_vars(0),
	m_num_clauses(0),
	m_clauses()
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
		forward();
	}
}

// TODO: do the same but with enums
std::unique_ptr<MaxsatProblem> CnfReader::read()
{
	seekProblem();

	if (m_clauses.empty()) throw std::runtime_error("no problem statement in file.");

	return std::make_unique<MaxsatProblem>(std::move(m_clauses), m_num_vars);

	// std::vector<int32_t> x = { -1, 2, 3 };
	// CnfClause clause(std::move(x));
	// std::vector clauses = { clause };
	// CnfExpression expr(std::move(clauses));
	// return std::make_unique<MaxsatProblem>(std::move(expr), 3);
}

void CnfReader::seekProblem()
{
	std::cout << m_contents.size() << "\n";
	while(!reachedEnd())
	{
		if (curr() == 'c') // comment
		{
			skipLine();
		}
		else if (curr() == 'p') // problem statement
		{
			std::cout << "owo\n";
			forward();
			readProblem();
			break;
		}
		else
		{
			throw std::runtime_error("invalid file format..");
		}
	}
}

void CnfReader::skipLine()
{
	while (!reachedEnd() && curr() != '\n')
	{
		forward();
	}
	forward();
}

void CnfReader::throwIfReachedEnd()
{
	if (m_i >= m_contents.size())
	{
		throw std::runtime_error("invalid file format.");
	}
}

void CnfReader::readToWordBuffer()
{
	m_buffer.clear();
	while (!reachedEnd() && curr() != ' ' && curr() != '\n')
	{
		m_buffer.emplace_back(curr());
		forward();
	}
}

void CnfReader::forward()
{
	m_i++;
}

bool CnfReader::reachedEnd()
{
	return m_i >= m_contents.size();
}

bool CnfReader::reachedEffectiveEnd()
{
	seekNextWord();
	return m_i >= m_contents.size();
}

void CnfReader::seekNextWord()
{
	while (!reachedEnd() && (curr() == ' ' || curr() == '\n'))
	{
		forward();
	}
}

std::string CnfReader::readNextWord()
{
	seekNextWord();
	throwIfReachedEnd();
	readToWordBuffer();
	return std::string(m_buffer.begin(), m_buffer.end());
}

uint64_t CnfReader::readNextUint64()
{
	std::string str = readNextWord();
	return std::stoul(str);
}

int64_t CnfReader::readNextInt32()
{
	std::string str = readNextWord();
	return std::stoi(str);
}

void CnfReader::processProblemStatement()
{
	std::string format = readNextWord();
	std::cout << "format: " << format << "\n";
	if (format != "cnf") throw std::runtime_error("problem format not supported.");

	try
	{
		m_num_vars = readNextInt32();
		std::cout << "num_vars: " << m_num_vars << "\n";
		m_num_clauses = readNextUint64();
		std::cout << "num_clauses: " << m_num_clauses << "\n";
		m_clauses.reserve(m_num_clauses);
	}
	catch(std::exception& e)
	{
		throw std::runtime_error(std::format("invalid problem arguments: {}", e.what()));
	}
}

void CnfReader::processProblemLines()
{
	for (size_t i = 0; i < m_num_clauses; i++)
	{
		processProblemClause();
	}
}

void CnfReader::processProblemClause()
{
	std::cout << "new line found!\n";
	std::vector<int32_t> vars;
	while (!reachedEffectiveEnd())
	{
		std::cout << m_i << "\n";
		std::cout << m_contents[m_i] << "\n";
		int32_t value = readNextInt32();
		std::cout << "value read: " << value << "\n";
		if (value > m_num_vars || value < -m_num_vars) throw std::runtime_error("variable outside of bounds in file.");
		if (value == 0) break;

		vars.emplace_back(value);
	}

	if (vars.empty()) throw std::runtime_error("clauses missing in file.");
	std::cout << "finished reading line\n";

	m_clauses.emplace_back(CnfClause(std::move(vars)));
}

void CnfReader::readProblem()
{
	std::cout << "problem found!\n";
	processProblemStatement();
	processProblemLines();
}
