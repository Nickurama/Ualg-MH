#pragma once

namespace Metaheuristic
{
	template<typename T>
	class Solution
	{
	private:
		T m_value;

	public:
		Solution(T value);
		T value();
		virtual void print() = 0;
	};
}

#include "metaheuristic/solution.ipp"
