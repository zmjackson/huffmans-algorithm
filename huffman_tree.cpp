#include "huffman_tree.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>

node::node()
	: value(0) {}

node::node(size_t value)
	: value(value) {}

huffman_node::huffman_node()
	: left(nullptr), right(nullptr) {}

huffman_node::huffman_node(size_t value)
	: node(value) {}

huffman_leaf::huffman_leaf(const char symbol, const size_t frequency) 
	: symbol(symbol), node(frequency) {}

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

	std::priority_queue<node_ptr, std::vector<node_ptr>, node_compare> node_queue;

	for (auto& char_data : char_map)
	{
		node_queue.push(std::make_shared<huffman_leaf>(char_data.first, char_data.second));
		std::cout << char_data.first << ' ' << char_data.second << std::endl;
	}

	while (node_queue.size() > 1)
	{
		node_ptr first = node_queue.top();
		node_queue.pop();
		node_ptr second = node_queue.top();
		node_queue.pop();
		huff_ptr new_node = std::make_shared<huffman_node>(first->value + second->value);
		new_node->left = first;
		new_node->right = second;
		node_queue.push(new_node);	
	}

	root = node_queue.top();
}

huffman_tree::~huffman_tree(){

}

void print_path(std::vector<bool>& path)
{
	for (bool i : path) std::cout << i;
	std::cout << std::endl;	
}

/*
Preconditions: Character is a character with an ASCII value
				between 0 and 127 (inclusive).
Postconditions: Returns the Huffman code for character if character is in the tree
				and an empty string otherwise.
*/

bool find_path(node_ptr head, std::vector<bool>& path, const char char_to_find)
{
	if (head == nullptr) return false;

	if (std::shared_ptr<huffman_leaf> leaf = std::dynamic_pointer_cast<huffman_leaf>(head))
	{
		if (leaf->symbol == char_to_find) return true;
	}
	else if (std::shared_ptr<huffman_node> huff_node = std::dynamic_pointer_cast<huffman_node>(head))
	{
		path.push_back(0);	
		print_path(path);
		if (!find_path(huff_node->left, path, char_to_find))
		{
			path.pop_back();			
		} 
		else
		{
			return true;
		}		
		path.push_back(1);
		print_path(path);
		if (!find_path(huff_node->right, path, char_to_find))
		{
			path.pop_back();			
		}
		else
		{
			return true;
		}
		
	}	
		
	return false;
}

std::string huffman_tree::get_character_code(char character) const 
{
	std::string character_code = "";
	std::vector<bool> path;
		
	if (std::shared_ptr<huffman_leaf> leaf_root = std::dynamic_pointer_cast<huffman_leaf>(root))
	{
		path.push_back(0);		
	}	
	else
	{
		int x = 5;
		find_path(root, path, character);
	}

	std::cout << "Path size:" << path.size() << std::endl;
	print_path(path);

	for (bool i : path) character_code.push_back(i);
	/*while (!path.empty())
	{
		if (path.front() == 0) character_code += "0";
		else character_code += "1";
		path.pop_back();
	}*/

	return character_code;
}

/*
Preconditions: file_name is the name of (and possibly path to) a text file
Postconditions: Returns the Huffman encoding for the contents of file_name
				if file name exists and an empty string otherwise.
				If the file contains letters not present in the huffman_tree,
				return an empty string
*/
std::string huffman_tree::encode(const std::string &file_name) const {

	char letter;
	std::string huffman_encoding = "";
	std::ifstream text_to_encode(file_name);

	if (text_to_encode)
	{
		while (text_to_encode.get(letter))
		{
			auto found_letter = letters_in_tree.find(letter);
			if (found_letter == letters_in_tree.end()) return "";
			else huffman_encoding += get_character_code(letter);
		}
	}

	return huffman_encoding;
}

/*
Preconditions: string_to_decode is a string containing Huffman-encoded text
Postconditions: Returns the plaintext represented by the string if the string
				is a valid Huffman encoding and an empty string otherwise
*/
std::string huffman_tree::decode(const std::string &string_to_decode) const {

	node_ptr curr_node = root;
	std::string decoded_text;

	for (char direction : string_to_decode)
	{
		
		if (std::shared_ptr<huffman_node> huff_node = std::dynamic_pointer_cast<huffman_node>(curr_node))
		{
			if (direction == '0') curr_node = huff_node->left;
			else if (direction == '1') curr_node = huff_node->right;
			else return "";
		}
		
		if (std::shared_ptr<huffman_leaf> leaf = std::dynamic_pointer_cast<huffman_leaf>(curr_node))
		{
			decoded_text.push_back(leaf->symbol);
			curr_node = root;
		}
	}
	return decoded_text;
}