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

std::unordered_map<std::string, LinkedListNode*> map_st2lln;

MinHeap<LinkedListNode> min_heap;

std::vector<int> ans_max_weight;

std::unordered_set<int> max_set;

void readFile(std::string filename, std::vector<int> &input_weight_list, int &total_vertexes){
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
    std::cout<<"----------------Q1/Q2.-----------------"<<std::endl;
    readFile(argv[1], input_weight_list, total_vertexes);
    std::cout<<"total_vertexes = "<<total_vertexes<<std::endl;
    //std::cout<<"input_weight_list.size() = "<<input_weight_list.size()<<std::endl;
    /*
    for(const auto &weight : input_weight_list){
        std::cout<<weight<<std::endl;
    }
    */

    std::cout<<"> Initialization..."<<std::endl;
    initializationAll(min_heap, map_st2lln, input_weight_list, total_vertexes);
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
    input_weight_list.clear();

//Question 3.
    std::cout<<"----------------Q3.-----------------"<<std::endl;
    readFile(argv[2], input_weight_list, total_vertexes);
    std::cout<<"total_vertexes = "<<total_vertexes<<std::endl;
    /*
    for(const auto &weight : input_weight_list){
        std::cout<<weight<<std::endl;
    }
    */

    std::cout<<"> Calculate max WIS using DP..."<<std::endl;
    weightedIndepSetDP(input_weight_list, total_vertexes, ans_max_weight);

    std::cout<<"> Reconstruct the max WIS..."<<std::endl;
    weightedIndepSetReConstruct(input_weight_list, total_vertexes, ans_max_weight, max_set);
    
    std::cout<<"> Whether 1(1st vertiex), 2(2nd vertex), 3, 4, 17, 117, 517, and 997 is in WIS? (1 is within, 0 is without for each)..."<<std::endl;
    std::vector<int> question_vec{0, 1, 2, 3, 16, 116, 516, 996};
    for(const auto &elem : question_vec){
        if(max_set.find(elem) != max_set.end()){//found one
            std::cout<<"1";
        }else{
            std::cout<<"0";
        }
    }
    std::cout<<std::endl;

    return EXIT_SUCCESS;
}
