#include "node.h"

void Node::add_child(NodePtr & child) {
	child->parent = this;
	children.push_back(child);
}

bool Node::is_in_hierarchy(string const & path) const {
	Node const * current = parent;

	while (current != nullptr) {
		if (parent->path == path) {
			return true;
		}
		current = current->parent;
	}

	return false;
}

string const & Node::get_path() const {
	return path;
}

string const & Node::get_include_name() const {
	return include_name;
}

bool Node::is_file_exist() const {
	return is_exist;
}

vector<NodePtr> const & Node::get_children() const {
	return children;
}