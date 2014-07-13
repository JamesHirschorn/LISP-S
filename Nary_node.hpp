/* Template class representing a node that can have (at most) N children. 
 *
 * The "mechanical" part of the program is delegated here. */

#ifndef NARYNODE_HPP
#define NARYNODE_HPP

#include <memory>

namespace tree {

template<typename DataType, int N>
class Nary_node
{
public:
	typedef Nary_node* pointer_type;

	// ctors
	Nary_node() 
	{
		initialize();
	}
	Nary_node(DataType data)
		: _data(data)
	{
		initialize();
	}

	// whether the i-th child node exists
	template<int i>
	bool has_child() const;

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
	//DataType operator*() const
	//{
	//	return _data;
	//}
	//DataType& operator*()
	//{
	//	return _data;
	//}
private:
	DataType _data;
	std::shared_ptr<DataType> _child[N];
	bool _empty[N];
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
	assert_in_range<i>;

	return _child[i].get();
}

template<typename T, int N>
template<int i>
void Nary_node<T, N>::set(pointer_type node)
{
	_child[i].reset(node);
}

template<typename T, int N>
template<int i>
bool Nary_node<T, N>::has_child() const
{
	assert_in_range<i>;
	
	return child<i>() != nullptr;
}

/* private member definitions */

template<typename T, int N>
void Nary_node<T, N>::initialize()
{
	for (int i = 0; i < N; ++i)
		_exists[i] = false;
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