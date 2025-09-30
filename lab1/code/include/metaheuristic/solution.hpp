#pragma once

#include <string>
namespace Metaheuristic
{
	template<typename T>
	class Solution
	{
	private:
		T m_value;

	public:
		Solution(T value);
		virtual ~Solution() = default;
		T value() const;
		virtual std::string output() const;
	};
}

#include "metaheuristic/solution.ipp"
