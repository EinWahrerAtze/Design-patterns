//
//  decorator.h
//  Design patterns
//
//  Created by Denis Fedorov on 28.02.2023.

#pragma once
#include "common.h"

namespace pattern
{
	struct text
	{
		virtual ~text() = default;

		virtual void render(const std::string_view string) const
		{
			std::cout << string;
		}
	};

	struct decorator : public text
	{
		explicit decorator(text * text) : m_text(text)
		{

		}
	protected:
		std::unique_ptr<text> m_text;
	};

	struct italic : public decorator
	{
		explicit italic(text * text) : decorator(text)
		{

		}

		void render(const std::string_view string) const override
		{
			std::cout << "<i>";
			m_text->render(string);
			std::cout << "</i>";
		}
	};

	struct bold : public decorator
	{
		explicit bold(text * text) : decorator(text)
		{

		}

		void render(const std::string_view string) const override
		{
			std::cout << "<b>";
			m_text->render(string);
			std::cout << "</b>";
		}
	};

	struct paragraph : public decorator
	{
		explicit paragraph(text * text) : decorator(text)
		{

		}

		void render(const std::string_view string) const override
		{
			std::cout << "<p>";
			m_text->render(string);
			std::cout << "</p>";
		}
	};

	struct reversed : public decorator
	{
		explicit reversed(text * text) : decorator(text)
		{

		}

		void render(const std::string_view string) const override
		{
			auto rstring {static_cast<std::string>(string.data())};
			std::reverse(rstring.begin(), rstring.end());
			m_text->render(rstring);
		}
	};

	struct link : public decorator
	{
		explicit link(text * text) : decorator(text)
		{

		}

		void render(const std::string_view link, const std::string_view description) const
		{
			std::cout << "<a href=" << link << ">";
			m_text->render(description);
			std::cout << "</a>";
		}
	};
}