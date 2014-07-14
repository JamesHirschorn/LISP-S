#include <sstream>

#include "parser.hpp"

namespace parser {

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