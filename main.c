
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

#define MAX_COLLISION 150
#define MAX_HESH 40
#define MAX_KEY 50


struct Hesh_Table
{
	struct Node *array;
	struct Node **table;
	int maxArray;
	int free;
	int maxTable;
	
};
struct Node
{
	int key;
	int info;
	struct Node *next;
};

int heshFunction(int key)
{
	if(key < 0)
	{
		return ((key)%(MAX_HESH/2-1)+MAX_HESH/2)%(MAX_HESH/2);
	}
	else
	{
		return key%MAX_HESH/2+MAX_HESH/2;
	}
}

int findFree(struct Hesh_Table* heshTable)
{
	int free = heshTable->free;
	
	heshTable->free = heshTable->free + 1;
	
	return free;
}

struct Node* findEndOfList(struct Node *element)
{
	if(element->next == NULL)
	{
		return element;
	}
	
	return findEndOfList(element->next);
}

void printList(struct Node *element)
{
	//printf("\t key = %d; next = %d ",element->key,element->next);
	printf("key = %d; ",element->key);
	if(element->next == NULL)
	{
		//printf("last\n");
		
		return;
	}
	//printf("not last\n");
	
	printList(element->next);
}

void printHeshTable(struct Hesh_Table* heshTable)
{
	int i;
	for(i = 0; i < heshTable->maxTable; i++)
	{
 	 	printf("list hesh = %d:   ",i);
 	 	if(heshTable->table[i] != NULL)
 	 	{
 			printList(heshTable->table[i]);
			printf("\n");
 		}
	}
}

void initHeshTable(struct Hesh_Table* heshTable,int maxTable,int maxArray)
{
	int i;
	heshTable->table = (struct Node**)calloc(maxTable,sizeof(struct Node*));
	heshTable->array = (struct Node*)calloc(maxArray,sizeof(struct Node));
	heshTable->maxArray = maxArray;
	heshTable->free = 0;
	heshTable->maxTable = maxTable;
	
	for(i = 0; i < maxArray;i++)
	{
		heshTable->array[i].key = NULL;
		heshTable->array[i].next = NULL;
	}
	for(i = 0; i < maxTable;i++)
	{
		heshTable->table[i] = NULL;
	}
}

void addToHeshTable(struct Hesh_Table* heshTable, int key, int info)
{
	int hesh;
	int ifree;
	struct Node *buff;
	hesh = heshFunction(key);
	printf("key = %d; hesh = %d ",key,hesh);
	
	ifree = findFree(heshTable);
	printf("ifree = %d\n ",ifree);
	
	if(heshTable->table[hesh] == NULL)
	{
		printf("list is empty\n ");
		heshTable->table[hesh] = &heshTable->array[ifree];
		heshTable->array[ifree].key = key;
		printf("heshTable->table[hesh] = %d;\n heshTable->array[ifree].key = %d\n",heshTable->table[hesh],heshTable->array[ifree].key);
	}
	else
	{
	 	printf("list is not empty\n ");
		buff = findEndOfList(heshTable->table[hesh]);
		buff->next = &heshTable->array[ifree];
		heshTable->array[ifree].key = key;
		printf("buff->next = %d;\n heshTable->array[ifree].key = %d\n",buff->next,heshTable->array[ifree].key);
	}
	
	printf("");
	printf("\n");
	printf("\n");
}

void copyHeshTable(struct Hesh_Table* copy, struct Hesh_Table* paste,int offset,int size)
{
	paste->table = (copy->table+offset);
}


int main(void) 
{
	srand(time(NULL));
	
	printf("============INIT===============\n");
	
	int i,j, ifree,key;
	int hesh = 0;
	
	struct Node *buff;
	
	struct Hesh_Table heshTableMain; 
	initHeshTable(&heshTableMain,MAX_HESH,MAX_COLLISION);
	
	struct Hesh_Table heshTableFirst; 
	initHeshTable(&heshTableFirst,MAX_HESH/2,0); 
	
	struct Hesh_Table heshTableSecond; 
	initHeshTable(&heshTableSecond,MAX_HESH/2,0);
	
	for(i = 0; i < MAX_KEY*2;i++)
	{
		addToHeshTable(&heshTableMain,rand()%MAX_KEY*2-MAX_KEY,i);
		
	}
	printf("============INIT_AND===============\n\n");
	
	printf("\n============heshTableMain===============\n");
	
	printHeshTable(&heshTableMain);
	
	copyHeshTable(&heshTableMain,&heshTableFirst,0,MAX_HESH/2);
	copyHeshTable(&heshTableMain,&heshTableSecond,MAX_HESH/2,MAX_HESH/2);
	
	printf("\n\n============heshTableFirst===============\n");
	
	printHeshTable(&heshTableFirst);
	
	printf("\n\n============heshTableSecond===============\n");
	
	printHeshTable(&heshTableSecond);
	return 0;
}
