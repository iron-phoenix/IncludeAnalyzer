#include "tree_printer.h"

void TreePrinter::print_tree(NodePtr const & node) {
	if (node->get_include_name() == "") {
		for (NodePtr const & next_node : node->get_children()) {
			print_tree(next_node);
		}
		return;
	}

	for (size_t i = 0; i != m_level; ++i) {
		m_out << "..";
	}

	m_out << node->get_include_name();

	if (!node->is_file_exist()) {
		m_out << " (!)";
	}

	m_out << '\n';

	++m_level;
	for (NodePtr const & next_node : node->get_children()) {
		print_tree(next_node);
	}
	--m_level;
}