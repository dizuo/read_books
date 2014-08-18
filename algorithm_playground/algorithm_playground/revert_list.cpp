#include "xshare.h"

struct SNode
{
	SNode* next;
	int data;
};

typedef SNode node_t;
typedef node_t* node_pt;

class SList
{
public:

	static void print_list(node_pt& phead);

	static void revert_list(node_pt& phead);

	static void destroy_list(node_pt& head);

	static void unit_test_case();

};

#ifdef REVERT_LIST_MAIN
int main()
{
	SList::unit_test_case();

	printf("any key pressed to exit...\n");
	getchar();

	return 0;
}
#endif

void SList::unit_test_case()
{
	srand(time(NULL));

	const int kMaxNum = 10;
	const int kMaxValue = 199;
	node_pt phead = NULL, pcur = NULL;

	for (int iter = 0; iter != kMaxNum; iter++)
	{
		node_pt pnode = new node_t;
		pnode->data = rand() % kMaxValue;
		pnode->next = NULL;

		if (iter == 0)
		{
			phead = pnode;
			pcur = phead;
		}
		else
		{
			pcur->next = pnode;
			pcur = pnode;
		}

	}

	printf("before reverse: \n");
	print_list(phead);

	revert_list(phead);
	
	printf("after reverse: \n");
	print_list(phead);

	destroy_list(phead);

}

void SList::print_list(node_pt& phead)
{
	node_pt pnode = phead;
	while (pnode)
	{
		printf("%d\t", pnode->data);
		pnode = pnode->next;
	}

}

void SList::destroy_list(node_pt& head)
{
	while (head)
	{
		node_pt tmp = head->next;

		delete head;
		head = NULL;

		head = tmp;
	}
}

void SList::revert_list(node_pt& phead)
{
	if (!phead || !phead->next)
	{
		return;
	}

	// split list two section.
	node_pt pcur = phead->next;
	phead->next = NULL;

	while (pcur)
	{
		// save next node.
		node_pt tmp = pcur->next;

		// insert pcur to front section.
		pcur->next = phead;
		phead = pcur;

		// next iteration
		pcur = tmp;
	}

}
