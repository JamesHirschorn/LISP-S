/* Class for parsing the input for tree summing. */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <istream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

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

template<typename I>
binary_tree_summing_parser<I>::binary_tree_summing_parser(
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

template<typename I>
typename binary_tree_summing_parser<I>::integer_type 
binary_tree_summing_parser<I>::getInteger(int delim)
{
	// read up to but not including the delimiter
	_is.get(_integer_buffer.get(), _integer_buffer_size, delim);
   
	// convert the buffer to a long long
	std::istringstream istr(_integer_buffer.get());

	integer_type result;
	istr >> result;
	return result;
}

template<typename I>
tree::binary_tree<integer_type> 
binary_tree_summing_parser<I>::getTree(std::istream& tree_stream, int left_delim, int right_delim)
{
	char error_message[] = "Bad tree input";

	char c;
	std::string saved_stream;

	// keeps track of the balance between left and right delimiters (0 means they are matched)
	long long count = 0;

	bool read_left = false;	// whether the left delimiter has been seen at least once 
	bool valid = false;		// whether tree is valid

	// Discard the surrounding left_delim and right_delim,
	// and save the middle stuff to saved_stream.
	while (count >= 0 && (!read_left || count > 0) && tree_stream.get(c))
	{
		switch (c)
		{
		case left_delim:
			++count;
			if (read_left)
				saved_stream += c;
			else
				read_left = true;
			break;
		case right_delim:
			--count;
			if (count > 0)
				saved_stream += c;
			break;
		default:
			saved_stream += c;
			break;
		}
	}
	
	// Check if the tree input is valid.
	if (!read_left || count != 0)
		throw std::exception(error_message);

	// We have parsed the empty tree.
	if (saved_stream.is_empty())
		return tree::binary_tree<I>();

	binary_tree<integer_type> left_tree = getTree(saved_stream, left_delim, right_delim);
	binary_tree<integer_type> 
}

}	// namespace parser

#endif