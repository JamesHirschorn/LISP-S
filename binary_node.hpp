/* Template class representing a node that can have (at most) two children. 
 *
 * Note that we use static polymorphism for better execution speed. */

#ifndef BINARY_NODE_HPP
#define BINARY_NODE_HPP

#include "Nary_node.hpp"

namespace tree {

template<typename DataType>
class binary_node
	: private Nary_node<DataType, 2>
{
	typedef Nary_node<DataType, 2> base_type;
public:
	typedef binary_node* pointer_type;

	// default ctor
	binary_node() 
	{}
	// explicit conversion ctor
	binary_node(DataType data)
		: base_type(data)
	{}
	
	// has a left branch 
	bool has_left_branch() const
	{
		return has_child<0>();
	}
	// has a right branch
	bool has_right_branch() const
	{
		return has_child<1>();
	}
	bool is_leaf() const
	{
		return is_leaf();
	}

	// pointer to the root of the left branch
	pointer_type left() const
	{
		return static_cast<pointer_type>(child<0>());
	}
	// pointer to the root of the right branch
	pointer_type right() const
	{
		return static_cast<pointer_type>(child<1>());
	}
	// set the left node
	void set_left(pointer_type node)
	{
		set<0>(node); 
	}
	// set the right node
	void set_right(pointer_type node)
	{
		set<1>(node);
	}

	// const dereference operator, 
	// e.g. for pointer_type p, we can do: DataType x = *p;
	operator DataType() const
	{
		return base_type::operator DataType();
	}
	// non-const dereference operator,
	// e.g. for pointer_type p, we can do: *p = d; where typeof(d) is DataType
	binary_node& operator=(DataType data)
	{
		*static_cast<typename base_type::pointer_type>(this) = data;

		return *this;
	}
};

}	// namespace tree

#endif