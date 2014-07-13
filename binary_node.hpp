/* Template class representing a node that can have (at most) two children. 
 *
 * Note that we use static polymorphism for better execution speed. */

#ifndef BINARY_NODE_HPP
#define BINARY_NODE_HPP

#include "Nary_node.hpp"

namespace tree {

template<typename DataType>
class binary_node
{
	typedef Nary_node<DataType, 2> compose_t;
public:
	typedef binary_node* pointer_type;

	// default ctor
	binary_node() 
	{}
	// explicit conversion ctor
	binary_node(DataType data) : _node(data)
	{}
	
	// has a left branch 
	bool has_left_branch() const
	{
		return _node.has_child<0>();
	}
	// has a right branch
	bool has_right_branch() const
	{
		return _node.has_child<1>();
	}
	// whether this is a leaf node
	bool is_leaf() const
	{
		return _node.is_leaf();
	}

	// pointer to the root of the left branch
	pointer_type left() const
	{
		return reinterpret_cast<pointer_type>(_node.child<0>());
	}
	// pointer to the root of the right branch
	pointer_type right() const
	{
		return reinterpret_cast<pointer_type>(_node.child<1>());
	}
	// set the left node
	void set_left(pointer_type node)
	{
		_node.set<0>(reinterpret_cast<typename compose_t::pointer_type>(node));
	}
	// set the right node
	void set_right(pointer_type node)
	{
		_node.set<1>(reinterpret_cast<typename compose_t::pointer_type>(node));
	}

	// const dereference operator, 
	// e.g. for pointer_type p, we can do: DataType x = *p;
	operator DataType() const
	{
		return _node;
	}
	// non-const dereference operator,
	// e.g. for pointer_type p, we can do: *p = d; where typeof(d) is DataType
	binary_node& operator=(DataType data)
	{
		_node = data;
		return *this;
	}

private:
	// compose with Nary_name
	compose_t _node;
};

}	// namespace tree

#endif