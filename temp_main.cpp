#include "huffman_tree.h"
#include <iostream>
#include <queue>

int main()
{   
    huffman_tree tree("texts/mississippi.txt");
    std::string test = tree.get_character_code('i');
    std::cout << test << std::endl; 
    std::string mississippi = "100110011001110110111";
    std::string decoded = tree.decode(mississippi);
    std::cout << decoded;
}