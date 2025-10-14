#pragma once

#include <cstdint>
#include <vector>

#include "problems/maxsat/cnf_clause.hpp"

namespace Problems
{
	class CnfExpression
	{
	private:
		std::vector<CnfClause> m_clauses;

	public:
		CnfExpression(std::vector<CnfClause>&& clauses);
		~CnfExpression() = default;

		// all copy and move operators should work correctly by default
		CnfExpression(const CnfExpression& other) = default;
		CnfExpression(CnfExpression&& other) = default;
		CnfExpression& operator=(const CnfExpression& other) = default;
		CnfExpression& operator=(CnfExpression&& other) = default;

		bool evaluate(const BitArray& arr) const;
		uint64_t evaluateNum(const BitArray& arr) const;
		size_t size() const;
	};
}
