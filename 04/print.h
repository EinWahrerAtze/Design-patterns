//
//  print.cpp
//  Patterns homeworks
//
//  Created by Denis Fedorov on 13.03.2023.

#pragma once
#include <string>
#include <string_view>
#include <fstream>

namespace output
{
	using namespace std::literals::string_literals;

	struct datafile
	{
		datafile(const std::string_view data) : m_data(data)
		{

		}

		virtual ~datafile() = default;
		virtual std::string print() const = 0;

		friend std::ostream & operator << (std::ostream & os, const datafile & file)
		{
			os << file.print() << '\n';
			return os;
		}
	protected:
		std::string m_data;
	};
	
	struct text : public datafile
	{
		using datafile::datafile;

		std::string print() const override
		{
			return m_data;
		}
	};

	struct html : public datafile
	{
		using datafile::datafile;

		std::string print() const override
		{
			return "<html>"s + m_data + "<html/>"s;
		}
	};

	struct json : public datafile
	{
		using datafile::datafile;

		std::string print() const override
		{
			return "{ \"data\": \""s + m_data + "\" }"s;
		}
	};

	void send(std::ostream & destination, const datafile & file)
	{
		destination << file;
	}
}