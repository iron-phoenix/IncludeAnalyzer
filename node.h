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
		path(path),
		include_name(include_name),
		is_exist(is_exist),
		parent(nullptr)
	{}

	void add_child(NodePtr & child);

	bool is_in_hierarchy(string const & path) const;

	string const & get_path() const;
	string const & get_include_name() const;
	bool is_file_exist() const;
	vector<NodePtr> const & get_children() const;

private:
	string path;
	string include_name;
	bool is_exist;

	Node const * parent;
	vector<NodePtr> children;
};

#endif