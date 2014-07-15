/* Trees and functions on trees. */

#ifndef TREES_HPP
#define TREES_HPP

#include <ostream>

#include <tree/Nary_node.hpp>
#include <tree/binary_node.hpp>

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
	explicit Nary_tree(pointer_type const& node_ptr);

	// root inspector
	pointer_type root() const;
	// root setter
	void set_root(pointer_type const& node_ptr);
	// whether this is an empty tree
	bool is_empty() const;
private:
	pointer_type _root;
};

/* member definitions */

template<typename NodeType>
Nary_tree<NodeType>::Nary_tree(pointer_type const& node_ptr)
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
void Nary_tree<NodeType>::set_root(pointer_type const& node_ptr)
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
public:
	// Returns the left-subtree, or else an empty tree if there is none.
	binary_tree left_subtree() const;
	// Returns the right-subtree, or else an empty tree if there is none.
	binary_tree right_subtree() const;
};

/* member definitions */

template<typename DataType>
binary_tree<DataType> 
binary_tree<DataType>::left_subtree() const
{
	binary_tree t;

	if (!this -> is_empty() && this -> root() -> has_left_branch())
		t.set_root(this -> root() -> left());

	return t;
}

template<typename DataType>
binary_tree<DataType> 
binary_tree<DataType>::right_subtree() const
{
	binary_tree t;

	if (!this -> is_empty() && this -> root() -> has_right_branch())
		t.set_root(this -> root() -> right());

	return t;
}

/** Functions on trees */

// Whether the tree T has a branch, i.e. a path starting at the root and
// ending at a leaf node, whose elements add up to sum.
// Thus this is always false for an empty tree.
// Note data_type must support the + operator.
template<typename NodeType>
bool
has_branch_sum(Nary_tree<NodeType> const& T, typename NodeType::data_type sum)
{
	typedef Nary_tree<NodeType> tree_type;

	// The implementation is by the obvious recursion.

	if (T.is_empty())
		return false;
	
	typename tree_type::pointer_type root = T.root();

	// branch of length 1
	if (root -> is_leaf())
		return *root == sum;

	for (int i = 0; i < tree_type::arity; ++i)
	{
		if (root -> has_child(i))
		{
			// the i-th subtree
			tree_type subtree( static_pointer_cast<NodeType>(root -> child(i)) );
			if (has_branch_sum(subtree, sum - *root))
				return true;
		}
	}

	return false;	// no suitable branch was found
}

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

	for (int i = 0; i < tree_type::arity; ++i)
	{
		if (root -> has_child(i))
		{
			tree_type subtree(static_pointer_cast<NodeType>(root -> child(i)));
			os << std::endl << subtree;
		}
	}

	return os;
}

}	// namespace tree

#endif
