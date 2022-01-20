#include<iostream>
#include<cstdio>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(-1);
        ListNode* tail = dummy;
        int carry = 0, v;
        while( l1 != nullptr || l2 != nullptr || carry > 0){
            v = carry;
            if( l1 ) v += l1->val;
            if( l2 ) v += l2->val;

            ListNode* n = new ListNode( v%10 );
            carry = v/10;
            
            tail->next = n;
            tail = n;

            if( l1 ) l1 = l1->next;
            if( l2 ) l2 = l2->next;
        }

        ListNode* head = dummy->next;
        delete dummy;
        return head;
    }
};
