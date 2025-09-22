// https://leetcode.com/problems/add-two-numbers/description/?source=submission-noac
#include <iostream>

/* Definition for singly-linked list. */
struct ListNode
{
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
	{
		// NOTE: -1 - invalid node value
		static int depth = 1;
		if (depth == -1 || depth > 100)
			return nullptr;
		int val = 0;
		static int integerPartOfDivision = 0;
		if (l1) {
			if (0 <= l1->val && l1->val <= 9)
				val += l1->val;
			else
				depth = -1;
		}
		if (l2) {
			if (0 <= l2->val && l2->val <= 9)
				val += l2->val;
			else
				depth = -1;
		}
		val += integerPartOfDivision;
		integerPartOfDivision = val / 10;

		ListNode* next = nullptr;
		if ((l1 && l1->next) || (l2 && l2->next)) {
			next = addTwoNumbers(l1 ? l1->next : nullptr, l2 ? l2->next : nullptr);
			if (depth == -1 || depth > 100)
				return nullptr;
		} else {
			next = (integerPartOfDivision ? new ListNode(integerPartOfDivision) : nullptr);
		}
		depth++;
		return new ListNode(val % 10, next);
	}
};

void
printNodes(ListNode* node)
{
	if (node) {
		std::cout << "[" << node->val;
		while (node->next) {
			node = node->next;
			std::cout << ", " << node->val;
		}
		std::cout << "]" << std::endl;
	}
}

void
deleteNode(ListNode** node)
{
	if (node && (*node)) {
		if ((*node)->next) {
			deleteNode(&(*node)->next);
		}
		delete (*node);
		(*node) = nullptr;
	}
}

int main()
{
	// Case 1
	// ListNode fNode1(2, new ListNode(4, new ListNode(3)));
	// ListNode fNode2(5, new ListNode(6, new ListNode(4)));

	// Case 2
	// ListNode fNode1(0);
	// ListNode fNode2(0);

	// Case 3
	// ListNode fNode1(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9)))))));
	// ListNode fNode2(9, new ListNode(9, new ListNode(9, new ListNode(9))));

	// Case 4 - ???
	ListNode fNode1(0);
	ListNode fNode2(1);

	Solution _solution;
	ListNode* fNodeResult = _solution.addTwoNumbers(&fNode1, &fNode2);

	printNodes(fNodeResult);

	deleteNode(&fNodeResult);
	deleteNode(&fNode1.next);
	deleteNode(&fNode2.next);

	return 0;
}
