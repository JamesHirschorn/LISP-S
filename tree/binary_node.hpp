/* Template class representing a node that can have (at most) two children. 
 *
 * Note that we use static polymorphism for better execution speed. */

#ifndef BINARY_NODE_HPP
#define BINARY_NODE_HPP

#include "Nary_node.hpp"

namespace tree {

template<typename DataType>
class binary_node;

//namespace detail {
//
//// forward declaration
//template<typename DataType>
//struct binary_node_pointer
//	: public node_pointer<binary_node<DataType>>
//{
//};
//
//}	// namespace detail

template<typename DataType>
class binary_node
	: public Nary_node<DataType, 2>
{
	typedef Nary_node<DataType, 2> base_type;
public:
	typedef typename base_type::data_type data_type;
/*	struct pointer_type
		: node_pointer<binary_node>
	{
	private:
		typedef node_pointer<binary_node> base_type;
	public:
		pointer_type(binary_node* p)
			: base_type(p)
		{
		}
		pointer_type(typename binary_node::base_type::pointer_type ptr)
			: base_type(ptr)
		{
//			_ptr = static_cast<std::shared_ptr<binary_node::base_type>>(ptr._ptr);
		}
	};*/
	//typedef detail::binary_node_pointer<DataType> pointer_type;
	typedef node_pointer<binary_node<DataType>> pointer_type;

	// default ctor
	binary_node() 
	{}
	// explicit conversion ctor
	binary_node(data_type data)
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

	// pointer to the root of the left branch
	pointer_type left() const
	{
		//base_type::pointer_type p = child<0>();
		
		//pointer_type pt = p;

		return static_pointer_cast<binary_node>(child<0>()); //static_cast<pointer_type>(child<0>());
	}
	// pointer to the root of the right branch
	pointer_type right() const
	{
		return static_pointer_cast<binary_node>(child<1>()); //static_cast<pointer_type>(child<1>());
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
	// e.g. for pointer_type p, we can do: data_type x = *p;
	//operator data_type() const
	//{
	//	return base_type::operator data_type();
	//}
	// non-const dereference operator,
	// e.g. for pointer_type p, we can do: *p = d; where typeof(d) is data_type
	//binary_node& operator=(data_type data)
	//{
	//	*static_cast<typename base_type::pointer_type>(this) = data;

	//	return *this;
	//}

	// conversion to Nary_node
	//operator Nary_node<DataType, 2>() const
	//{
	//	return *this;
	//}
};

//namespace detail {
//
//// forward declaration
//template<typename DataType>
//struct binary_node_pointer
//	: node_pointer<binary_node<DataType>>
//{
//};
//
//}	// namespace detail

}	// namespace tree

#endif