#pragma once

#include <string>
#include <chrono>

namespace Metaheuristic
{
	template<typename T>
	class Solution
	{
	private:
		T m_value;
		std::chrono::high_resolution_clock::duration m_duration;

	public:
		Solution(T value);
		virtual ~Solution() = default;
		const T& value() const;
		virtual std::string output() const;
		void setDuration(std::chrono::high_resolution_clock::duration duration);
		std::chrono::high_resolution_clock::duration duration() const;
	};
}

#include "metaheuristic/solution.ipp"
