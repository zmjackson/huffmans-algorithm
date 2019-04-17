#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#include <iostream>
#include <memory>

class huffman_node;

typedef std::unique_ptr<huffman_node> huff_ptr;

class huffman_node
{
	public:
	huff_ptr left;
	huff_ptr right;
	size_t value;

	protected:	
	huffman_node();
	huffman_node(size_t value);
};

class huffman_head : public huffman_node
{	
	public:	
	huffman_head(huffman_node& left, huffman_node& right);	
};

class huffman_leaf : public huffman_node
{	
	public:
	char symbol;	
	huffman_leaf(const char symbol, const size_t frequency) ;	
};

class huffman_tree {
	public:
		huffman_tree(const std::string &file_name);
		~huffman_tree();
		
		std::string get_character_code(char character) const;
		std::string encode(const std::string &file_name) const;
		std::string decode(const std::string &string_to_decode) const;	
};

#endif