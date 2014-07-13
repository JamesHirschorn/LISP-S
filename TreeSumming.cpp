#include "Nary_node.hpp"

int main(int argc, char** argv)
{
	using namespace tree;

	Nary_node<int, 2> node;

	bool has_left = node.has_child<0>();
	bool has_right = node.has_child<1>();

	node.set<0>(new Nary_node<int, 2>(10));

	int value = *node.child<0>();
}