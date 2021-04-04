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

void knapsackSolDP(long ** &ans, const int rows, const int cols, const std::vector<std::vector<int>> &input_item_list);
void knapsackSolDPSpdUp(long *&pre_ans, long *&ans, const int rows, const int cols, const std::vector<std::vector<int>> &input_item_list);

#endif
