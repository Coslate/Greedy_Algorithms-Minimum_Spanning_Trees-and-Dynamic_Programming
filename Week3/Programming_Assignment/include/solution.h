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

void initializationAll(MinHeap<LinkedListNode> &min_heap, std::unordered_map<std::string, LinkedListNode*> &map_st2lln, std::unordered_map<LinkedListNode*, std::string> &huffman_code, const std::vector<int> &input_weight_list, const int total_vertexes);

void huffmanCoding(MinHeap<LinkedListNode> &min_heap, const int total_vertexes, std::unordered_map<std::string, LinkedListNode*> &map_st2lln);

int calMaxLengthHuffmanCode(const int total_vertexes, std::unordered_map<std::string, LinkedListNode*> &map_st2lln);

int calMinLengthHuffmanCode(const int total_vertexes, std::unordered_map<std::string, LinkedListNode*> &map_st2lln);

#endif
