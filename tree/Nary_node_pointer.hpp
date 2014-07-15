/* Pointer class for Nary-nodes.
 *
 * This is designed for use with static polymorphism (for execution speed).
 */

#ifndef NARY_NODE_POINTER_HPP
#define NARY_NODE_POINTER_HPP

#include <memory>

namespace tree {

/** represents a pointer to an Nary-node */

template<typename NodeType>
struct node_pointer
{
	typedef NodeType node_type;

	node_pointer() {}
	// Allows for implicit conversion from Nary_node*.
	// This form is only intended to be used for RAII.
	// e.g. node_pointer p(new Nary_node(10));
	node_pointer(node_type* p);
	
	// conversion ctor
	// O* must be implicitly convertible to node_type*
	template<typename O>
	node_pointer(node_pointer<O> const& ptr);

	// Acquire a new resource.
	void reset(node_type* p);

	// comparison operators
	bool operator==(node_pointer other) const;
	bool operator!=(node_pointer other) const;

	// dereference operators
	typename node_type operator*() const;
	typename node_type& operator*();

	// member operators 
	node_type const* operator->() const;
	node_type* operator->();
private:
	std::shared_ptr<node_type> _ptr;
	// needed for the implementation of the conversion ctor
	template<typename O>
	friend struct node_pointer;
	template<typename N, typename O>
	friend node_pointer<N> static_pointer_cast(node_pointer<O> const&);
};

/* member definitions */

template<typename N>
node_pointer<N>::node_pointer(N* p)
	: _ptr(p)
{
}

template<typename N>
template<typename O>
node_pointer<N>::node_pointer(node_pointer<O> const& ptr)
	: _ptr(ptr._ptr)
{
}

template<typename N>
void
node_pointer<N>::reset(N* p)
{
	_ptr.reset(p);
}

template<typename N>
bool 
node_pointer<N>::operator==(node_pointer other) const
{
	return _ptr == other._ptr;
}

template<typename N>
bool 
node_pointer<N>::operator!=(node_pointer other) const
{
	return !(*this == other);
}

template<typename N>
typename N //::data_type 
node_pointer<N>::operator*() const
{
	return *_ptr.get();
}

template<typename N>
typename N& 
node_pointer<N>::operator*()
{
	return *_ptr.get();
}

template<typename N>
N const* 
node_pointer<N>::operator->() const
{
	return _ptr.get();
}

template<typename N>
N* 
node_pointer<N>::operator->()
{
	return _ptr.get();
}

/** pointer function definitions */

/* static cast */
// O* must be convertible to N* using static_cast
template<typename N, typename O>
node_pointer<N> 
static_pointer_cast(node_pointer<O> const& np)
{
	node_pointer<N> result;

	result._ptr = std::static_pointer_cast<node_pointer<N>::node_type>(np._ptr);

	return result;
}

}	// namespace tree

#endif