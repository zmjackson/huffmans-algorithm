#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#include <iostream>
#include <string>
#include <memory>

class huffman_node;

typedef std::shared_ptr<huffman_node> huff_ptr;

class huffman_node
{
	public:
	huff_ptr left;
	huff_ptr right;
	size_t value;
	
	huffman_node(const huffman_node& node);
	huffman_node();
	huffman_node(size_t value);
};

class huffman_leaf : public huffman_node
{	
	public:
	char symbol;	
	huffman_leaf(const char symbol, const size_t frequency);	
};

class huffman_node_compare
{
	public:
	bool operator()(const huff_ptr node1, const huff_ptr node2) const
	{
		return node1->value > node2->value;
	}
};

class huffman_tree {
	public:
		huff_ptr root;
		huffman_tree(const std::string &file_name);
		~huffman_tree();
		
		std::string get_character_code(char character) const;
		std::string encode(const std::string &file_name) const;
		std::string decode(const std::string &string_to_decode) const;	
};

#endif