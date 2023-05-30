#include <iostream>
#include <fstream>
#include <vector> 

#include "Huffman.hpp"

#define LINE 512
#define COL  512

void decode(std::string file_names[], int MAXVAL)
{

    /* 
     * Deserialize huffman tree from the txt file
     */
    
    std::ifstream huffman_tree_file {file_names[0]};
    Node* head = nullptr;

    deserialize_huffman_tree(head, huffman_tree_file);

    huffman_tree_file.close();

    /*
     * Open the file to which we are going to write the 
     * decoded image
     */

    std::ofstream decoded_img_file {file_names[1]};

    /*
     * Write the header to the pgm file
     */

    decoded_img_file << "P2\n";
    decoded_img_file << "# Copyrights\n";
    decoded_img_file << LINE << " " << COL << "\n";
    decoded_img_file << MAXVAL << "\n";

    /*
     * Input the encoded image
     */

    std::ifstream encoded_img_file {file_names[2], std::ios::binary};

    /*
     * We read bit by bit to walk through the huffman tree
     * and find out which value it is 
     */

    int curr_row {1};
    int curr_col {1};
    char buffer {0};
    Node* curr_node = head;

    while (curr_row <= 512)
    {
        encoded_img_file.get(buffer);
        int i=0;
        for (i=0; i<8; i++)
        {
            if (buffer & (1 << (7-i))) curr_node = curr_node->right;
            else                       curr_node = curr_node->left;

            if (curr_node->val != -1)
            {
                decoded_img_file << curr_node->val;
                curr_node = head;
                if (curr_col == 512) 
                {
                    decoded_img_file << "\n";
                    curr_col = 1;
                    curr_row++;

                    if (curr_row > 512)
                        break;
                }
                else
                {
                    decoded_img_file << " ";
                    curr_col++;
                }
            }
        }
    }
    
    /* 
     * Clean up
     */

    decoded_img_file.close();
    encoded_img_file.close();
    delete_tree(head);
}

int main()
{
    std::string lena_files[] = {"lena_huffman_tree.txt", "lena_ascii.huff.pgm", "lena_ascii.huff"};
    std::string baboon_files[] = {"baboon_huffman_tree.txt", "baboon_ascii.huff.pgm", "baboon_ascii.huff"};

    decode(lena_files, 245);
    decode(baboon_files, 255);
    
    return 0;
}
