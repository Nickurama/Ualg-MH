#pragma once

#include "node.hpp"

namespace Metaheuristic
{
	template<typename T, typename G>
	class Problem
	{
	protected:
		Node<T> m_rootNode;

	public:
		Problem(T root_value);
		virtual ~Problem() = default;

		virtual G check(Node<T>) = 0;
		std::vector<std::unique_ptr<Node<T>>> getRootNodes();
	};
}

#include "metaheuristic/problem.ipp"
