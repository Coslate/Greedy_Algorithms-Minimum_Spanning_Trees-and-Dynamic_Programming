//solution.cpp
#include <solution.h>

void knapsackSolDP(long ** &ans, const int rows, const int cols, const std::vector<std::vector<int>> &input_item_list){
    for(int i=1;i<cols;++i){
        for(int j=0;j<rows;++j){
            if(j < input_item_list[i][1]){
                ans[j][i] = ans[j][i-1];
                continue;
            }
            
            long tmp_plus = ans[j-input_item_list[i][1]][i-1] + input_item_list[i][0];
            if(ans[j][i-1] >= tmp_plus){
                ans[j][i] = ans[j][i-1];
            }else{
                ans[j][i] = tmp_plus;
            }
            
            //long tmp_total_subprob = long(rows) * long(cols-1);
            //std::cout<<"i = "<<i<<", j = "<<j<<", cols = "<<cols<<", rows = "<<rows<<", tmp_total_subprob = "<<tmp_total_subprob<<", Complete "<<(((i-1)*rows + j)/(double)tmp_total_subprob)*100<<"% ..."<<std::endl;
        }
    }
}

void knapsackSolDPSpdUp(long *&pre_ans, long *&ans, const int rows, const int cols, const std::vector<std::vector<int>> &input_item_list){
    for(int i=1;i<cols;++i){
        for(int j=0;j<rows;++j){
            if(j < input_item_list[i][1]){
                ans[j] = pre_ans[j];
                continue;
            }
            
            long tmp_plus = pre_ans[j-input_item_list[i][1]] + input_item_list[i][0];
            if(pre_ans[j] >= tmp_plus){
                ans[j] = pre_ans[j];
            }else{
                ans[j] = tmp_plus;
            }
            
            //long tmp_total_subprob = long(rows) * long(cols-1);
            //std::cout<<"i = "<<i<<", j = "<<j<<", cols = "<<cols<<", rows = "<<rows<<", tmp_total_subprob = "<<tmp_total_subprob<<", Complete "<<(((i-1)*rows + j)/(double)tmp_total_subprob)*100<<"% ..."<<std::endl;
        }

        for(int j=0;j<rows;++j){
            pre_ans[j] = ans[j];
        }
    }
}

