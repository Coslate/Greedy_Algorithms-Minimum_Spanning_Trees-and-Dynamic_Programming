#ifndef _SOLUTION_H_
#define _SOLUTION_H_

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <stack> 
#include <cfloat>
#include <MinHeap.h>
#include <Union_Find.h>

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

int maxSpacingCluster(const std::vector<std::vector<int>> &input_edge_list, const int k, UnionFind &unfnd_cluster, const int total_nodes, std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, std::unordered_set<std::string> &clusters);

#endif
