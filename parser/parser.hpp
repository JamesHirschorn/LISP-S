/* Class for parsing the input for tree summing. */

#include <istream>
#include <memory>

#include "tree/tree.hpp"

namespace parser {

template<typename IntType>
class binary_tree_summing_parser
{
public:
	typedef IntType integer_type;
	/* ctor */
	// is - the input stream to be parsed
	// integer_buffer_size - maximum number of characters to read an integer
	// tree_buffer_size - maximum number of characters to read a tree
	binary_tree_summing_parser(std::istream& is, std::size_t integer_buffer_size = 80, std::size_t tree_buffer_size = 10000);

	integer_type getInteger(int delim);
	tree::binary_tree<integer_type> getTree(int left_delim, int right_delim);
private:
	std::istream& _is;
	const std::size_t _integer_buffer_size;
	const std::size_t _tree_buffer_size;
	std::shared_ptr<char> _integer_buffer;
	std::shared_ptr<char> _tree_buffer;
};

binary_tree_summing_parser::binary_tree_summing_parser(
	std::istream& is, 
	std::size_t integer_buffer_size, 
	std::size_t tree_buffer_size) : 
		_is(is), 
		_integer_buffer_size(integer_buffer_size), 
		_tree_buffer_size(tree_buffer_size),
		// Note that the default deleter does not work with arrays.
		_integer_buffer(new char[_integer_buffer_size], std::default_delete<char[]>()),
		_tree_buffer(new char[_tree_buffer_size], std::default_delete<char[]>())
{
}

long long binary_tree_summing_parser::getInteger(int delim)
{
	_is.get(_integer_buffer.get(), _integer_buffer_size, delim);
   
	// convert the buffer to a long long
	std::istringstream istr(_integer_buffer.get());

	long long result;
	istr >> result;
	return result;
}

}	// namespace parser