// You are given two non-empty linked lists representing two
// non-negative integers. The digits are stored in reverse order and
// each of their nodes contain a single digit. Add the two numbers and
// return it as a linked list.

// You may assume the two numbers do not contain any leading zero,
// except the number 0 itself.

// Complexity: O(max(m, n)) time. O(max(m, n)) space.

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode pre_head(0);
        ListNode* l3 = &pre_head;
        int carry = 0;

        while (l1 != nullptr || l2 != nullptr) {
            int a = l1 ? l1->val : 0;
            int b = l2 ? l2->val : 0;

            int sum = a + b + carry;
            int val = sum % 10;
            carry = sum / 10;

            l3->next = new ListNode(val);

            if (l1 != nullptr) {
                l1 = l1->next;
            }

            if (l2 != nullptr) {
                l2 = l2->next;
            }

            l3 = l3->next;
        }

        if (carry > 0) {
            l3->next = new ListNode(carry);
        }

        return pre_head.next;
    }
};


#include <sstream>
#include <iostream>

ListNode* new_list(int x)
{
    ListNode* head = new ListNode(x % 10);
    ListNode* node = head;

    while (x /= 10) {
        node->next = new ListNode(x % 10);
        node = node->next;
    }

    return head;
}

std::string list_to_str(ListNode* node)
{
    std::ostringstream oss;
    oss << '(' << node->val;
    node = node->next;

    while (node != nullptr) {
        oss << " -> " << node->val;
        node = node->next;
    }
    oss << ')';

    return oss.str();
}

bool list_equal(ListNode* l1, ListNode* l2)
{
    while (l1 != nullptr && l2 != nullptr) {
        if (l1->val != l2->val) {
            return false;
        }
        l1 = l1->next;
        l2 = l2->next;
    }

    return l1 == nullptr && l2 == nullptr;
}

void test(int a, int b)
{
    ListNode* l1 = new_list(a);
    ListNode* l2 = new_list(b);

    std::cout << "Input:    " << list_to_str(l1) << " + "
                              << list_to_str(l2) << '\n';

    ListNode* output = Solution().addTwoNumbers(l1, l2);
    ListNode* expected = new_list(a + b);

    std::cout << "Output:   " << list_to_str(output) << '\n';
    std::cout << "Expected: " << list_to_str(expected) << '\n';
    std::cout << "-----\n";

    if (!list_equal(output, expected)) {
        std::cout << "TEST FAILURE!\n";
        exit(EXIT_FAILURE);
    }
}

int main()
{
    test(0, 0);
    test(0, 1);
    test(1, 0);
    test(1, 1);
    test(1, 123);
    test(123, 1);
    test(243, 564);
    test(999, 999);
}
