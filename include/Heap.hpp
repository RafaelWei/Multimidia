#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include "Huffman.hpp"

class MinHeap
{
private:
    int elem_count;
    std::vector<Node*> h;

    void heapify();
    void heapify_down(int i);
    void heapify_up(int i);

public:
    MinHeap(std::vector<int>& freq);
    void add(Node* new_node);
    bool empty();
    bool one_left();
    Node* extract_min();
};

#endif
