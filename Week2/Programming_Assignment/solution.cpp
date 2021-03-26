//solution.cpp
#include <solution.h>

int maxSpacingCluster(const std::vector<std::vector<int>> &input_edge_list, const int k, UnionFind &unfnd_cluster, const int total_nodes, std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, std::unordered_set<std::string> &clusters){
    int cluster_num = total_nodes; 
    int min_space = INT_MAX;
    for(const auto &elem : input_edge_list){
        std::string node1_str = std::to_string(elem[0]);
        std::string node2_str = std::to_string(elem[1]);
        LinkedListNode *node1 = map_node_st2lln[node1_str];
        LinkedListNode *node2 = map_node_st2lln[node2_str];

        if(unfnd_cluster.Union(node1, node2)){
            --cluster_num;
        }

        if(cluster_num == k){
            break;
        }
    }

    for(const auto &elem : input_edge_list){
        std::string node1_str = std::to_string(elem[0]);
        std::string node2_str = std::to_string(elem[1]);
        LinkedListNode *node1 = map_node_st2lln[node1_str];
        LinkedListNode *node2 = map_node_st2lln[node2_str];

        if(unfnd_cluster.FindIterative(node1) != unfnd_cluster.FindIterative(node2)){
            std::string ancestor = unfnd_cluster.FindIterative(node1)->GetName();
            if(clusters.find(ancestor) == clusters.end()){//not found
                clusters.insert(ancestor);
            }
            if(elem[2] < min_space){
                min_space = elem[2];
            }
        }
    }

    return min_space;
}
