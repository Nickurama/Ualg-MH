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
	for (int32_t val : m_cnf)
	{
		// int32_t abs_val = (val + 2) & 0x7FFFFFFF;
		// int32_t abs_val_i = std::abs(val) - 1;
		int32_t abs_val_i = arr.size() - std::abs(val); // left to right semantic
		if (val < 0)
		{
			if (!arr[abs_val_i])
			{
				return true;
			}
		}
		else
		{
			if (arr[abs_val_i])
			{
				return true;
			}
		}
	}
	return false;
}
