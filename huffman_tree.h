#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#include <iostream>
#include <string>
#include <memory>

class node; 
class huffman_node;

typedef std::shared_ptr<node> node_ptr;
typedef std::shared_ptr<huffman_node> huff_ptr;


class node
{
	public:
	size_t value;

	node();
	node(size_t value);
	virtual ~node() = default;
};

class huffman_node : public node
{
	public:
	node_ptr left;
	node_ptr right;	
	
	huffman_node();	
	huffman_node(size_t value);
};

class huffman_leaf : public node
{	
	public:
	char symbol;	
	huffman_leaf(const char symbol, const size_t frequency);	
};

class node_compare
{
	public:
	bool operator()(const node_ptr node1, const node_ptr node2) const
	{
		return node1->value > node2->value;
	}
};

class huffman_tree {
	public:
		node_ptr root;
		huffman_tree(const std::string &file_name);
		~huffman_tree();
		
		std::string get_character_code(char character) const;
		std::string encode(const std::string &file_name) const;
		std::string decode(const std::string &string_to_decode) const;	
};

#endif