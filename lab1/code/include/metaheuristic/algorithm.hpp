#pragma once

namespace Metaheuristic
{
	template<typename T>
	class Algorithm
	{
	private:

	protected:
		Algorithm() = default;

	public:
		// pure virtual class
		Algorithm(const Algorithm&) = delete;
		Algorithm& operator=(const Algorithm&) = delete;
		Algorithm(const Algorithm&&) = delete;
		Algorithm& operator=(const Algorithm&&) = delete;
		virtual ~Algorithm() {};

		// virtual Node neighbors() = 0;
	};
}
