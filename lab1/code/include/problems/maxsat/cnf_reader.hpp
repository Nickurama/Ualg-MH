#pragma once

#include "problems/maxsat/maxsat_problem.hpp"
#include <string>
namespace Problems
{
	class CnfReader
	{
	private:
		std::vector<char> m_contents;
		size_t m_i;
		std::vector<char> m_buffer;
		int32_t m_num_vars;
		uint64_t m_num_clauses;
		std::vector<CnfClause> m_clauses;

		char curr();
		void skipTillEndline();
		void seekProblem();
		void stopReading();
		void skipLine();
		void readProblem();
		void readToWordBuffer();
		void processProblemStatement();
		void seekNextWord();
		std::string readNextWord();
		uint64_t readNextUint64();
		int64_t readNextInt32();
		void throwIfReachedEnd();
		void processProblemLines();
		void processProblemClause();
		void forward();
		bool reachedEnd();
		bool reachedEffectiveEnd();

	public:
		CnfReader(const std::string& filename);
		std::unique_ptr<MaxsatProblem> read();
	};
}
