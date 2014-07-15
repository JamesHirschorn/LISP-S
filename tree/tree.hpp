/* Trees and functions on trees. */

#ifndef TREES_HPP
#define TREES_HPP

#include <ostream>

#include "Nary_node.hpp"
#include "binary_node.hpp"

namespace tree {

/** Trees */

/* NodeType must be compatible with Nary_node<T, N> for some N. */
template<typename NodeType>
class Nary_tree
{
public:
	typedef NodeType node_type;
	typedef typename node_type::pointer_type pointer_type;
	static int const arity = node_type::arity;

	// default ctor
	Nary_tree() 
	{}
	// explicit conversion ctor
	explicit Nary_tree(pointer_type node_ptr);

	// root inspector
	pointer_type root() const;
	// root setter
	void set_root(pointer_type node_ptr);
	// whether this is an empty tree
	bool is_empty() const;
private:
	pointer_type _root;
};

template<typename NodeType>
Nary_tree<NodeType>::Nary_tree(pointer_type node_ptr)
	: _root(node_ptr)
{
}

template<typename NodeType>
typename Nary_tree<NodeType>::pointer_type
Nary_tree<NodeType>::root() const
{
	return _root;
}

template<typename NodeType>
void Nary_tree<NodeType>::set_root(pointer_type node_ptr)
{
	_root = node_ptr;
}

template<typename NodeType>
bool Nary_tree<NodeType>::is_empty() const
{
	return _root == nullptr;
}

/* Binary tree */
template<typename DataType>
class binary_tree
	: public Nary_tree<binary_node<DataType>>
{
};

/** Functions on trees */

// Writes the tree contents to the output, one node at a time,
// according to the pre-order.
// One line per node of the form: node_value, child0_value child1_value ...
template<typename NodeType>
std::ostream& operator<<(std::ostream& os, Nary_tree<NodeType> const& T)
{
	typedef Nary_tree<NodeType> tree_type;

	if (T.is_empty())
		return os;

	typename tree_type::pointer_type root = T.root();

	os << *root << ", ";
	for (int i = 0; i < tree_type::arity; ++i)
	{
		if (root -> has_child(i))
			os << *(root -> child(i));
		else
			os << "null";
		os << " ";
	}

	os << std::endl;

	return os;
}

}	// namespace tree

#endif