#include "include_frequency.h"

frequency_set IncludeFrequency::include_frequency(NodePtr const & node) {
	IncludeFrequency include_frequency;
	include_frequency.count_frequency(node);

	frequency_set f_set;
	for (auto & path_to_filename : include_frequency.filenames) {
		string path = path_to_filename.first;
		string filename = path_to_filename.second;
		f_set.emplace(include_frequency.frequency[path], filename);
	}
	return f_set;
}

void IncludeFrequency::count_frequency(NodePtr const & node) {
	if (!node->is_file_exist()) {
		if (node->get_include_name() != "") {
			frequency[node->get_include_name()] += 1;
			filenames[node->get_include_name()] = node->get_include_name();
		}
		else {
			for (NodePtr const & child : node->get_children()) {
				count_frequency(child);
				frequency[child->get_path()] -= 1;
				filenames[child->get_path()] = child->get_include_name();
			}
		}
		return;
	}
	frequency[node->get_path()] += 1;
	filenames[node->get_path()] = node->get_include_name();
	for (NodePtr const & child : node->get_children()) {
		count_frequency(child);
	}
}