/* Template class representing a node that can have (at most) N children. 
 *
 * The "mechanical" part of the program is delegated here. */

#ifndef NARYNODE_HPP
#define NARYNODE_HPP

#include <memory>

template<typename DataType, int N>
class Nary_node
{
public:
	typedef DataType* pointer_type;
}