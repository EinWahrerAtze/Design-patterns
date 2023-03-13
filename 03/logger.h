//
//  logger.h
//  Patterns homeworks
//
//  Created by Denis Fedorov on 01.03.2023.

#pragma once
#include <fstream>
#include <iostream>

namespace pattern
{
	struct log_command
	{
		virtual ~log_command() = default;
		virtual void print(const std::string_view) = 0;
	};

	struct log_console : public log_command
	{
		void print(const std::string_view message) override
		{
			std::cout << message << '\n';
		}
	};

	struct log_file : public log_command
	{
		log_file(const std::string_view path)
		{
			fout.open(path.data(), std::ios_base::out);
		}

		~log_file()
		{
			if (fout.is_open()) { fout.close(); }
		}

		void print(const std::string_view message) override
		{
			fout << message.data() << '\n';
		}
	private:
		std::ofstream fout;
	};
}