#ifndef _SOLUTION_H_
#define _SOLUTION_H_

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <AdjList.h>
#include <iostream>
#include <algorithm>
#include <stack> 
#include <cfloat>
#include <MinHeap.h>

class JobNode{
        int weight;
        int length;
    public : 
        JobNode() : weight(0), length(0){};
        JobNode(const int weight, const int length) : weight(weight), length(length){};

        inline int              GetWeight() const {return weight;}
        inline int              GetLength() const {return length;}

        inline void             SetWeight(const int val){weight = val;}
        inline void             SetLength(const int val){length = val;}
        inline void             operator=(const JobNode& other2) { length = other2.GetLength(); weight = other2.GetWeight();}
};


void scheduleDiff(const std::vector<std::pair<int, int>> &input_list, const int &total_jobs, std::vector<std::pair<int, int>> &sch_result);

void scheduleRatio(const std::vector<std::pair<int, int>> &input_list, const int &total_jobs, std::vector<std::pair<int, int>> &sch_result);

bool approximatelyEqual(double a, double b, double epsilon);

long long calSumWeightedComplTime(const std::vector<std::pair<int, int>> &sch_result);

void buildAdjList(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, const std::vector<std::vector<std::string>> &input_edge_list, AdjList &adj_list, const bool set_weight);

void primHeapImplementation(std::unordered_set<std::string> &myset, std::unordered_set<std::string> &uncovered_set, std::vector<int> &mst, AdjList &adj_list, const int total_vertex_size, std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, MinHeap<LinkedListNode> &min_heap);

long long calTotalCost(const std::vector<int> &mst);

#endif
