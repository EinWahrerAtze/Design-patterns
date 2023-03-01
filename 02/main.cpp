//
//  main.cpp
//  Design patterns
//
//  Created by Denis Fedorov on 28.02.2023.

#include "units.h"

int main(int argc, const char * argv[])
{
	std::cout << "testing decorator pattern:\n";
	auto text_block {std::make_unique<pattern::link>(new pattern::text)};
	text_block->render("www.some_link.com"s, "some description"s);

	std::cout << "\n\ntesting proxy pattern\n";
	try
	{
		auto one_shot_db_ptr {std::make_unique<pattern::one_shot_db>(new pattern::database(), 5)};

		for (auto i {0}; i < 10; ++i)
		{
			std::cout << "count: " << i << " " << one_shot_db_ptr->get_data("hello"s) << "\n";
		}
	}
	catch (const std::invalid_argument & error)
	{
		std::cout << error.what() << "\n";
	}

	return 0;
}