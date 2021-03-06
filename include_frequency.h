#ifndef INCLUDE_FREQUENCY_H
#define INCLUDE_FREQUENCY_H

#include "node.h"

#include <unordered_map>
#include <utility>
#include <string>
#include <set>
#include <cstddef>

using std::unordered_map;
using std::pair;
using std::string;
using std::make_pair;
using std::set;

struct Comparator {
	bool operator()(pair<string, size_t> const & p1, pair<string, size_t> const & p2) {
		return p1.second == p2.second ? p1.first < p2.first : p1.second > p2.second;
	}
};

typedef unordered_map <string, size_t> string_number_map;
typedef unordered_map <string, string> string_string_map;
typedef set<pair<string, size_t>, Comparator> frequency_set;

struct IncludeFrequency {
	static frequency_set include_frequency(NodePtr const & node);

private:
	string_number_map m_frequency;
	string_string_map m_filenames;

	void count_frequency(NodePtr const & node);
};

#endif