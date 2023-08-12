//
// object.cpp
//
// Created by Denis Fedorov on Thu Jul 13 2023
//

#include "object.hpp"
#include "observer.hpp"

namespace pattern
{
	auto Object::Attach(ObjectObserver * observer) -> bool
	{
		auto [position, success] {m_observers.insert(observer)};
		return success;
	}

	auto Object::Detach(ObjectObserver * observer) -> bool
	{
		return m_observers.erase(observer) > static_cast<size_t>(0);
	}

	auto Object::Warning(const std::string & message) const -> void
	{
		this->Notify(State::WARNING, message);
	}

	auto Object::Error(const std::string & message) const -> void
	{
		this->Notify(State::ERROR, message);
	}

	auto Object::FatalError(const std::string & message) const -> void
	{
		this->Notify(State::FATAL_ERROR, message);
	}

	auto Object::Notify(State state, const std::string & message) const -> void
	{
		for (auto it {m_observers.cbegin()}; it != m_observers.cend();)
		{
			const auto pos {it++};
			(*pos)->Update(*this, state, message);
		}
	}
}