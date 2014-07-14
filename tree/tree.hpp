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
	std::shared_ptr<node_type> _root;
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
	return _root.get();
}

template<typename NodeType>
void Nary_tree<NodeType>::set_root(pointer_type node_ptr)
{
	_root.reset(node_ptr);
}

template<typename NodeType>
bool Nary_tree<NodeType>::is_empty() const
{
	return _root.is_leaf();
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

	os << root << ", ";
	for (int i = 0; i < tree_type::arity; ++i)
		os << root -> child(i) << " ";

	os << std::endl;

	return os;
}

// specialization
template<typename DataType>
std::ostream& operator<<(std::ostream& os, binary_tree<DataType> const& T)
{
	Nary_tree<Nary_node<DataType, 2>> T_as_Nary;
	binary_node<DataType> no(*T.root());
	static_cast<Nary_node<DataType, 2>>(no);
	T_as_Nary.set_root(T.root());

	os << T_as_Nary;
	return os;
}

}	// namespace tree

#endif