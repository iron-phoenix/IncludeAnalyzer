#ifndef TREE_PRINTER_H
#define TREE_PRINTER_H

#include "node.h"

#include <ostream>
#include <vector>

using std::ostream;
using std::vector;

struct TreePrinter {
	TreePrinter(ostream & out) :
		out(out),
		level(0)
	{}

	void print_tree(NodePtr const & node);

private:
	ostream & out;
	size_t level;
};

#endif