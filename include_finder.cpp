#include "include_finder.h"

#include <cstring>
#include <stdexcept>

vector<IncludeFile> IncludeFinder::find_includes() {

	vector<IncludeFile> result;

	bool is_any_symbol = false;

	char peek = '\0';
	while (m_in.get(peek)) {
		if (isspace(peek)) {
			skip_whitespaces();
		}

		switch (peek) {
		case '/':
			process_comment();
			break;
		case '"':
			process_string();
			is_any_symbol = true;
			break;
		case '#':
			if (is_any_symbol) {
				throw std::runtime_error("Syntax error. Please check your source files.");
			}
			else {
				process_include(result);
			}
			break;
		case '\n':
			is_any_symbol = false;
			break;
		default:
			is_any_symbol = true;
			break;
		}
	}

	return result;
}

void IncludeFinder::process_comment() {
	char peek = '\0';
	m_in.get(peek);

	if (peek == '/') {
		while (m_in && peek != '\n') {
			m_in.get(peek);
		}
	}
	else if (peek == '*') {
		skip_multistring_comment();
	}
}

void IncludeFinder::process_string() {
	char peek = '\0';
	while (m_in.get(peek) && peek != '"') {
		if (m_in && peek == '\\' && m_in.peek() == '"') {
			m_in.get();
		}
	}
}

void IncludeFinder::process_include(vector<IncludeFile> & include_files) {
	char peek = '\0';

	skip_bad_symbols();

	char tmp[8] = { 0 };
	long long pos = m_in.tellg();

	for (int i = 0; i != 7; ++i) {
		if (!m_in) {
			break;
		}
		if (m_in.peek() == '\\') {
			m_in.get();
			if (m_in && m_in.get() == '\n') {
				--i;
				continue;
			}
			else {
				throw std::runtime_error("Syntax error. Please check your source files.");
			}
		}
		m_in.get(tmp[i]);
	}

	if (strcmp(tmp, "include") == 0) {
		skip_bad_symbols();

		m_in.get(peek);

		if (peek == '"' || peek == '<') {
			add_file(include_files, peek);
		}
		else {
			throw std::runtime_error("Syntax error. Please check your source files.");
		}
	}
	else {
		m_in.seekg(pos);
	}
}

void IncludeFinder::add_file(vector<IncludeFile> & include_files, char file_type) {
	char peek = '\0';

	if (file_type == '<') {
		file_type = '>';
	}

	string file_name = "";
	while (m_in.get(peek) && peek != file_type) {
		if (m_in && peek == '\\' && m_in.peek() == '\n') {
			m_in.get();
			continue;
		}
		file_name.push_back(peek);
	}
	include_files.emplace_back(file_name, file_type == '"');

	while (m_in.get(peek) && peek != '\n') {
		if (peek == '/') {
			if (m_in && m_in.peek() == '*') {
				skip_multistring_comment();
			}
		}
	}
}

void IncludeFinder::skip_multistring_comment() {
	char peek = '\0';

	while (m_in.get(peek)) {
		if (peek == '*') {
			if (m_in.peek() == '/') {
				m_in.get();
				break;
			}
		}
	}
}

void IncludeFinder::skip_whitespaces() {
	while (m_in && m_in.peek() != '\n' && isspace(m_in.peek())) {
		m_in.get();
	}
}

void IncludeFinder::skip_bad_symbols() {
	char peek = '\0';
	while (m_in.get(peek)) {
		if (isspace(peek)) {
			skip_whitespaces();
		}
		else if (peek == '\\' && m_in.peek() == '\n') {
			m_in.get();
		}
		else if (peek == '/' && m_in.peek() == '*') {
			m_in.get();
			skip_multistring_comment();
		}
		else {
			break;
		}
	}
	m_in.unget();
}