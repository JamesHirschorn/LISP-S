/* Class for parsing the input for tree summing. 
 * 
 * We only parse binary trees for now, but this can obviously be extended to Nary-trees. */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <algorithm>
#include <cctype>
#include <functional>
#include <istream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

#include "tree/tree.hpp"

namespace parser {

/** parser class for summing binary trees */

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

	// whether there was input available for the last parse_tree calls (see below)
	bool input_was_available() const;

	// Parse one tree from the input stream.
	// An exception is thrown if the input does not contain a valid sum/tree pair.
	void parse_tree();

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

	static char const _error_message[]; 
};

/* member function definitions */

template<typename I>
binary_tree_summing_parser<I>::binary_tree_summing_parser(
	std::istream& is, 
	int left_delim, int right_delim,
	std::size_t integer_buffer_size) 
	:	_is(is), 
		_left_delim(left_delim), _right_delim(right_delim),
		// Note that the default deleter (when none is specified) does not work with arrays.
		_integer_buffer(new char[integer_buffer_size], std::default_delete<char[]>()),
		_integer_buffer_size(integer_buffer_size)
{
}

template<typename I>
bool
binary_tree_summing_parser<I>::input_was_available() const
{
	return _is.good();
}

template<typename I>
void
binary_tree_summing_parser<I>::parse_tree()
{
	_last_sum = getInteger<I>(
		_is, 
		_left_delim, 
		_integer_buffer.get(), _integer_buffer_size, 
		_error_message);

	_last_tree = getBinaryTree<I>(
		_is,
		_left_delim, _right_delim,
		_integer_buffer.get(), _integer_buffer_size,
		_error_message);
}

/* private member definitions */

template<typename I>
char const binary_tree_summing_parser<I>::_error_message[] = "Bad tree input";

/** parsing functions */

bool isnumeral(int c)
{
	return '0' <= c && c <= '9';
}

// Gets an integer from the stream, by reading up to the delimiter.
template<typename I>
typename binary_tree_summing_parser<I>::integer_type
getInteger(
	std::istream& input, 
	int const delim,
	char* integer_buffer,
	std::size_t const buffer_size,
	char const* error_message)
{
	// Read up to but not including the delimiter.
	input.get(integer_buffer, buffer_size - 1, delim);

	// The input should only include white-space, numerals and the minus sign.
	std::string str(integer_buffer);
	// flag indicated whether a non-whitespace character has been read yet.
	bool read_nw = false;	

	for (auto c : str)
	{
		if ( !isnumeral(c) && !std::isspace(c) && !(!read_nw && c == '-') )
			throw std::exception(error_message);
		read_nw |= !std::isspace(c);
	}

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
	int const left_delim, int const right_delim,
	char* integer_buffer, 
	std::size_t const buffer_size,
	char const* error_message)
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
		if (c == left_delim)
		{
			++count;
			if (read_left)
				saved_stream += c;
			else
				read_left = true;
		}
		else if (c == right_delim)
		{
			--count;
			if (count > 0)
				saved_stream += c;
		}
		else
		{
			// If the first non-whitespace character is not the left delimiter, 
			// then the input is invalid.
			if (!read_left && !std::isspace(c))
				throw std::exception(error_message);

			saved_stream += c;
		}
	}
	
	// Check if the delimiters are balanced.
	if (count != 0)
		throw std::exception(error_message);

	typedef typename binary_tree_summing_parser<I>::tree_type tree_type;
	tree_type t;

	// Check that the input does not only contain whitespace.
	if ( std::all_of(saved_stream.begin(), saved_stream.end(), std::isspace) ) 
	{
		return t;	// empty tree
	}

	// Parse saved_stream, which should contain the root node value 
	// and the left and right sub-trees.
	std::istringstream istr(saved_stream);

	binary_tree_summing_parser<I>::integer_type value = getInteger<I>(
		istr, left_delim, integer_buffer, buffer_size, error_message);
	t.set_root(new tree_type::node_type(value));

	tree_type left_tree = getBinaryTree<I>(istr, left_delim, right_delim,
		integer_buffer, buffer_size, error_message);
	if (!left_tree.is_empty())
		t.root() -> set_left(left_tree.root());

	tree_type right_tree = getBinaryTree<I>(istr, left_delim, right_delim,
		integer_buffer, buffer_size, error_message);
	if (!right_tree.is_empty())
		t.root() -> set_right(right_tree.root());

	// If there is still more non-whitespace after the right tree,
	// then the input is invalid.
	while (istr.get(c))
		if (!std::isspace(c))
			throw std::exception(error_message);

	return t;
}

}	// namespace parser

#endif