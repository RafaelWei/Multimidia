#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <fstream>

struct Node
{
    int val;
    int freq;
    Node* left;
    Node* right;
};

Node* create_node(int v, int f, Node* l, Node* r);
int get_tree_height(Node* head);
void delete_tree(Node* head);
void create_codes(Node* curr_node, std::vector<char>& prefix, int curr_level, std::vector<std::string>& codes);
void write_bit(bool bit, unsigned char& buffer, int& curr_idx, std::ofstream& file);
void serialize_huffman_tree(Node* head, std::ofstream& huffman_tree_file);
void deserialize_huffman_tree(Node*& head, std::ifstream& input_file);

#endif
