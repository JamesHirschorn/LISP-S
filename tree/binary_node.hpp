/* Template class representing a node that can have (at most) two children. 
 *
 * Note that we use static polymorphism for better execution speed. */

#ifndef BINARY_NODE_HPP
#define BINARY_NODE_HPP

#include <tree/Nary_node.hpp>

namespace tree {

template<typename DataType>
class binary_node
	: public Nary_node<DataType, 2>
{
	typedef Nary_node<DataType, 2> base_type;
public:
	typedef typename base_type::data_type		data_type;
	typedef node_pointer<binary_node<DataType>> pointer_type;

	// default ctor
	binary_node() 
	{}
	// explicit conversion ctor
	explicit binary_node(data_type const& data)
		: base_type(data)
	{}
	
	// has a left branch 
	bool has_left_branch() const
	{
	    return this -> template has_child<0>();
	}
	// has a right branch
	bool has_right_branch() const
	{
	    return this -> template has_child<1>();
	}

	// pointer to the root of the left branch (i.e. the left child)
	pointer_type left() const
	{
	    return static_pointer_cast<binary_node>(this -> template child<0>()); 
	}
	// pointer to the root of the right branch
	pointer_type right() const
	{
	    return static_pointer_cast<binary_node>(this -> template child<1>()); 
	}
	// set the left node
	void set_left(pointer_type node)
	{
	    this -> template set<0>(node); 
	}
	// set the right node
	void set_right(pointer_type node)
	{
	    this -> template set<1>(node); 
	}

	// Note: default assignment operator hides base_type::operator=.
	binary_node& operator=(data_type data)
	{
		base_type::operator=(data);
		return *this;
	}

	/* hide the base members with return type base_type::pointer_type */
	
	pointer_type child(int i) const
	{
		return static_pointer_cast<binary_node>(base_type::child(i));
	}
};

}	// namespace tree

#endif
