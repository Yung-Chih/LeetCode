
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

#include <set>
using namespace std;
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if( !head ) return nullptr;

        ListNode* slow = head, *fast = head;
        bool cycle = false;
        while( slow != nullptr && fast != nullptr ){
            if( slow == fast ){
                cycle = true;
                break;
            }
            slow = slow->next;
            fast = (fast->next) ? fast->next->next : fast->next;
        }

        if( !cycle ) return nullptr;

        // Fast = 2n, slow = n, (fast - slow) % cycle length = 0
        // n % cycle length = 0
        // dist( fast/slow, head ) = cycle length 
        slow = head;
        while( slow != fast ){
            fast = fast->next;
            slow = slow->next;
        }
        return slow;


    }
};