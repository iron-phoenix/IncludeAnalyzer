#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H

#include "include_finder.h"
#include "include_file.h"
#include "node.h"

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>

#include <boost/optional/optional.hpp>

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::find_if;
using std::for_each;
using std::find;

namespace fs = boost::filesystem;

template<typename IncludeGetter = IncludeFinder>
struct TreeBuilder {
	TreeBuilder(string const & home_path, vector<string> const & include_paths) :
		m_home_path(home_path) {
		for (string const & include_path : include_paths) {
			this->m_include_paths.emplace_back(include_path);
		}
	}

	TreeBuilder(TreeBuilder const &) = delete;
	TreeBuilder & operator=(TreeBuilder const &) = delete;

	NodePtr build_path_tree(vector<string> const & extensions) const {
		if (!fs::exists(m_home_path) && !fs::is_directory(m_home_path)) {
			throw std::runtime_error("Path not find: " + m_home_path.string());
		}

		NodePtr root = make_shared<Node>("", "", false);

		for_each(fs::recursive_directory_iterator(m_home_path), fs::recursive_directory_iterator(),
			[this, &extensions, &root](fs::directory_entry const & entry) {
			if (fs::is_regular_file(entry)) {
				if (find(extensions.begin(), extensions.end(), entry.path().extension()) != extensions.end()) {
					NodePtr new_node = this->build_file_tree(entry.path().string());
					root->add_child(new_node);
				}
			}
		});

		return root;
	}

	NodePtr build_file_tree(string const & file_path) const {
		fs::path full_path = fs::canonical(file_path);

		if (!fs::exists(full_path)) {
			throw std::runtime_error("File not find: " + full_path.string());
		}

		NodePtr root = make_shared<Node>(full_path.string(), full_path.filename().string(), fs::exists(full_path));

		build_file_tree(root, full_path);

		return root;
	}
private:
	fs::path m_home_path;
	vector<fs::path> m_include_paths;

	void build_file_tree(NodePtr parent, fs::path & path) const {
		fs::ifstream istream_to_analyse(path);
		IncludeGetter include_getter(istream_to_analyse);

		try{
			vector<IncludeFile> include_files = include_getter.find_includes();
			for (IncludeFile const & inf : include_files) {
				boost::optional<fs::path> full_path = get_path(inf.get_file_name(), inf.is_in_source());

				if (full_path) {
					if (!parent->is_in_hierarchy(full_path.get().string())) {
						NodePtr node = make_shared<Node>(full_path.get().string(), inf.get_file_name(), true);
						parent->add_child(node);

						build_file_tree(node, full_path.get());
					}
				}
				else {
					NodePtr node = make_shared<Node>("", inf.get_file_name(), false);
					parent->add_child(node);
				}
			}
		}
		catch (...) {
			throw std::runtime_error("Syntax error: " + path.string());
		}
	}

	boost::optional<fs::path> get_path(string const & include_name, bool is_in_home) const {
		if (is_in_home) {
			return find_file_in_directory(m_home_path, include_name);
		}
		else {
			boost::optional<fs::path> result;
			for (fs::path const & path_to_check : m_include_paths) {
				if (result = find_file_in_directory(path_to_check, include_name)) {
					break;
				}
			}
			return result;
		}
	}

	boost::optional<fs::path> find_file_in_directory(fs::path const & path_to_check, fs::path const & file_name) const {
		fs::path full_path = path_to_check / file_name;

		if (!fs::exists(full_path)) {
			return boost::optional<fs::path>();
		}

		fs::directory_iterator const end;
		fs::directory_iterator const it = find_if(fs::directory_iterator(full_path.parent_path()), end,
			[&full_path](fs::directory_entry const & entry) {
			return entry.path().filename() == full_path.filename();
		});

		return it == end ? boost::optional<fs::path>() : fs::canonical(it->path());
	}
};

#endif