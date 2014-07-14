/* Trees and functions on trees. */

#ifndef TREES_HPP
#define TREES_HPP

#include "Nary_node.hpp"
#include "binary_node.hpp"

namespace tree {

/* N-ary tree with N fixed */
template<typename DataType, int N>
class Nary_tree
{
public:
	typedef Nary_node<DataType, N> node_type;

	// default ctor
	Nary_tree() 
	{}
	// explicit conversion ctor
	explicit Nary_tree(typename node_type::pointer_type node_ptr);

	// root inspector
	typename node_type::pointer_type root() const;
	// root setter
	void set_root(typename node_type::pointer_type node_ptr);
private:
	std::shared_ptr<node_type> _root;
};

template<typename T, int N>
Nary_tree<T, N>::Nary_tree(typename node_type::pointer_type node_ptr)
	: _root(node_ptr)
{
}

template<typename T, int N>
typename Nary_tree<T, N>::node_type::pointer_type
Nary_tree<T, N>::root() const
{
	return _root.get();
}

template<typename T, int N>
void Nary_tree<T, N>::set_root(typename node_type::pointer_type node_ptr)
{
	_root.reset(node_ptr);
}

/* Binary tree */
template<typename DataType>
class binary_tree
	: public Nary_tree<DataType, 2>
{
};

}	// namespace tree

#endif