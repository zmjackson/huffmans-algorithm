#include "huffman_tree.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>

huffman_node::huffman_node(size_t value)
	: value(value), left(nullptr), right(nullptr) {}

huffman_node::huffman_node(const huffman_node& node)	
{

}

huffman_leaf::huffman_leaf(const char symbol, const size_t frequency) 
	: symbol(symbol), huffman_node(frequency) {}

/*
Preconditions: file_name is the name of (and possibly path to) a text file
Postconditions: Reads the contents of file_name and constructs a
				huffman tree based on the character frequencies of the file contents
*/
huffman_tree::huffman_tree(const std::string &file_name){

	std::unordered_map<char, size_t> char_map;

	std::ifstream input_text(file_name);
	char curr_char;

	while(input_text.get(curr_char))
	{
		char_map[curr_char] += 1;
	}

	input_text.close();

	std::priority_queue<huff_ptr> node_queue;

	for (auto& char_data : char_map)
	{
		node_queue.push(std::make_unique<huffman_leaf>(char_data.first, char_data.second));
	}

	while (node_queue.size() > 1)
	{
		huff_ptr first = std::move(node_queue.top);
		node_queue.pop();
		huff_ptr second = std::move(node_queue.top);
		node_queue.pop();
		huff_ptr new_node = std::make_unique<huffman_node>(first->value + second->value);
		new_node->left = std::move(first);
		new_node->right = std::move(second);
		node_queue.push(std::move(new_node));	
	}

	root = std::move(node_queue.top);
}

huffman_tree::~huffman_tree(){

}

/*
Preconditions: Character is a character with an ASCII value
				between 0 and 127 (inclusive).
Postconditions: Returns the Huffman code for character if character is in the tree
				and an empty string otherwise.
*/
std::string huffman_tree::get_character_code(char character) const {
	return "";
}

/*
Preconditions: file_name is the name of (and possibly path to) a text file
Postconditions: Returns the Huffman encoding for the contents of file_name
				if file name exists and an empty string otherwise.
				If the file contains letters not present in the huffman_tree,
				return an empty string
*/
std::string huffman_tree::encode(const std::string &file_name) const {
	return "";
}

/*
Preconditions: string_to_decode is a string containing Huffman-encoded text
Postconditions: Returns the plaintext represented by the string if the string
				is a valid Huffman encoding and an empty string otherwise
*/
std::string huffman_tree::decode(const std::string &string_to_decode) const {
	return "";
}
