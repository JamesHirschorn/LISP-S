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

	has_left = bNode.has_left_branch();
	has_right = bNode.has_right_branch();
	bNode.set_left(new binary_node<int>(5));
	bNode.set_right(new binary_node<int>(6));
	int left_value = *bNode.left();
	int right_value = *bNode.right();

	*bNode.left() = 7;
	value = *bNode.left();

	binary_tree<int> bt;

	parser::binary_tree_summing_parser p(std::cin);
	std::cout << p.getInteger('\n') << std::endl;
}