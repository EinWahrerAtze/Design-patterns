//
//  chain.h
//  Patterns homeworks
//
//  Created by Denis Fedorov on 13.03.2023.

#pragma once
#include <list>
#include <memory>
#include <string>
#include <string_view>
#include <stdexcept>

namespace pattern
{
	using namespace std::literals::string_literals;

	template <typename T>
	struct message
	{
		T id;
		std::string body;

		message(T type) : id(type)
		{

		}

		message(T type, const std::string_view message) : id(type), body(message)
		{

		}

		friend void operator >> (const std::string_view data, message<T> & msg)
		{
			msg.body = data;
		}

		friend std::ostream & operator << (std::ostream & os, const message<T> & msg)
		{
			os << msg.body;
			return os;
		}
	};

	template <typename T>
	class handler
	{
	public:
		virtual ~handler() = default;
		virtual bool accept(const message<T> & msg) = 0;
	protected:
		void log(std::ostream & os, const message<T> & msg)
		{
			os << msg << '\n';
		}
	};

	template <typename T>
	class handler_collection
	{
	public:
		void add(std::unique_ptr<handler<T>> handler)
		{
			m_handlers.push_back(std::move(handler));
		}

		void handle(const message<T> & msg)
		{
			bool done {false};
			for (const auto & handler : m_handlers)
			{
				if (handler->accept(msg))
				{
					done = true;
					break;
				}
			}

			if (!done) { throw std::runtime_error {"unhandled message recieved: \""s + msg.body + "\"\n"s}; }
		}
	private:
		std::list<std::unique_ptr<handler<T>>> m_handlers;
	};
}