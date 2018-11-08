typedef struct LongLinkedListSetNode
{
	void* tag;
	struct LongLinkedListSetNode* next;
} Node;

typedef struct LongLinkedListSet
{
	struct LongLinkedListSetNode* first;
	struct LongLinkedListSetNode* last;
	int size;
} LongLinkedListSet;

void add(LongLinkedListSet* list, void* add)
{
	if(list->size == 0)
	{
		Node* toAdd = (Node*)calloc(1, sizeof(Node));
		toAdd->tag = add;
		list->first = toAdd;
		list->last = toAdd;
		list->size = 1;
	}
	else
	{
		for(Node* check = list->first; check!=0; check=check->next)
		{
			if(check->tag == add)
				return;
		}

		Node* toAdd = (Node*)calloc(1, sizeof(Node));
		toAdd->tag = add;
		list->last->next = toAdd;
		list->last = toAdd;
		list->size++;
	}
}

int indexOf(LongLinkedListSet* list, void* checkLong)
{
	int i = 0;

	for(Node* check = list->first; check!=0; check=check->next)
	{
		if(check->tag == checkLong)
			return i;

		i++;
	}

	return -1;
}

void freeList(LongLinkedListSet* list)
{
	Node* cur = list->first;

	while(cur)
	{
		Node* next = cur->next;
		free(cur);
		cur = next;
	}
}
