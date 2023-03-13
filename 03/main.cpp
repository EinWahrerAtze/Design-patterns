//
//  main.cpp
//  Patterns homeworks
//
//  Created by Denis Fedorov on 01.03.2023.

#include "units.h"

int main(int argc, const char * argv[])
{
	using namespace pattern;
	using namespace std::literals::string_literals;

	auto observer_deleter {[](observer * obs)
	{
		std::cout << "observer removed\n";
		delete obs;
	}};

	object object;

	auto sptr_warnings {std::make_shared<warning_handler>()};
	auto sptr_errors {std::make_shared<error_handler>("errors.txt"s)};
	auto sptr_fatal_errors {std::make_shared<fatal_error_handler>("fatal_errors.txt"s)};

	object.add_observer(std::weak_ptr<observer>(sptr_warnings));
	object.add_observer(std::weak_ptr<observer>(sptr_errors));
	object.add_observer(std::weak_ptr<observer>(sptr_fatal_errors));

	object.warning("first warning"s);
	object.error("first error"s);
	object.fatal_error("first fatal error"s);

	{
		std::shared_ptr<observer> sptr_warnings2 {new warning_handler, observer_deleter};
		std::shared_ptr<observer> sptr_errors2 {new error_handler("errors2.txt"s), observer_deleter};
		std::shared_ptr<observer> sptr_fatal_errors2 {new fatal_error_handler("fatal_errors2.txt"s), observer_deleter};

		object.add_observer(std::weak_ptr<observer>(sptr_warnings2));
		object.add_observer(std::weak_ptr<observer>(sptr_errors2));
		object.add_observer(std::weak_ptr<observer>(sptr_fatal_errors2));

		object.warning("second warning"s);
		object.error("second error"s);
		object.fatal_error("second fatal error"s);
	}

	object.warning("third warning"s);
	object.error("third error"s);
	object.fatal_error("third fatal error"s);

	return 0;
}