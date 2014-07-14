/* Template class representing a node that can have (at most) N children. 
 *
 * This is intended for use as a base class for specialized node types. 
 * The "mechanical" parts are delegated here. */

#ifndef NARY_NODE_HPP
#define NARY_NODE_HPP

#include <memory>

namespace tree {

template<typename DataType, int N>
class Nary_node
{
public:
	typedef Nary_node* pointer_type;

	// default ctor
	Nary_node() 
	{
		initialize();
	}
	// explicit conversion ctor
	explicit Nary_node(DataType data)
		: _data(data)
	{
		initialize();
	}

	// whether the i-th child node exists
	template<int i>
	bool has_child() const;
	// whether this is a leaf node
	bool is_leaf() const;

	// pointer to the i-th child node
	template<int i>
	pointer_type child() const;
	// set the i-th child node
	template<int i>
	void set(pointer_type child);

	// const dereference operator, 
	// e.g. for pointer_type p, we can do: DataType x = *p;
	operator DataType() const
	{
		return _data;
	}
	// non-const dereference operator,
	// e.g. for pointer_type p, we can do: *p = d; where typeof(d) is DataType
	Nary_node& operator=(DataType data)
	{
		_data = data;
		return *this;
	}
private:
	DataType _data;
	std::shared_ptr<Nary_node> _child[N];
	void initialize();
	// compile-time check that the index i is in range
	template<int i>
	struct assert_in_range;
};

template<typename T, int N>
template<int i>
typename Nary_node<T, N>::pointer_type 
Nary_node<T, N>::child() const
{
	static assert_in_range<i> a;

	return _child[i].get();
}

template<typename T, int N>
template<int i>
void Nary_node<T, N>::set(pointer_type node)
{
	static assert_in_range<i> a;

	_child[i].reset(node);
}

template<typename T, int N>
template<int i>
bool Nary_node<T, N>::has_child() const
{
	static assert_in_range<i> a;
	
	return child<i>() != nullptr;
}

template<typename T, int N>
bool Nary_node<T, N>::is_leaf() const
{	
	for (int i = 0; i < N; ++i)
		if (_child[i] != nullptr)
			return false;

	return true;
}

/* private member definitions */

// For future use.
template<typename T, int N>
void Nary_node<T, N>::initialize()
{
}

template<typename T, int N>
template<int i>
struct Nary_node<T, N>::assert_in_range
{
	// compile time assertion
	static_assert(i < N, "Child node index out of range.");
};

}	// namespace tree

#endif