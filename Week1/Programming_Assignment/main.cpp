//main.cpp
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <solution.h>

bool debug_addr     = false;
bool debug_key      = true;
bool debug_name     = true;
bool set_weight     = true;

int total_jobs = 0;

int num_of_nodes = 0;

int num_of_edges = 0;

std::vector<std::pair<int, int>> input_list;

std::vector<std::pair<int, int>> sch_result_q1;

std::vector<std::pair<int, int>> sch_result_q2;

//All of the edges and the correspondent weight from input text file.
std::vector<std::vector<std::string>> input_edge_list;

//Generate the correspondence between Node & LinkedListNode.
std::unordered_map<std::string, LinkedListNode*> map_node_st2lln;

//Adjacent list of a graph
AdjList adj_list(false, false);

std::unordered_set<std::string> myset;

std::unordered_set<std::string> uncovered_set;

std::vector<int> mst;

MinHeap<LinkedListNode> min_heap;


void readFile1(std::string filename){
    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open()){
        int  count_line = 0;
        while ( std::getline (myfile,line) ){
            std::istringstream iss(line); 

            if(count_line == 0){
                for(std::string s; iss >> s;){
                    total_jobs = std::stoi(s);
                }
                ++count_line;
                continue;
            }
                
            std::vector<int> tmp_vec;
            for(std::string s; iss >> s;){
                tmp_vec.push_back(std::stoi(s));
            }
            std::pair<int, int> job_s;
            job_s.first  = tmp_vec[0];
            job_s.second = tmp_vec[1];
            input_list.push_back(job_s);
        }
        myfile.close();
    }else std::cout << "Unable to open file"; 
}

void readFile2(std::string filename){
    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open()){
        int  count_line = 0;
        while ( std::getline (myfile,line) ){
            std::istringstream iss(line); 

            if(count_line == 0){
                std::string s; 
                iss >> s;
                num_of_nodes = std::stoi(s);
                iss >> s;
                num_of_edges = std::stoi(s);
                ++count_line;
                continue;
            }
                
            std::vector<std::string> tmp_vec;
            for(std::string s; iss >> s;){
                tmp_vec.push_back(s);
            }
            input_edge_list.push_back(tmp_vec);
        }
        myfile.close();
    }else std::cout << "Unable to open file"; 
}

int main(int argc, char*argv[]){
    if(argc < 3){
        std::cerr<<"Error: There should be at least one input argument like ./main arg1 arg2."<<std::endl;
        return EXIT_FAILURE;
    }
    
/*
    int method = 1;//1: Naive Based, 2: MinHeap Based
    if( (argc > 2) && (strcmp(argv[2], "-method") == 0)){
        method = atoi(argv[3]);
    }
    std::cout<<"method = "<<method<<std::endl;
*/

//Question 1.
    readFile1(argv[1]);
    std::cout<<"Q1, total_jobs = "<<total_jobs<<std::endl;
    std::cout<<"<scheduleDiff>..."<<std::endl;
    scheduleDiff(input_list, total_jobs, sch_result_q1);

    std::cout<<"print the scheduled result : "<<std::endl;
    for(const auto &elem : sch_result_q1){
        std::cout<<"("<<elem.first<<", "<<elem.second<<") ";
    }
    std::cout<<std::endl;

    std::cout<<"<calSumWeightedComplTime>..."<<std::endl;
    long long ans = calSumWeightedComplTime(sch_result_q1);
    std::cout<<"> ans = "<<ans<<std::endl;

    std::cout<<"==========================="<<std::endl;

//Question 2.
    std::cout<<"Q2, total_jobs = "<<total_jobs<<std::endl;
    std::cout<<"<scheduleRatio>..."<<std::endl;
    scheduleRatio(input_list, total_jobs, sch_result_q2);

    std::cout<<"print the scheduled result : "<<std::endl;
    for(const auto &elem : sch_result_q2){
        std::cout<<"("<<elem.first<<", "<<elem.second<<") ";
    }
    std::cout<<std::endl;

    std::cout<<"<calSumWeightedComplTime>..."<<std::endl;
    ans = calSumWeightedComplTime(sch_result_q2);
    std::cout<<"> ans = "<<ans<<std::endl;

//Question 3.
    readFile2(argv[2]);
    std::cout<<"==========================="<<std::endl;
    std::cout<<num_of_nodes<<" "<<num_of_edges<<std::endl;
    for(const auto &elem : input_edge_list){
        std::cout<<elem[0]<<" "<<elem[1]<<" "<<elem[2]<<std::endl;
    }

    std::cout<<"<buildAdjList>..."<<std::endl;
    buildAdjList(map_node_st2lln, input_edge_list, adj_list, set_weight);

    std::cout<<"----------adj_list------------"<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"----------------------"<<std::endl;

/*
    for (auto element : map_node_st2lln) {
        LinkedListNode* the_node = element.second;
        std::cout<<">>>> map_node_st2lln->the_node = "<<the_node->GetName()<<"("<<the_node<<")..."<<std::endl;
        adj_list.PrintAdjList(map_node_st2lln, the_node, debug_addr, debug_name, debug_key);
    }
*/

    std::cout<<"<primHeapImplementation>..."<<std::endl;
    std::cout<<"<initialization>..."<<std::endl;
    std::cout<<"source : "<<input_edge_list[0][0]<<std::endl;

    for (auto element : map_node_st2lln) {
        LinkedListNode* the_node = element.second;
        std::string node_name = element.first;
        if(node_name.compare(input_edge_list[0][0]) != 0){//different with source node
            uncovered_set.insert(node_name);
        }

        //Build the MinHeap
        min_heap.Insert(*the_node);
    }
    min_heap.DecreaseKey(input_edge_list[0][0], 0);
    primHeapImplementation(myset, uncovered_set, mst, adj_list, num_of_nodes, map_node_st2lln, min_heap);

    std::cout<<"<calTotalCost>..."<<std::endl;
    long long ans_total_cost = calTotalCost(mst);
    std::cout<<"ans_total_cost = "<<ans_total_cost<<std::endl;

    return EXIT_SUCCESS;
}
