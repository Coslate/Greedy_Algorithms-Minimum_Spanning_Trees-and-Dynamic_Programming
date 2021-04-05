//main.cpp
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <solution.h>

//All of the values & weight of the vertexes.
std::vector<std::vector<int>> input_item_list;

int total_items = 0;

int knapsack_size = 0;

void readFile(std::string filename, std::vector<std::vector<int>> &input_item_list, int &total_items, int &knapsack_size){
    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open()){
        int  count_line = 0;
        while ( std::getline (myfile,line) ){
            std::istringstream iss(line); 
            std::string s;
            std::vector<int> tmp_vw_list;

            if(count_line == 0){
                iss >> s;
                knapsack_size = std::stoi(s);
                iss >> s;
                total_items   = std::stoi(s);
                ++count_line;
                continue;
            }

            while(iss>>s){
                tmp_vw_list.push_back(std::stoi(s));
            }
            input_item_list.push_back(tmp_vw_list);
        }
        myfile.close();
    }else std::cout << "Unable to open file"; 
}

int main(int argc, char*argv[]){
    if(argc < 3){
        std::cerr<<"Error: There should be at least one input argument like ./main arg1 arg2."<<std::endl;
        return EXIT_FAILURE;
    }
    
    std::cout<<"----------------Q1.----------------"<<std::endl;
    readFile(argv[1], input_item_list, total_items, knapsack_size);
    std::cout<<"total_items = "<<total_items<<std::endl;
    std::cout<<"knapsack_size = "<<knapsack_size<<std::endl;
    /*
    for(const auto &item : input_item_list){
        std::cout<<item[0]<<" "<<item[1]<<std::endl;
    }
    */

    std::cout<<"> Initialization..."<<std::endl;
    long **ans = new long *[knapsack_size];
    for(int j=0;j<knapsack_size;++j){
        ans[j] = new long [total_items];
    }

    for(int i=0;i<knapsack_size;++i){
        ans[i][0] = 0;
    }

    long *ans_q1  = new long [knapsack_size];
    long *pre_ans_q1 = new long [knapsack_size]();

    std::cout<<"> Dynamic Programming..."<<std::endl;
    knapsackSolDP(ans, knapsack_size, total_items, input_item_list);                     //space complexity: O(knapsack_size*total_items)
    knapsackSolDPSpdUp(pre_ans_q1, ans_q1, knapsack_size, total_items, input_item_list); //space complexity: O(knapsack_size)

    std::cout<<"> Print the Result..."<<std::endl;
    std::cout<<"ans["<<knapsack_size-1<<"]["<<total_items-1<<"] = "<<ans[knapsack_size-1][total_items-1]<<std::endl;
    std::cout<<"ans_q1["<<knapsack_size-1<<"] = "<<ans_q1[knapsack_size-1]<<std::endl;

    //deallocate
    for(int j=0;j<knapsack_size;++j){
        delete [] ans[j];
    }
    delete [] ans;
    delete [] ans_q1;
    delete [] pre_ans_q1;
    input_item_list.clear();

    std::cout<<"----------------Q2.----------------"<<std::endl;
    readFile(argv[2], input_item_list, total_items, knapsack_size);
    std::cout<<"total_items = "<<total_items<<std::endl;
    std::cout<<"knapsack_size = "<<knapsack_size<<std::endl;
    /*
    for(const auto &item : input_item_list){
        std::cout<<item[0]<<" "<<item[1]<<std::endl;
    }
    */

    //If using the same solution as knapsacksolDP with ans[][] in Q1, the operation will full of cache miss and replacement between DRAM, and the running time will be very slow due to the very large space requirement(knapsack_size*total_items).
    //The speedup here we only use one array with size = knapsack_size to store the needed info to calculate the current ans.
    std::cout<<"> Initialization..."<<std::endl;
    long *ans_q2  = new long [knapsack_size];
    long *pre_ans_q2 = new long [knapsack_size]();

    std::cout<<"> Dynamic Programming..."<<std::endl;
    knapsackSolDPSpdUp(pre_ans_q2, ans_q2, knapsack_size, total_items, input_item_list); //space complexity: O(knapsack_size)

    std::cout<<"> Print the Result..."<<std::endl;
    std::cout<<"ans_q2["<<knapsack_size-1<<"] = "<<ans_q2[knapsack_size-1]<<std::endl;

    //deallocate
    delete [] ans_q2;
    delete [] pre_ans_q2;
    return EXIT_SUCCESS;
}
