# include "problems/maxsat/cnf_expression.hpp"
#include <iostream>

using namespace Problems;

// cnf should be 1-indexed, there can be no negative 0
CnfExpression::CnfExpression(std::vector<CnfClause>&& clauses) :
	m_clauses(std::move(clauses))
{
}

bool CnfExpression::evaluate(const BitArray& arr) const
{
	for (const CnfClause& clause : m_clauses)
	{
		if (!clause.evaluate(arr))
		{
			return false;
		}
	}
	return true;
}

uint64_t CnfExpression::evaluateNum(const BitArray& arr) const
{
	uint64_t counter = 0;
	for (const CnfClause& clause : m_clauses)
		if (clause.evaluate(arr)) counter++;
	return counter;
}
size_t CnfExpression::size() const
{
	return m_clauses.size();
}
