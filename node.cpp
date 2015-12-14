#include "node.h"

void Node::add_child(NodePtr & child) {
	child->m_parent = this;
	m_children.push_back(child);
}

bool Node::is_in_hierarchy(string const & path) const {
	Node const * current = m_parent;

	while (current != nullptr) {
		if (m_parent->m_path == path) {
			return true;
		}
		current = current->m_parent;
	}

	return false;
}

string const & Node::get_path() const {
	return m_path;
}

string const & Node::get_include_name() const {
	return m_include_name;
}

bool Node::is_file_exist() const {
	return m_is_exist;
}

vector<NodePtr> const & Node::get_children() const {
	return m_children;
}