#include "huffman_tree.h"
#include <iostream>
#include <queue>

using namespace std;

int main()
{   
    huffman_tree tree("texts/mississippi.txt");
    string test = tree.get_character_code('m');
    cout << test << endl; 
    string encoded = tree.encode("texts/mississippi.txt");    
    string decoded = tree.decode(encoded);
    cout << decoded;
}