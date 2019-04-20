#include "huffman_tree.h"
#include <iostream>

int main()
{
    huffman_tree tree("texts/mississippi.txt");
    std::string test1 = tree.get_character_code('s');
    std::string test2 = tree.get_character_code('i');

    std::cout << test1 << std::endl;
    //std::cout << test2 << std::endl;
}