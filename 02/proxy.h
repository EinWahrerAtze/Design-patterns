//
//  proxy.h
//  Design patterns
//
//  Created by Denis Fedorov on 28.02.2023.

#pragma once
#include "common.h"

using namespace std::literals;

namespace pattern
{

	struct database
	{
		std::string get_data(const std::string_view key) const
		{
			return "database: " + static_cast<std::string>(key.data());
		}
	};

	class one_shot_db
	{
	public:
		one_shot_db(database * db, uint32_t limit) : m_count(), m_limit(limit), m_database(db)
		{
			if (m_limit > std::numeric_limits<uint32_t>::max() / 2)
			{
				throw std::invalid_argument {"negative value not allowed"};
			}
		}

		std::string get_data(const std::string_view key)
		{
			if (m_count < m_limit)
			{
				++m_count;
				return m_database->get_data(key);
			}
			else
			{
				return "error"s;
			}
		}
	private:
		uint32_t m_count;
		const uint32_t m_limit;
		std::unique_ptr<database> m_database;
	};
}