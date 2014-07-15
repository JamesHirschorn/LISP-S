#include <iostream>

#include "parser/parser.hpp"
#include "tree/Nary_node.hpp"
#include "tree/binary_node.hpp"
#include "tree/tree.hpp"

int main(int argc, char** argv)
{
	using namespace tree;

	Nary_node<int, 2> node;

	bool has_left = node.has_child<0>();
	bool has_right = node.has_child<1>();

	node.set<0>(new Nary_node<int, 2>(10));
	has_left = node.has_child<0>();

	int value = *node.child<0>();
	*node.child<0>() = 5;
	value = *node.child<0>();

	//node.has_child<2>();

	binary_node<int> bNode;
	bNode = 12;

	has_left = bNode.has_left_branch();
	has_right = bNode.has_right_branch();
	bNode.set_left(new binary_node<int>(5));
	bNode.set_right(new binary_node<int>(6));
	int left_value = *bNode.left();
	int right_value = *bNode.right();

	*bNode.left() = 7;
	value = *bNode.left();

	binary_tree<int> bt;

	auto left_subtree = bt.left_subtree();

	parser::binary_tree_summing_parser<int> p(std::cin, '(', ')');

	for (int i = 1; p.input_available(); ++i)
	{
		std::cout << "Tree " << i << ":\n\n";

		try 
		{
			p.parse_tree();
		}
		catch (std::exception e)
		{
			std::cout << e.what();
			exit(EXIT_FAILURE);
		}
		std::cout << p.last_tree() << std::endl << std::endl;
	}
#if 0

#endif
}