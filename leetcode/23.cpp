#include <vector>
#include <queue>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* head = new ListNode(-1e9);
        ListNode* tail = head;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>> > pq;
        for(int i = 0; i<lists.size(); i++){
            if( lists[i] ){
                pq.emplace(lists[i]->val, i);
            }
        }

        while(!pq.empty()){
            int v = pq.top().first;
            int i = pq.top().second;
            pq.pop();
            
            tail->next = new ListNode(v);
            tail = tail->next;
            lists[i] = lists[i]->next;
            if( lists[i] ){
                pq.emplace( lists[i]->val, i );
            }
        }

        ListNode* dummy = head;
        head = head->next;
        delete dummy;
        return head;
    }
};