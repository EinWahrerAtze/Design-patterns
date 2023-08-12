//
// observer.hpp
//
// Created by Denis Fedorov on Wed Jul 12 2023
//

#pragma once
#include "common.hpp"
#include "object.hpp"

namespace pattern
{
	template <typename Object, typename State>
	class Observer
	{
	public:
		using OnUpdate = std::function<void(const Object &, State, const std::string &)>;

		explicit Observer(OnUpdate on_update) : m_on_update(std::move(on_update))
		{
			
		}

		auto Update(const Object & object, State state, const std::string & message) -> void
		{
			m_on_update(object, state, message);
		}
	private:
		OnUpdate m_on_update;
	};
}