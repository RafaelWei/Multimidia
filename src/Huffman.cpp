#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

#include "Heap.hpp"
#include "Huffman.hpp"

Node* create_node(int v, int f, Node* l, Node* r)
{
    Node* new_node = new Node;
    new_node->val = v;
    new_node->freq = f;
    new_node->left = l;
    new_node->right = r;

    return new_node;
}

void delete_tree(Node* head)
{
    if (head == nullptr)
        return;

    delete_tree(head->left);
    delete_tree(head->right);

    delete head;
}

int get_tree_height(Node* head)
{
    if (head == nullptr)
        return 0;

    int left_height  = get_tree_height(head->left);
    int right_height = get_tree_height(head->right);

    return std::max(left_height, right_height) + 1;
}

void create_codes(Node* curr_node, std::vector<char>& prefix, int curr_level, std::vector<std::string>& codes)
{
    if (curr_node->left)
    {
        prefix[curr_level] = '0';
        create_codes(curr_node->left, prefix, curr_level+1, codes);
    }

    if (curr_node->right)
    {
        prefix[curr_level] = '1';
        create_codes(curr_node->right, prefix, curr_level+1, codes);
    }

    if (curr_node->left == nullptr && curr_node->right == nullptr)
    {
        int val {curr_node->val};
        std::string coded_val(prefix.begin(), prefix.begin()+curr_level);
        codes[val] = coded_val;
    }
}

void write_bit(bool bit, unsigned char& buffer, int& curr_idx, std::ofstream& file)
{
    buffer = (buffer << 1) | bit;
    curr_idx++;

    if (curr_idx == 8)
    {
        file.put(buffer);
        buffer = 0;
        curr_idx = 0;
    }
}

void serialize_huffman_tree(Node* head, std::ofstream& huffman_tree_file)
{
    if (head == nullptr)
    {
        huffman_tree_file << -2 << " ";
        return;
    }

    huffman_tree_file << head->val << " " << head->freq << " ";

    serialize_huffman_tree(head->left, huffman_tree_file);
    serialize_huffman_tree(head->right, huffman_tree_file);
}

void deserialize_huffman_tree(Node*& head, std::ifstream& input_file)
{
    int val {0};
    int freq {0};

    if (!input_file.eof()) 
        input_file >> val;

    if (val == -2)
        return;
            
    input_file >> freq;
    head = create_node(val, freq, nullptr, nullptr);

    deserialize_huffman_tree(head->left, input_file);
    deserialize_huffman_tree(head->right, input_file);
}

