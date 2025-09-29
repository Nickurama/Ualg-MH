# include "problems/maxsat/cnf_expression.hpp"

using namespace Problems;

// cnf should be 1-indexed, there can be no negative 0
CnfExpression::CnfExpression(std::vector<CnfClause>&& clauses) :
	m_clauses(std::move(clauses))
{
}

bool CnfExpression::evaluate(const BitArray& arr) const
{
	for (CnfClause clause : m_clauses)
		if (!clause.evaluate(arr)) return false;
	return true;
}
