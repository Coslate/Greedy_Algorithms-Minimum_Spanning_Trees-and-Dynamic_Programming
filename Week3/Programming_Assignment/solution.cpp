//solution.cpp
#include <solution.h>


void initializationAll(MinHeap<LinkedListNode> &min_heap, std::unordered_map<std::string, LinkedListNode*> &map_st2lln, const std::vector<int> &input_weight_list, const int total_vertexes){
    for(int i=0;i<total_vertexes;++i){
        std::string symbol = std::to_string(i);
        if(map_st2lln.find(symbol) == map_st2lln.end()){//not found
            LinkedListNode* new_node = new LinkedListNode(input_weight_list[i], symbol);
            map_st2lln[symbol] = new_node;
            min_heap.Insert(*new_node);
        }
    }
}

void huffmanCoding(MinHeap<LinkedListNode> &min_heap, const int total_vertexes, std::unordered_map<std::string, LinkedListNode*> &map_st2lln){
    for(int i=total_vertexes;i<2*total_vertexes-1;++i){
        std::string symbol = std::to_string(i);
        LinkedListNode* min_node1 = map_st2lln[min_heap.ExtractMin().GetName()];
        LinkedListNode* min_node2 = map_st2lln[min_heap.ExtractMin().GetName()];
        LinkedListNode* inter_node = new LinkedListNode(min_node1->GetData()+min_node2->GetData(), symbol);
        inter_node->SetHuffmanCode("");
        //std::cout<<"<><><><><><><><><><><><>"<<std::endl;
        //std::cout<<"ineter_node = "<<inter_node->GetName()<<", weight = "<<inter_node->GetData()<<std::endl;
        //std::cout<<"left_child("<<min_node1<<") = "<<min_node1->GetName()<<", weight = "<<min_node1->GetData()<<std::endl;
        //std::cout<<"right_child("<<min_node2<<") = "<<min_node2->GetName()<<", weight = "<<min_node2->GetData()<<std::endl;
        inter_node->SetLeft(min_node1);
        inter_node->SetRight(min_node2);
        min_heap.Insert(*inter_node);

        if(map_st2lln.find(symbol) == map_st2lln.end()){
            map_st2lln[symbol] = inter_node;
        }
    }

    //std::cout<<">> Merge Complete..."<<std::endl;
    //std::cout<<">> min_heap.size() = "<<min_heap.GetSize()<<std::endl;

    std::queue<LinkedListNode> internal_node_q;
    internal_node_q.push(min_heap.ExtractMin());

    while(!internal_node_q.empty()){
        LinkedListNode current_node = internal_node_q.front();
        internal_node_q.pop();
        //std::cout<<current_node.GetName()<<", "<<"internal_node_q.size() = "<<internal_node_q.size()<<std::endl;

        LinkedListNode* left_child  = current_node.GetLeft();
        LinkedListNode* right_child = current_node.GetRight();

        if(left_child != NULL){
            left_child ->SetHuffmanCode(current_node.GetHuffmanCode()+"0");
            internal_node_q.push(*left_child);
            //std::cout<<"left_child("<<left_child<<") = "<<left_child->GetName()<<", "<<"huffman_code = "<<left_child->GetHuffmanCode()<<std::endl;
        }

        if(right_child != NULL){
            right_child->SetHuffmanCode(current_node.GetHuffmanCode()+"1");
            internal_node_q.push(*right_child);
            //std::cout<<"right_child("<<right_child<<") = "<<right_child->GetName()<<", "<<"huffman_code = "<<right_child->GetHuffmanCode()<<std::endl;
        }

        if(left_child != NULL && right_child != NULL){
            std::string the_node_name = current_node.GetName();
            LinkedListNode* del_current_node = map_st2lln[the_node_name];
            delete del_current_node;
            del_current_node = nullptr;
            map_st2lln.erase(the_node_name);
        }
    }
}

int calMaxLengthHuffmanCode(const int total_vertexes, std::unordered_map<std::string, LinkedListNode*> &map_st2lln){
    int max_length = -INT_MAX;
    for(int i=0;i<total_vertexes;++i){
        std::string symbol = std::to_string(i);
        int huffman_code_length = map_st2lln[symbol]->GetHuffmanCode().length();
        if(huffman_code_length > max_length){
            max_length = huffman_code_length;
        }
    }

    return max_length;
}

int calMinLengthHuffmanCode(const int total_vertexes, std::unordered_map<std::string, LinkedListNode*> &map_st2lln){
    int min_length = INT_MAX;
    for(int i=0;i<total_vertexes;++i){
        std::string symbol = std::to_string(i);
        int huffman_code_length = map_st2lln[symbol]->GetHuffmanCode().length();
        if(huffman_code_length < min_length){
            min_length = huffman_code_length;
        }
    }

    return min_length;
}
