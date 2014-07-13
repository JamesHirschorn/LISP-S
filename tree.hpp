#include <memory>

/* Represents a node that can have (at most) N children. */
template<typename DataType, int N>
class Nary_node
{
public:
	typedef std::shared_ptr<DataType> pointer_type;

	// has a left branch (i.e. child node)
	template<int i>
	bool has_child() const;
	// has a right branch
	bool has_right_branch() const;
	// is a leaf
	bool is_leaf() const
	{
		return ( !has_left_branch() ) && ( !has_right_branch() );
	}
private:
	pointer_type[N] _child;
};

template<typename DataType>
class BinaryNode
{
public:
	typedef std::shared_ptr<DataType> pointer_type;

	// has a left branch (i.e. child node)
	bool has_left_branch() const;
	// has a right branch
	bool has_right_branch() const;
	// is a leaf
	bool is_leaf() const
	{
		return ( !has_left_branch() ) && ( !has_right_branch() );
	}
private:
	pointer_type left;
	pointer_type right;
};

template<typename T>
BinaryNode::has_left_branch()