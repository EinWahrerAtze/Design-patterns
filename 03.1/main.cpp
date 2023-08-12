//
// main.cpp
//
// Created by Denis Fedorov on Thu Jul 13 2023
//


#include "object.hpp"
#include "utility.hpp"
#include "observer.hpp"

using namespace pattern;
using namespace pattern::utility;

struct PrintToFile
{
	PrintToFile(const std::string & path)
	{
		fout.open(path, std::ios_base::app | std::ios_base::out);

		if (!fout.is_open())
		{
			throw std::runtime_error {"Could not open \"" + path + "\" for output!"s};
		}
	}

	auto operator()(const std::string & message) -> void
	{
		fout << message << '\n';
	}
private:
	std::ofstream fout;
};
	
auto OnWarning(const Object & obj, Object::State state, const std::string & msg) -> void
{
	if (state == Object::State::WARNING)
	{
		// Logger logger {std::cout};
		// logger.Print(msg);
	}
}

int main(int argc, const char * argv[])
{
	PrintToFile to_file {"errors.txt"};

	Logger log_to_file {to_file::operator()};
	Logger log_to_screen {[](const std::string & msg)
	{
		std::cout << msg << '\n';
	}};

	Object::ObjectObserver warning_observer {OnWarning};
	Object::ObjectObserver error_observer {[&log_to_file](const Object & obj, Object::State state, const std::string & msg)
	{
		if (state == Object::State::ERROR)
		{
			log_to_file.Print(msg);
		}
	}};
	Object::ObjectObserver fatal_error_observer {[&](const Object & obj, Object::State state, const std::string & msg)
	{
		if (state == Object::State::FATAL_ERROR)
		{
			log_to_file.Print(msg);
			log_to_screen.Print(msg);
			OnWarning(obj, state, msg);
		}
	}};

	Object object;

	object.Attach(&warning_observer);
	object.Attach(&error_observer);
	object.Attach(&fatal_error_observer);

	object.Warning("WARNING: WHAT THE FUCK IS GOING ON?\n"s);
	object.Error("ERROR: YOU ARE DUMBASS\n"s);
	object.FatalError("FATAL ERROR: FUCK YOU\n"s);

	return 0;
}