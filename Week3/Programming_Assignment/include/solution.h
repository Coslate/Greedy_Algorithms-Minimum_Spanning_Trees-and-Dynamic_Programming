#ifndef _SOLUTION_H_
#define _SOLUTION_H_

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
#include <cfloat>
#include <MinHeap.h>

void initializationAll(MinHeap<LinkedListNode> &min_heap, std::unordered_map<std::string, LinkedListNode*> &map_st2lln, const std::vector<int> &input_weight_list, const int total_vertexes);

void huffmanCoding(MinHeap<LinkedListNode> &min_heap, const int total_vertexes, std::unordered_map<std::string, LinkedListNode*> &map_st2lln);

int calMaxLengthHuffmanCode(const int total_vertexes, std::unordered_map<std::string, LinkedListNode*> &map_st2lln);

int calMinLengthHuffmanCode(const int total_vertexes, std::unordered_map<std::string, LinkedListNode*> &map_st2lln);

void weightedIndepSetDP(const std::vector<int> &input_weight_list, const int total_vertexes, std::vector<int> &ans_max_weight);

void weightedIndepSetReConstruct(const std::vector<int> &input_weight_list, const int total_vertexes, const std::vector<int> &ans_max_weight, std::unordered_set<int> &max_set);

#endif
