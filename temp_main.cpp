#include "huffman_tree.h"
#include <iostream>

int main()
{
    huffman_tree tree("texts/iliad_1.txt");
    std::string test = tree.get_character_code('a');

    std::cout << "Finished" << std::endl;
}