//
//  main.cpp
//  Patterns homeworks
//
//  Created by Denis Fedorov on 13.03.2023.

#include <iostream>
#include "print.h"

int main()
{
	using namespace output;

	std::ofstream fout {"datafile.txt"s, std::ios_base::out | std::ios_base::app};

	text text_sample("text example"s);
	html html_sample("html example"s);
	json json_sample("json example"s);

	send(fout, text_sample);
	send(fout, html_sample);
	send(fout, json_sample);
	send(std::cout, text_sample);
	send(std::cout, html_sample);
	send(std::cout, json_sample);

	return 0;
}