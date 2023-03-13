//
//  main.cpp
//  Patterns homeworks
//
//  Created by Denis Fedorov on 13.03.2023.

#include <fstream>
#include <iostream>
#include "chain.h"

namespace pattern
{
	enum class msg_type
	{
		WARNING,
		ERROR,
		FATAL_ERROR,
		INDETERMINATE
	};

	class warning_handler : public handler<msg_type>
	{
	public:
		bool accept(const message<msg_type> & msg) override
		{
			if (msg.id == msg_type::WARNING)
			{
				log(std::cout, msg);
				return true;
			}
			else
			{
				return false;
			}
		}
	};

	class error_handler : public handler<msg_type>
	{
	public:
		error_handler(const std::string_view filename)
		{
			m_fout.open(filename.data(), std::ios_base::out);
		}

		bool accept(const message<msg_type> & msg) override
		{
			if (msg.id == msg_type::ERROR && m_fout.is_open())
			{
				log(m_fout, msg);
				return true;
			}
			else
			{
				return false;
			}
		}
	private:
		std::ofstream m_fout;
	};

	class fatal_error_handler : public handler<msg_type>
	{
	private:
		bool accept(const message<msg_type> & msg) override
		{
			if (msg.id == msg_type::FATAL_ERROR)
			{
				throw std::runtime_error {"fatal error: \""s + msg.body + "\"\n"s};
				return true;
			}
			else
			{
				return false;
			}
		}
	};

	class indeterminate_handler : public handler<msg_type>
	{
	private:
		bool accept(const message<msg_type> & msg) override
		{
			if (msg.id == msg_type::INDETERMINATE)
			{
				throw std::runtime_error {"indeterminate message: \""s + msg.body + "\"\n"s};
				return true;
			}
			else
			{
				return false;
			}
		}
	};
}

int main()
{
	using namespace pattern;

	handler_collection<msg_type> collection;

	collection.add(std::make_unique<indeterminate_handler>());
	collection.add(std::make_unique<fatal_error_handler>());
	collection.add(std::make_unique<error_handler>("out.txt"s));
	collection.add(std::make_unique<warning_handler>());

	try
	{
		collection.handle(message<msg_type>(msg_type::WARNING, "warning message"s));
		collection.handle(message<msg_type>(msg_type::ERROR, "error message"s));
		collection.handle(message<msg_type>(msg_type::FATAL_ERROR, "fatal error message"s));
		collection.handle(message<msg_type>(msg_type::INDETERMINATE, "indeterminate message"s));
	}
	catch (const std::runtime_error & ex)
	{
		std::cout << ex.what();
	}

	return 0;
}