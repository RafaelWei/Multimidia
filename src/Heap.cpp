#include <vector>

#include "Huffman.hpp"
#include "Heap.hpp"

MinHeap::MinHeap(std::vector<int>& freq):elem_count{0}
{
    h.push_back(nullptr);
    for(int i=0; i<static_cast<int>(freq.size()); i++)
    {
        if(freq[i] != 0)
        {
            elem_count++;
            h.push_back(create_node(i, freq[i], nullptr, nullptr)); 
        }
    }

    heapify();
}

void MinHeap::heapify()
{
    for (int i=elem_count/2; i>=1; i--)
    {
        heapify_down(i);
    }
}

void MinHeap::heapify_down(int i)
{
    while (2*i <= elem_count)
    {
        int min_child = 2*i;
        if (min_child < elem_count && h[min_child]->freq > h[min_child+1]->freq)
        {
            min_child = min_child+1;
        }

        if (h[i]->freq > h[min_child]->freq) 
        {
            std::swap(h[i], h[min_child]);
            i = min_child;
        }
        else
        {
            break;
        }
    }
}

void MinHeap::heapify_up(int i)
{
    while (i>=2 && h[i]->freq < h[i/2]->freq)
    {
        std::swap(h[i], h[i/2]);
        i = i/2;
    }
}

void MinHeap::add(Node* new_node)
{
    h.push_back(new_node);
    elem_count++;
    heapify_up(elem_count);
}

bool MinHeap::empty()
{
    return elem_count == 0;
}

bool MinHeap::one_left()
{
    return elem_count == 1;
}

Node* MinHeap::extract_min()
{
    if (elem_count == 0)
        return nullptr;

    Node* to_return = h[1];

    h[1] = h[elem_count];
    h.pop_back();
    elem_count--;

    heapify_down(1);

    return to_return;
}
