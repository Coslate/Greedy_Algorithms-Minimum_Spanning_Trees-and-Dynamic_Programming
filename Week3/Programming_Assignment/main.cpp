//main.cpp
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_set>
#include <solution.h>

//All of the weight of the vertexes.
std::vector<int> input_weight_list;

int total_vertexes = 0;

//Huffman coding result
std::unordered_map<LinkedListNode*, std::string> huffman_code;

std::unordered_map<std::string, LinkedListNode*> map_st2lln;

MinHeap<LinkedListNode> min_heap;

void readFile1(std::string filename){
    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open()){
        int  count_line = 0;
        while ( std::getline (myfile,line) ){
            std::istringstream iss(line); 

            if(count_line == 0){
                std::string s; iss >> s;
                total_vertexes = std::stoi(s);
                ++count_line;
                continue;
            }
                
            std::string s; iss >> s;
            input_weight_list.push_back(std::stoi(s));
        }
        myfile.close();
    }else std::cout << "Unable to open file"; 
}

int main(int argc, char*argv[]){
    if(argc < 3){
        std::cerr<<"Error: There should be at least one input argument like ./main arg1 arg2."<<std::endl;
        return EXIT_FAILURE;
    }
    
//Question 1. & Question 2.
    std::cout<<"Q1/Q2."<<std::endl;
    readFile1(argv[1]);
    std::cout<<"total_vertexes = "<<total_vertexes<<std::endl;
    //std::cout<<"input_weight_list.size() = "<<input_weight_list.size()<<std::endl;
    /*
    for(const auto &weight : input_weight_list){
        std::cout<<weight<<std::endl;
    }
    */

    std::cout<<"> Initialization..."<<std::endl;
    initializationAll(min_heap, map_st2lln, huffman_code, input_weight_list, total_vertexes);
    std::cout<<"> Huffman Coding..."<<std::endl;
    huffmanCoding(min_heap, total_vertexes, map_st2lln);
    std::cout<<"> Huffman Coding Result : "<<std::endl;
    for(int i=0;i<total_vertexes;++i){
        std::string symbol = std::to_string(i);
        std::cout<<symbol<<" : "<<map_st2lln[symbol]->GetHuffmanCode()<<", length = "<<map_st2lln[symbol]->GetHuffmanCode().length()<<std::endl;
    }

    std::cout<<"> Calculate Max/Min Length : "<<std::endl;
    int max_length = calMaxLengthHuffmanCode(total_vertexes, map_st2lln);
    int min_length = calMinLengthHuffmanCode(total_vertexes, map_st2lln);
    std::cout<<"max_length = "<<max_length<<std::endl;
    std::cout<<"min_length = "<<min_length<<std::endl;

    //Release the heap memory
    for(auto &elem : map_st2lln){
        LinkedListNode* the_node = elem.second;
        if(the_node != nullptr){
            delete the_node;
            the_node = nullptr;
        }
    }
    

    return EXIT_SUCCESS;
}
