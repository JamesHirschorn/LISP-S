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
	typedef tree::binary_tree<IntType> tree_type;
	/* ctor */
	// is - the input stream to be parsed
	// left_delim - left delimiter, e.g. '('
	// right_delim - right delimiter, e.g. ')'
	// integer_buffer_size - maximum number of characters to read an integer (default is 80)
	binary_tree_summing_parser(std::istream& is, int left_delim, int right_delim,
		std::size_t integer_buffer_size = 80);

	// whether there is any input on the input stream
	bool input_available() const;

	// Parse one tree from the input stream.
	// An exception is thrown if the input does not contain a valid sum/tree pair.
	tree_type parse_tree();

	/* inspectors */
	// last sum read from input
	integer_type last_sum() const { return _last_sum; }
	// last tree read from input
	tree_type last_tree() const { return _last_tree; }
private:
	std::istream& _is;
	int const _left_delim, _right_delim;
	std::shared_ptr<char> _integer_buffer;
	std::size_t const _integer_buffer_size;

	integer_type _last_sum;	// last sum read in
	tree_type _last_tree;	// last tree read in


	integer_type getInteger(int delim);
	tree_type getSubTrees(std::istream& input, int left_delim, int right_delim);
	tree_type parse(std::istream& input, int left_delim, int right_delim);

	static char const _error_message[] = "Bad tree input";
};

/* member function definitions */

template<typename I>
binary_tree_summing_parser<I>::binary_tree_summing_parser(
	std::istream& is, 
	int left_delim, int right delim,
	std::size_t integer_buffer_size, 
	std::size_t tree_buffer_size) : 
		_is(is), 
		_left_delim(left_delim), _right_delim(right_delim),
		// Note that the default deleter does not work with arrays.
		_integer_buffer(new char[_integer_buffer_size], std::default_delete<char[]>()),
		_integer_buffer_size(integer_buffer_size)
{
}

template<typename I>
bool
binary_tree_summing_parser<I>::input_available() const
{
	return _is.is_good();
}

template<typename I>
typename binary_tree_summing_parser<I>::tree_type
binary_tree_summing_parser<I>::parse_tree()
{
	_last_sum = getInteger(
		_is, 
		_left_delim, 
		_integer_buffer, _integer_buffer_size, 
		_error_message);

	_last_tree = getBinaryTree(
		_is,
		_left_delim, _right_delim,
		_integer_buffer, _integer_buffer_size,
		_error_message);
}

/* parsing functions */

// Gets an integer from the stream, by reading up to the delimiter.
template<typename I>
typename binary_tree_summing_parser<I>::integer_type 
binary_tree_summing_parser<I>::getInteger(
	std::istream& input, 
	int delim,
	char* integer_buffer,
	std::size_t buffer_size,
	char* error_message)
{
	// Read up to but not including the delimiter.
	input.get(integer_buffer, buffer_size, delim);

	// Make sure the input stream is still in a good state.
	if (!input.is_good())
		throw std::exception(error_message);

	// Convert the buffer to a long long.
	std::istringstream istr(integer_buffer);

	typename binary_tree_summing_parser<I>::integer_type result;
	istr >> result;
	return result;
}

// Reads a binary tree from the input.
template<typename I>
typename binary_tree_summing_parser<I>::tree_type
getBinaryTree(
	std::istream& tree_stream, 
	int left_delim, int right_delim,
	char* integer_buffer, 
	std::size_t buffer_size,
	char* error_message)
{
	char c;
	std::string saved_stream;

	// keeps track of the balance between left and right delimiters (0 means they are matched)
	long long count = 0;

	bool read_left = false;	// whether the left delimiter has been seen at least once 

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

	binary_tree<I> tree;

	// We have parsed the empty tree.
	if (saved_stream.is_empty())
		return tree;

	// Parse saved_stream, which should contain the root node value 
	// and the left and right sub-trees.
	std::istringstream istr(saved_stream);

	I value = getInteger(istr, left_delim);
	tree.set_root(new binary_tree<I>::node_type(value));

	binary_tree<integer_type> left_tree = getTree(istr, left_delim, right_delim);
	if (!left_tree.is_empty())
		tree.root() -> set_left(left_tree.root());
	binary_tree<integer_type> right_tree = getTree(istr, left_delim, right_delim);
	if (!right_tree.is_empty())
		tree.root() -> set_right(right_tree.root());

	return tree;
}

template<typename I>
typename binary_tree_summing_parser<I>::tree_type
binary_tree_summing_parser<I>::parse(std::istream& tree_stream, int left_delim, int right_delim)
{
	I value = getInteger(tree_stream, left_delim);
}

}	// namespace parser

#endif