#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int get_MSE(const std::string files[])
{
    int WIDTH {0};
    int HEIGHT {0};
    int MAXVAL {0};
    std::string temp {""};

    std::vector<std::vector<int>> img;
    std::vector<std::vector<int>> huffman_img;

     /*
     * Creating an input stream to read the file
     */

    std::ifstream input_file(files[0]);
    std::ifstream huffman_input_file(files[1]);
    
    /*
     * The first line of the file is the string "P2"
     */

    std::getline(input_file, temp);
    std::getline(huffman_input_file, temp);

    /* 
     * The second line of the file is something about copyrights
     */

    std::getline(input_file, temp);
    std::getline(huffman_input_file, temp);

    /*
     * The next line describes the width and the heigh of the picture in this order
     */

    input_file >> WIDTH >> HEIGHT;
    huffman_input_file >> WIDTH >> HEIGHT;

    /*
     * Then there is the MAXVAL. We input the MAXVAL and dynamically 
     * allocate an array with this value.
     *
     * The indexes of the array represent the pixel values and the interger
     * stored in this index represents the frequency of that value.
     */

    input_file >> MAXVAL;
    huffman_input_file >> MAXVAL;

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
        }
    }

    huffman_img.resize(HEIGHT);
    for (auto it = huffman_img.begin(); it != huffman_img.end(); it++)
    {
        it->resize(WIDTH);
    }

    for (int line=0; line<HEIGHT; line++)
    {
        for (int col =0; col<WIDTH; col++)
        {
            huffman_input_file >> huffman_img[line][col];
        }
    }

    // Calculate the mean square error
    double MSE = 0;
    for (int line=0; line<HEIGHT; line++)
    {
        for (int col =0; col<WIDTH; col++)
        {
            MSE += (img[line][col]-huffman_img[line][col])*(img[line][col]-huffman_img[line][col]);
        }
    }

    MSE = (MSE)/(WIDTH*HEIGHT);
    
    return MSE;
}

int main()
{
    std::string lena_files[] = {"../res/lena_ascii.pgm", "lena_ascii.huff.pgm"};
    std::string baboon_files[] = {"../res/baboon_ascii.pgm", "baboon_ascii.huff.pgm"};

    std::cout << "Lena's compression mean square error:\n";
    std::cout << get_MSE(lena_files) << std::endl;

    std::cout << "Baboon's compression mean square error:\n";
    std::cout << get_MSE(baboon_files) << std::endl;

    return 0;
}
