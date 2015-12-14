#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;

struct Node;
typedef shared_ptr<Node> NodePtr;

struct Node {
	Node(string const & path, string const & include_name, bool is_exist) :
		m_path(path),
		m_include_name(include_name),
		m_is_exist(is_exist),
		m_parent(nullptr)
	{}

	void add_child(NodePtr & child);

	bool is_in_hierarchy(string const & path) const;

	string const & get_path() const;
	string const & get_include_name() const;
	bool is_file_exist() const;
	vector<NodePtr> const & get_children() const;

private:
	string m_path;
	string m_include_name;
	bool m_is_exist;

	Node const * m_parent;
	vector<NodePtr> m_children;
};

#endif