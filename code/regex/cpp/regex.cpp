/*
 * regex.cpp -- Regex-Matcher der C++-Library testen
 *
 * (c) 2016 Hansruedi Patzen, HSR
 */

#include "regex.h"

#include <ostream>
#include <iomanip>
#include <regex>
#include <string>
#include <chrono>

namespace Regex {

void test(std::ostream & out, std::size_t const & numberOfRounds) {
	std::string regexString { };
	std::string searchString { };

	auto begin = std::chrono::high_resolution_clock::now();

	for (std::size_t i = 0; i < numberOfRounds; i++) {
		
		regexString += "a?";
		searchString += "a";
		std::string pattern { regexString + searchString };


		// perform matching
		auto beginonce = std::chrono::high_resolution_clock::now();
		std::regex regex { pattern };
		bool	matches = std::regex_match(searchString, regex);
		auto endonce = std::chrono::high_resolution_clock::now();

		// right aligned string
		out << std::right << std::setw(numberOfRounds);
		out << searchString;

		// left aligned match/nomatch string
		out << std::left << std::setw(15);
		out << (matches ? " matches " : " doesn't match ");

		// left aligned regular expression
		out << std::left << std::setw(3 * numberOfRounds) << pattern;


		// left aligned 
		out << std::right << std::setw(10);
		out << (std::chrono::duration_cast<std::chrono::nanoseconds>(endonce - beginonce).count() / 1000000) << " ms";

		out << std::endl;
	}

	auto end = std::chrono::high_resolution_clock::now();
	out << "Total runtime: ";
	out << std::setprecision(9);
	out << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / 1000000000.) << "s";
	out << std::endl;
}

} // namespace Regex
