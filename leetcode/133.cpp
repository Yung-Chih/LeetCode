#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};


class Solution {
private:
    unordered_map<int, Node*> V;
public:
    Node* cloneGraph(Node* node) {
        if( node == nullptr ) return nullptr;
        if( V.count(node->val) )
            return V[node->val];
        
        V[node->val] = new Node(node->val);
        for( Node* nei : node->neighbors ){
            V[node->val]->neighbors.emplace_back( cloneGraph(nei) );
        }
        return V[node->val];
    }
};