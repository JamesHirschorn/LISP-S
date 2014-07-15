#include <iostream>

#include <parser/parser.hpp>
#include <tree/Nary_node.hpp>
#include <tree/binary_node.hpp>
#include <tree/tree.hpp>

int main(int argc, char** argv)
{
	using namespace tree;

	// Set up the parser to use the std input.
	parser::binary_tree_summing_parser<int> p(std::cin, '(', ')');

	// Read in one tree at a time until we use up the input.
	while (true)
	{
		// Try to parse the tree. An exception will be thrown
		// if the data is invalid.
		try 
		{
			p.parse_tree();
		}
		catch (std::exception const& e)
		{
		    std::cerr << e.what() << std::endl;
		    exit(EXIT_FAILURE);
		}

		// If input was not available for the last parse, then quit.
		if (p.input_was_available())
		{
			// Check if the tree that was just read in has a branch whose members
			// add up to sum.
			bool has_path_with_sum = has_branch_sum(p.last_tree(), p.last_sum());

			// Output the result
			std::cout << (has_path_with_sum ? "yes" : "no") << std::endl;
		}
		else
			break;
	}
}
