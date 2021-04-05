//solution.cpp
#include <solution.h>

void optimalBSTSolDP(float ** &ans, const int total_items, const std::vector<float> &input_weight_list){
    for(int s=0;s<total_items;++s){
        for(int i=0;i<total_items;++i){
            int j = i+s;
            float min_val = FLT_MAX;
            float prob_sum = 0;

            if(j > total_items-1){continue;}

            for(int k=i;k<=j;++k){
                prob_sum += input_weight_list[k];
                
            }
            for(int r=i;r<=j;++r){
                float left_val  = (i > r-1) ? 0 : ans[r-1][i];
                float right_val = (r+1 > j) ? 0 : ans[j][r+1];
                float sum_f = left_val + right_val;
                if(min_val > sum_f){
                    min_val = sum_f;
                }
                
            }
            ans[j][i] = min_val + prob_sum;
            
            //long tmp_total_subprob = long(rows) * long(cols-1);
            //std::cout<<"i = "<<i<<", j = "<<j<<", cols = "<<cols<<", rows = "<<rows<<", tmp_total_subprob = "<<tmp_total_subprob<<", Complete "<<(((i-1)*rows + j)/(double)tmp_total_subprob)*100<<"% ..."<<std::endl;
        }
    }
}




