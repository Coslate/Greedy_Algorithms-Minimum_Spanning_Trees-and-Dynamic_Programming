//main.cpp
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_set>
#include <solution.h>

//All of the key values & weight of the nodes.
std::vector<int> input_key_list;
std::vector<float> input_weight_list;

int total_items = 0;

void readFile(std::string filename, std::vector<int> &input_key_list, std::vector<float> &input_weight_list, int &total_items){
    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open()){
        int  count_line = 0;
        while ( std::getline (myfile,line) ){
            std::istringstream iss(line); 
            std::string s;

            if(count_line == 0){
                iss >> s;
                total_items = std::stoi(s);
                ++count_line;
                continue;
            }

            iss >> s;
            input_key_list.push_back(std::stoi(s));
            iss >> s;
            input_weight_list.push_back(std::stof(s));
        }
        myfile.close();
    }else std::cout << "Unable to open file"; 
}

int main(int argc, char*argv[]){
    if(argc < 2){
        std::cerr<<"Error: There should be at least one input argument like ./main arg1."<<std::endl;
        return EXIT_FAILURE;
    }
    
    std::cout<<"----------------Q1.----------------"<<std::endl;
    readFile(argv[1], input_key_list, input_weight_list, total_items);
    std::cout<<"total_items = "<<total_items<<std::endl;

    for(size_t i=0;i<input_key_list.size();++i){
        std::cout<<input_key_list[i]<<" "<<input_weight_list[i]<<std::endl;
    }

    std::cout<<"> Initialization..."<<std::endl;
    float **ans = new float *[total_items];
    for(int j=0;j<total_items;++j){
        ans[j] = new float [total_items];
    }

    std::cout<<"> Dynamic Programming..."<<std::endl;
    optimalBSTSolDP(ans, total_items, input_weight_list);

    std::cout<<"> Print the result..."<<std::endl;
    std::cout<<"ans["<<total_items-1<<"]["<<0<<"] = "<<ans[total_items-1][0]<<std::endl;

    //deallocate
    for(int j=0;j<total_items;++j){
        delete [] ans[j];
    }
    delete [] ans;
    return EXIT_SUCCESS;
}
