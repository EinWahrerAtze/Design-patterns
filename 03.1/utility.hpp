//
// command.hpp
//
// Created by Denis Fedorov on Wed Jul 12 2023
//

#pragma once
#include "common.hpp"

namespace pattern::utility
{
	class Logger
	{
		using PrintFunction = std::function<void(const std::string &)>;

	public:
		Logger(PrintFunction action) : m_action(std::move(action))
		{
			if (!m_action)
			{
				throw std::invalid_argument {"Invalid argument given!"s};
			}
		}

		auto Print(const std::string & message) const -> void
		{
			m_action(message);
		}
	private:
		PrintFunction m_action;
	};

	// template <typename T = std::ostream>
	// class Logger
	// {
	// public:
	// 	using OutputDestination = T;

	// 	explicit Logger(OutputDestination & stream = std::cout) : m_stream(stream)
	// 	{

	// 	}

	// 	auto Print(const std::string & message) -> void
	// 	{
	// 		m_stream << message;
	// 	}
	// private:
	// 	OutputDestination & m_stream;
	// };
}