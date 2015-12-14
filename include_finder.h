#ifndef INCLUDE_FINDER_H
#define INCLUDE_FINDER_H

#include "include_file.h"

#include <vector>
#include <string>
#include <istream>

using std::vector;
using std::string;
using std::istream;

struct IncludeFinder {
	IncludeFinder(istream & in) :
		in(in)
	{}

	IncludeFinder(IncludeFinder const &) = delete;
	IncludeFinder & operator=(IncludeFinder const &) = delete;

	vector<IncludeFile> find_includes();

private:
	istream & in;

	void process_comment();
	void process_string();
	void process_include(vector<IncludeFile> & include_files);
	void add_file(vector<IncludeFile> & include_files, char file_type);

	//-------------------------------------------------------------------------------

	void skip_multistring_comment();
	void skip_whitespaces();
	void skip_bad_symbols();
};

#endif