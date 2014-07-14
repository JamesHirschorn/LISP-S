/* Trees and functions on trees. */

#ifndef TREES_HPP
#define TREES_HPP

#include "Nary_node.hpp"
#include "binary_node.hpp"

namespace tree {

/* NodeType must be compatible with Nary_node<T, N> for some N. */
template<typename NodeType>
class tree
{
public:
	typedef NodeType node_type;

	// default ctor
	tree() 
	{}
	// explicit conversion ctor
	explicit tree(typename node_type::pointer_type node_ptr);

	// root inspector
	typename node_type::pointer_type root() const;
	// root setter
	void set_root(typename node_type::pointer_type node_ptr);
private:
	std::shared_ptr<node_type> _root;
};

template<typename NodeType>
tree<NodeType>::tree(typename node_type::pointer_type node_ptr)
	: _root(node_ptr)
{
}

template<typename NodeType>
typename tree<NodeType>::node_type::pointer_type
tree<NodeType>::root() const
{
	return _root.get();
}

template<typename NodeType>
void tree<NodeType>::set_root(typename node_type::pointer_type node_ptr)
{
	_root.reset(node_ptr);
}

/* Binary tree */
template<typename DataType>
class binary_tree
	: public tree<Nary_node<DataType, 2>>
{
};

/* Functions on trees */



}	// namespace tree

#endif