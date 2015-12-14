#ifndef INCLUDE_FILE_H
#define INCLUDE_FILE_H

#include <string>

using std::string;

struct IncludeFile {
	IncludeFile(string const & file_name, bool in_source) :
		file_name(file_name),
		in_source(in_source)
	{}

	string const & get_file_name() const {
		return file_name;
	}

	bool is_in_source() const {
		return in_source;
	}

private:
	string file_name;
	bool in_source;
};

#endif