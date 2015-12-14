#include "node.h"
#include "tree_builder.h"
#include "tree_printer.h"
#include "include_frequency.h"

#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

using std::vector;
using std::string;

int main(int argc, char ** argv) {
	string const usage = "Usage: analyzer <source path> [options]\nOptions: -I <include directory>";
	if (argc < 2) {
		std::cout << usage << std::endl;
		return 1;
	}

	string home_path(argv[1]);
	vector<string> include_directories;

	for (int i = 2; i != argc; i += 2) {
		if (strcmp(argv[i], "-I") == 0) {
			include_directories.emplace_back(argv[i + 1]);
		}
		else {
			std::cout << usage << std::endl;
			return 1;
		}
	}

	try {
		TreeBuilder<> tree_builder(home_path, include_directories);
		NodePtr root = tree_builder.build_path_tree({ ".cpp", ".h" });

		TreePrinter tree_printer(std::cout);
		tree_printer.print_tree(root);

		std::cout << std::endl;

		frequency_set frequency = IncludeFrequency::include_frequency(root);

		for (auto & f : frequency) {
			std::cout << f.first << " " << f.second << std::endl;
		}
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
		return 2;
	}
	
	return 0;
}