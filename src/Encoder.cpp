#include <iostream>
#include <vector>
#include <fstream>

#include "Heap.hpp"
#include "Huffman.hpp"

void encode(const std::string file_names[])
{
    std::string temp {""};

    int WIDTH {0}, HEIGHT {0};
    int MAXVAL {0};
    int tree_height {0};
    std::vector<std::vector<int>> img;

    /*
     * Creating an input stream to read the file
     */

    std::ifstream input_file(file_names[0]);
    
    /*
     * The first line of the file is the string "P2"
     */

    std::getline(input_file, temp);

    /* 
     * The second line of the file is something about copyrights
     */

    std::getline(input_file, temp);

    /*
     * The next line describes the width and the heigh of the picture in this order
     */

    input_file >> WIDTH >> HEIGHT;

    /*
     * Then there is the MAXVAL. We input the MAXVAL and dynamically 
     * allocate an array with this value.
     *
     * The indexes of the array represent the pixel values and the interger
     * stored in this index represents the frequency of that value.
     */

    input_file >> MAXVAL;
    std::vector<int> freq(MAXVAL+1, 0);

    /*
     * Input the actual values of the pixels. We save the image pixels in the img matrix
     */

    img.resize(HEIGHT);
    for (auto it = img.begin(); it != img.end(); it++)
    {
        it->resize(WIDTH);
    }

    for (int line=0; line<HEIGHT; line++)
    {
        for (int col =0; col<WIDTH; col++)
        {
            input_file >> img[line][col];
            freq[img[line][col]]++;
        }
    }


    /*
     * With the values of the pixels, we can now instantiate the heap
     * and build the huffman encoding tree
     */

    MinHeap heap(freq);

    while(!heap.one_left())
    {
        Node* n1 = heap.extract_min();
        Node* n2 = heap.extract_min();

        Node* new_node = create_node(-1, n1->freq + n2->freq, n1, n2);

        heap.add(new_node);
    }

    Node* head = heap.extract_min();

    /*
     * Create the map value->code using the huffman tree
     */

    tree_height = get_tree_height(head);
    std::vector<char> prefix(tree_height);
    std::vector<std::string> codes(MAXVAL+1, "");
    create_codes(head, prefix, 0, codes); 

    /*
     * Compute the average length of the huffman encoding
     */
    
    double average = 0;
    int num_elems = 0;
    for (auto& str : codes)
    {
        if (!str.empty())
        {
            num_elems++; 
            average += str.size();
        }
    }

    average = average / num_elems;
    std::cout << "Average symbol length when compressing " << file_names[0].substr(7) << ": " << average << std::endl;

    /*
     * We need to save the codes to a file in order to 
     * be able to decode it afterwards
     */
    std::ofstream huffman_tree_file {file_names[1]};
    serialize_huffman_tree(head, huffman_tree_file);

    huffman_tree_file.close();


    /*
     * Encoding the picture using the generated mapping 
     * and writing to the output file
     */

    std::ofstream output_file {file_names[2], std::ios::binary | std::ios::out};
    unsigned char buffer {0};
    int curr_idx {0};
    std::string curr_code {""} ;

    for (int row = 0; row < WIDTH; row++)
    {
        for (int col = 0; col < HEIGHT; col++)
        {
            curr_code = codes[img[row][col]];
            for (int i=0; i<static_cast<int>(curr_code.size()); i++)
            {
                if (curr_code[i] == '1') write_bit(1, buffer, curr_idx, output_file);
                else                write_bit(0, buffer, curr_idx, output_file);
            }
        }
    }

    /*
     * If there is still something left in the buffer we need to flush it!!!
     */

    if (curr_idx != 0)
        output_file.put(buffer);
    
    /*
     * Close out and free the allocated memory
     */

    output_file.close();
    delete_tree(head);
    input_file.close();

}

int main(int argc, char** argv)
{
    std::string lena_files[] = {"../res/lena_ascii.pgm", "lena_huffman_tree.txt", "lena_ascii.huff"};
    std::string baboon_files[] = {"../res/baboon_ascii.pgm", "baboon_huffman_tree.txt", "baboon_ascii.huff"};
    encode(lena_files);
    encode(baboon_files);

    return 0;
}
