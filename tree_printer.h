#ifndef TREE_PRINTER_H
#define TREE_PRINTER_H

#include "node.h"

#include <ostream>
#include <vector>

using std::ostream;
using std::vector;

struct TreePrinter {
	TreePrinter(ostream & out) :
		m_out(out),
		m_level(0)
	{}

	TreePrinter(TreePrinter const &) = delete;
	TreePrinter & operator=(TreePrinter const &) = delete;

	void print_tree(NodePtr const & node);

private:
	ostream & m_out;
	size_t m_level;
};

#endif