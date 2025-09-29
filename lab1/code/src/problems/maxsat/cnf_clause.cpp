# include "problems/maxsat/cnf_clause.hpp"

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
		int32_t abs_val = val & 0x7FFFFFFF;
		if (val < 0)
		{
			if (!arr[abs_val])
			{
				return true;
			}
		}
		else
		{
			if (arr[abs_val])
			{
				return true;
			}
		}
	}
	return false;
}
