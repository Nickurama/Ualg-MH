# include "problems/maxsat/cnf_clause.hpp"
#include <iostream>

using namespace Problems;

// cnf should be 1-indexed, there can be no negative 0
CnfClause::CnfClause(std::vector<int32_t>&& cnf) :
	m_cnf(std::move(cnf))
{
}

// arr should have at least as many bits as the number of the variables in the cnf.
bool CnfClause::evaluate(const BitArray& arr) const
{
	const size_t arr_size = arr.size();
	for (int32_t val : m_cnf)
	{
		if (val < 0)
		{
			if (!arr[arr_size + val]) // left to right semantic
			{
				return true;
			}
		}
		else
		{
			if (arr[arr_size - val]) // left to right semantic
			{
				return true;
			}
		}
	}
	return false;
}

std::vector<int32_t> CnfClause::getRelatedVariables() const
{
	return m_cnf;
}
