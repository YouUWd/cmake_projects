#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for singly-linked list.
*/
struct ListNode {
    int val;
    struct ListNode *next;
};


struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {
    struct ListNode *ret = NULL, *tail = NULL;
    int carry = 0;
    while (l1 || l2) {
        int v1 = l1 ? l1->val : 0;
        int v2 = l2 ? l2->val : 0;
        int sum = v1 + v2 + carry;
        if (!ret) {
            ret = tail = malloc(sizeof(struct ListNode));
            tail->val = sum % 10;
            tail->next = NULL;
        } else {
            tail->next = malloc(sizeof(struct ListNode));
            tail = tail->next;
            tail->val = sum % 10;
            tail->next = NULL;
        }
        carry = sum / 10;
        if (l1) {
            l1 = l1->next;
        }
        if (l2) {
            l2 = l2->next;
        }
    }
    if (carry > 0) {
        tail->next = malloc(sizeof(struct ListNode));
        tail = tail->next;
        tail->val = carry;
        tail->next = NULL;
    }
    return ret;
}

int main() {
    struct ListNode *head = malloc(sizeof(struct ListNode));

    head->val = 9;

    struct ListNode n1;
    n1.val = 9;
    n1.next = NULL;

    head->next = &n1;

    addTwoNumbers(head, &n1);
    return 0;
}