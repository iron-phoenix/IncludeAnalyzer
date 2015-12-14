#ifndef INCLUDE_FILE_H
#define INCLUDE_FILE_H

#include <string>

using std::string;

struct IncludeFile {
	IncludeFile(string const & file_name, bool in_source) :
		m_file_name(file_name),
		m_in_source(in_source)
	{}

	string const & get_file_name() const {
		return m_file_name;
	}

	bool is_in_source() const {
		return m_in_source;
	}

private:
	string m_file_name;
	bool m_in_source;
};

#endif