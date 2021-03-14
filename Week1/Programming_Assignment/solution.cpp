//solution.cpp
#include <solution.h>

void scheduleDiff(const std::vector<std::pair<int, int>> &input_list, const int &total_jobs, std::vector<std::pair<int, int>> &sch_result){
    std::cout<<"total_jobs = "<<total_jobs<<std::endl;
    std::unordered_set<int> inserted_set;
    while(int(sch_result.size()) < total_jobs){
        long long max_score  = -INT_MAX;
        long long max_weight = -INT_MAX; 
        int max_pos;
        bool get_max = false;

        for(size_t i=0;i<input_list.size();++i){
            int score = input_list[i].first - input_list[i].second;
            if(score == max_score){
                if(input_list[i].first > max_weight){
                    if(inserted_set.find(i) == inserted_set.end()){
                        max_weight = input_list[i].first;
                        max_pos = int(i);
                        get_max = true;
                    }
                }
            }else if(score > max_score){
                if(inserted_set.find(i) == inserted_set.end()){
                    max_score = score;
                    max_weight = input_list[i].first;
                    max_pos = int(i);
                    get_max = true;
                }
            }
        }
        if(get_max){
            sch_result.push_back(input_list[max_pos]);
            inserted_set.insert(max_pos);
        }
        //std::cout<<"sch_result.size() = "<<sch_result.size()<<std::endl;
        //std::cout<<"progress = "<<sch_result.size()/(float)total_jobs*100<<"%"<<std::endl;
    }
}

void scheduleRatio(const std::vector<std::pair<int, int>> &input_list, const int &total_jobs, std::vector<std::pair<int, int>> &sch_result){
    std::unordered_set<int> inserted_set;
    while(int(sch_result.size()) < total_jobs){
        double max_score  = -DBL_MAX;
        int max_weight    = -INT_MAX; 
        int max_pos;
        bool get_max = false;

        for(size_t i=0;i<input_list.size();++i){
            double score = input_list[i].first/(double)input_list[i].second;
            if(score > max_score){
                if(inserted_set.find(i) == inserted_set.end()){
                    max_score = score;
                    max_weight = input_list[i].first;
                    max_pos = int(i);
                    get_max = true;
                }
            }else if(approximatelyEqual(score, max_score, 1.0e-10)){
                if(input_list[i].first > max_weight){
                    if(inserted_set.find(i) == inserted_set.end()){
                        max_weight = input_list[i].first;
                        max_pos = int(i);
                        get_max = true;
                    }
                }
            
            }
        }
        if(get_max){
            sch_result.push_back(input_list[max_pos]);
            inserted_set.insert(max_pos);
        }
        //std::cout<<"sch_result.size() = "<<sch_result.size()<<std::endl;
        //std::cout<<"progress = "<<sch_result.size()/(float)total_jobs*100<<"%"<<std::endl;
    }
}

bool approximatelyEqual(double a, double b, double epsilon){
    return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

long long calSumWeightedComplTime(const std::vector<std::pair<int, int>> &sch_result){
    long long sum_wt = 0;
    long long comp_time = 0;
    for(size_t i=0;i<sch_result.size();++i){
        comp_time += sch_result[i].second;
        sum_wt    += sch_result[i].first*comp_time;
    }
    return sum_wt;
}

void buildAdjList(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, const std::vector<std::vector<std::string>> &input_edge_list, AdjList &adj_list, const bool set_weight){
    //Build the mapping of node_name -> address for all nodes.
    for (auto &itRow : input_edge_list){
        for (size_t i=0; i<itRow.size()-1;++i){//only [0] & [1] are vertices, [2] is the weight of the edge from [0] -> [1].
            if(map_node_st2lln.find(itRow[i]) == map_node_st2lln.end()){//not found
                int node_data = 100000;//100000 is defined by the question. If a vertex v cannot be reached by source vertex, then the distance is 100000.
                LinkedListNode* new_node = new LinkedListNode(node_data, itRow[i]);
                map_node_st2lln[itRow[i]] = new_node;
            }
        }

        //Build the adjacent list for all nodes.
        if(!set_weight){
            adj_list.SetAdjList(map_node_st2lln[itRow[0]], map_node_st2lln[itRow[1]], 0);
        }else{
            adj_list.SetAdjList(map_node_st2lln[itRow[0]], map_node_st2lln[itRow[1]], std::stoi(itRow[2]));
        }

//        std::cout<<"in BuildAdjList > "<<itRow[0]<<"("<<map_node_st2lln[itRow[0]]<<") -> "<<itRow[1]<<"("<<map_node_st2lln[itRow[1]]<<"), "<<itRow[2]<<std::endl;
    }
}

void primHeapImplementation(std::unordered_set<std::string> &myset, std::unordered_set<std::string> &uncovered_set, std::vector<int> &mst, AdjList &adj_list, const int total_vertex_size, std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, MinHeap<LinkedListNode> &min_heap){
    while(int(myset.size()) != total_vertex_size){
        LinkedListNode min_edge_node   = min_heap.ExtractMin();
        std::string min_edge_node_name = min_edge_node.GetName();
        int         min_edge           = min_edge_node.GetData();

        //std::cout<<"myset.size() = "<<myset.size()<<std::endl;
        //std::cout<<"min_edge_node_name = "<<min_edge_node_name<<std::endl;
        //std::cout<<"min_edge = "<<min_edge<<std::endl;
        //std::cout<<"-------------"<<std::endl;
        myset.insert(min_edge_node_name);
        uncovered_set.erase(min_edge_node_name);
        mst.push_back(min_edge);
        
        //Traversing all the adjacent nodes.
        LinkedListNode *proc_node = map_node_st2lln[min_edge_node_name];
        LinkedList* the_linked_list = adj_list.ReadAdjList(proc_node);

        if(the_linked_list == NULL){
            std::cout<<"The proc_node: "<<proc_node->GetName()<<"("<<proc_node<<")"<<", explored = "<<proc_node->GetExplored()<<", has no adjacent List."<<std::endl;
        }

        if(the_linked_list != NULL){
            LinkedListNode* current_node = the_linked_list->GetFristNode();
            while(current_node != NULL){
                if(uncovered_set.find(current_node->GetName()) != uncovered_set.end()){//find a node in uncovered_set
                    int orig_min_edge_dist = min_heap.GetDataFromMap(current_node->GetName()).GetData();
                    int new_min_edge_dist  = current_node->GetData();
                    if(new_min_edge_dist < orig_min_edge_dist){
                        min_heap.DecreaseKey(current_node->GetName(), new_min_edge_dist);
                    }
                }
                current_node = current_node->GetNext();
            }
        }
    }
}

long long calTotalCost(const std::vector<int> &mst){
    long long sum_cost = 0;
    for(const auto &elem : mst){
        sum_cost += elem;
    }

    return sum_cost;
}
