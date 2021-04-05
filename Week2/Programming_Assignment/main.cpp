//main.cpp
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <solution.h>

int total_nodes  = 0;
int num_of_nodes = 0;
int num_of_edges = 0;

//All of the edges and the correspondent weight from input text file.
std::vector<std::vector<int>> input_edge_list;

std::vector<std::vector<std::string>> input_edge_s_list;

//Generate the correspondence between Node & LinkedListNode.
std::unordered_map<std::string, LinkedListNode*> map_node_st2lln;

UnionFind unfnd_cluster;

std::unordered_set<std::string> clusters;

void readFile1(std::string filename){
    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open()){
        int  count_line = 0;
        while ( std::getline (myfile,line) ){
            std::istringstream iss(line); 

            if(count_line == 0){
                for(std::string s; iss >> s;){
                    total_nodes = std::stoi(s);
                }
                ++count_line;
                continue;
            }
                
            std::vector<int> tmp_vec;
            for(std::string s; iss >> s;){
                tmp_vec.push_back(std::stoi(s));
            }
            input_edge_list.push_back(tmp_vec);
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
            input_edge_s_list.push_back(tmp_vec);
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
    std::cout<<"Q1."<<std::endl;
    readFile1(argv[1]);
    std::cout<<"original num of custers = "<<total_nodes<<std::endl;
    for(const auto &elem : input_edge_list){
        std::string node1_str = std::to_string(elem[0]);
        std::string node2_str = std::to_string(elem[1]);

        if(map_node_st2lln.find(node1_str) == map_node_st2lln.end()){
            LinkedListNode *new_node1 = new LinkedListNode(0, node1_str);
            map_node_st2lln[node1_str] = new_node1;
            unfnd_cluster.FindIterative(new_node1);
        }
        if(map_node_st2lln.find(node2_str) == map_node_st2lln.end()){
            LinkedListNode *new_node2 = new LinkedListNode(0, node2_str);
            map_node_st2lln[node2_str] = new_node2;
            unfnd_cluster.FindIterative(new_node2);
        }

//        std::cout<<elem[0]<<" "<<elem[1]<<" "<<elem[2]<<std::endl;
    }

    std::sort(input_edge_list.begin(), input_edge_list.end(),
          [](const std::vector<int>& a, const std::vector<int>& b) {
                return a[2] < b[2];
            }
    );

    int max_space = maxSpacingCluster(input_edge_list, 4, unfnd_cluster, total_nodes, map_node_st2lln, clusters);
    unsigned long count_i = 0;
    std::cout<<"final clusters = [";
    for(const auto &elem : clusters){
        if(clusters.size()==1){
            std::cout<<elem<<"]"<<std::endl;
        }else if(count_i==clusters.size()-1){
            std::cout<<elem<<"]"<<std::endl;
        }else{
            std::cout<<elem<<" ";
        }
        ++count_i;
    }
    std::cout<<"max_space = "<<max_space<<std::endl;
    std::cout<<"-------------------------"<<std::endl;

    return EXIT_SUCCESS;
}
