//
// object.hpp
//
// Created by Denis Fedorov on Wed Jul 12 2023
//

#pragma once
#include "common.hpp"

namespace pattern
{
	template <typename, typename>
	class Observer;

	class Object
	{
	public:
		enum class State
		{
			WARNING,
			ERROR,
			FATAL_ERROR
		};

		using ObjectObserver = Observer<Object, State>;

		auto Attach(ObjectObserver *) -> bool;
		auto Detach(ObjectObserver *) -> bool;

		auto Warning(const std::string &) const -> void;
		auto Error(const std::string &) const -> void;
		auto FatalError(const std::string &) const -> void;
	private:
		auto Notify(State, const std::string &) const -> void;
	private:
		std::set<ObjectObserver *> m_observers;
	};
}