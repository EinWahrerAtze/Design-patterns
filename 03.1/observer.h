//
//  observer.h
//  Patterns homeworks
//
//  Created by Denis Fedorov on 01.03.2023.

#pragma once
#include <memory>
#include <string>
#include <string_view>
#include "logger.h"

namespace pattern
{
	struct observer
	{
		virtual ~observer() = default;

		virtual void on_warning(const std::string_view message) const = 0;
		virtual void on_error(const std::string_view message) const = 0;
		virtual void on_fatal_error(const std::string_view message) const = 0;
	};

	class warning_handler : public observer
	{
	public:
		warning_handler() : m_log_console(std::make_unique<log_console>())
		{

		}

		void on_warning(const std::string_view message) const override
		{
			m_log_console->print(message);
		}

		void on_error(const std::string_view message) const override
		{

		}

		void on_fatal_error(const std::string_view message) const override
		{

		}
	private:
		std::unique_ptr<log_command> m_log_console;
	};

	class error_handler : public observer
	{
	public:
		error_handler(const std::string_view path) : m_log_console(std::make_unique<log_file>(path))
		{
			
		}

		void on_warning(const std::string_view message) const override
		{

		}

		void on_error(const std::string_view message) const override
		{
			m_log_console->print(message);
		}

		void on_fatal_error(const std::string_view message) const override
		{

		}
	private:
		std::unique_ptr<log_command> m_log_console;
	};

	class fatal_error_handler : public observer
	{
	public:
		fatal_error_handler(const std::string_view path) : m_log_file(std::make_unique<log_file>(path)),
														   m_log_console(std::make_unique<log_console>())
		{
			
		}

		void on_warning(const std::string_view message) const override
		{

		}

		void on_error(const std::string_view message) const override
		{

		}

		void on_fatal_error(const std::string_view message) const override
		{
			m_log_file->print(message);
			m_log_console->print(message);
		}
	private:
		std::unique_ptr<log_command> m_log_file;
		std::unique_ptr<log_command> m_log_console;
	};
}