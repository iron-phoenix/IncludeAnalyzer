#include "include_frequency.h"

frequency_set IncludeFrequency::include_frequency(NodePtr const & node) {
	IncludeFrequency include_frequency;
	include_frequency.count_frequency(node);

	frequency_set f_set;
	for (auto & path_to_filename : include_frequency.m_filenames) {
		string path = path_to_filename.first;
		string filename = path_to_filename.second;
		f_set.emplace(filename, include_frequency.m_frequency[path]);
	}
	return f_set;
}

void IncludeFrequency::count_frequency(NodePtr const & node) {
	if (!node->is_file_exist()) {
		if (node->get_include_name() != "") {
			m_frequency[node->get_include_name()] += 1;
			m_filenames[node->get_include_name()] = node->get_include_name();
		}
		else {
			for (NodePtr const & child : node->get_children()) {
				count_frequency(child);
				m_frequency[child->get_path()] -= 1;
				if (m_filenames.count(child->get_path()) == 0 ||
					(m_filenames.count(child->get_path()) != 0 &&
					child->get_include_name().size() > m_filenames[child->get_path()].size())) {
					m_filenames[child->get_path()] = child->get_include_name();
				}
			}
		}
		return;
	}

	m_frequency[node->get_path()] += 1;
	if (m_filenames.count(node->get_path()) == 0 ||
		(m_filenames.count(node->get_path()) != 0 &&
		node->get_include_name().size() > m_filenames[node->get_path()].size())) {
		m_filenames[node->get_path()] = node->get_include_name();
	}

	for (NodePtr const & child : node->get_children()) {
		count_frequency(child);
	}
}