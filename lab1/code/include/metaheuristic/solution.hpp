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
		virtual ~Solution();
		T value();
		virtual void print();
	};
}

#include "metaheuristic/solution.ipp"
