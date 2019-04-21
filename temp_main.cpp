#include "huffman_tree.h"
#include <iostream>
#include <queue>

int main()
{   
    huffman_tree tree("texts/mississippi.txt");
    std::string test = tree.get_character_code('i');
    std::cout << test << std::endl; 
}