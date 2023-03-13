//
//  object.h
//  Patterns homeworks
//
//  Created by Denis Fedorov on 01.03.2023.

#pragma once
#include <list>
#include "observer.h"

namespace pattern
{
	class object
	{
	public:
		object() : m_invalid_observer_exist(false)
		{

		}

		void warning(const std::string_view message)
		{
			for (const auto & obs : m_observers)
			{
				if (obs.expired())
				{
					m_invalid_observer_exist = true;
				}
				else
				{
					auto sptr {obs.lock()};
					sptr->on_warning(message);
				}
			}

			if (m_invalid_observer_exist) { this->correct_list(); }
		}

		void error(const std::string_view message)
		{
			for (const auto & obs : m_observers)
			{
				if (obs.expired())
				{
					m_invalid_observer_exist = true;
				}
				else
				{
					auto sptr {obs.lock()};
					sptr->on_error(message);
				}
			}

			if (m_invalid_observer_exist) { this->correct_list(); }
		}

		void fatal_error(const std::string_view message)
		{
			for (const auto & obs : m_observers)
			{
				if (obs.expired())
				{
					m_invalid_observer_exist = true;
				}
				else
				{
					auto sptr {obs.lock()};
					sptr->on_fatal_error(message);
				}
			}

			if (m_invalid_observer_exist) {	this->correct_list(); }
		}

		void add_observer(std::weak_ptr<observer> new_observer)
		{
			m_observers.push_back(new_observer);
		}
	private:
		void correct_list()
		{
			m_observers.remove_if([](std::weak_ptr<observer> wptr)
			{
				return wptr.expired();
			});

			m_invalid_observer_exist = false;
		}
	private:
		bool m_invalid_observer_exist;
		std::list<std::weak_ptr<observer>> m_observers;
	};
}
