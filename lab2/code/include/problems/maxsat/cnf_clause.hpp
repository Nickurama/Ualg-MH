#pragma once

#include <cstdint>
#include <vector>

#include "problems/maxsat/bit_array.hpp"

namespace Problems
{
	class CnfClause
	{
	private:
		std::vector<int32_t> m_cnf;

	public:
		CnfClause(std::vector<int32_t>&& cnf);
		~CnfClause() = default;

		// all copy and move operators should work correctly by default
		CnfClause(const CnfClause& other) = default;
		CnfClause(CnfClause&& other) = default;
		CnfClause& operator=(const CnfClause& other) = default;
		CnfClause& operator=(CnfClause&& other) = default;

		bool evaluate(const BitArray& arr) const;
	};
}
