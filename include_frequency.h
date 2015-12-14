#ifndef INCLUDE_FREQUENCY_H
#define INCLUDE_FREQUENCY_H

#include "node.h"

#include <unordered_map>
#include <utility>
#include <string>
#include <set>
#include <functional>

using std::unordered_map;
using std::pair;
using std::string;
using std::make_pair;
using std::set;
using std::greater;

typedef unordered_map <string, size_t> string_number_map;
typedef unordered_map <string, string> string_string_map;
typedef set<pair<size_t, string>, greater<pair<size_t, string>>> frequency_set;

struct IncludeFrequency {
	static frequency_set include_frequency(NodePtr const & node);

private:
	string_number_map frequency;
	string_string_map filenames;

	void count_frequency(NodePtr const & node);
};

#endif