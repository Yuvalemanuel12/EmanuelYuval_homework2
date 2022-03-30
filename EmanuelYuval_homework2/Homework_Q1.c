#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	int Id;
	char* name;
	int salary;
	int yearType;
	union startingYear
	{
		char hebrewYear[7];
		long long gregorianDate;
	};
}Worker;

typedef struct WorkerList
{
	Worker* data;
	struct WorkerList* next;
} WorkerList;

WorkerList* deleteWorstWorker(WorkerList* head);
WorkerList* addWorker(WorkerList* head, Worker* w);
void printWorker(Worker* ptrWorker);
Worker* createWorker();
void freeWorkers(WorkerList* head);
void update_worker(WorkerList* head, float percent);
int index(WorkerList* head, long unsigned id);
WorkerList* reverse(WorkerList* head);
void printAllWorkers(WorkerList* head);


void main()
{
	int i;
	Worker* ptrWorker;
	WorkerList* head = NULL;

	for (i = 0; i < 4; i++)
	{
		ptrWorker = createWorker();
		head = addWorker(head, ptrWorker);
	}
	printAllWorkers(head);
	head = reverse(head);
	printf("the reverse list is: \n");
	printAllWorkers(head);
	float perecent = 20.0;
	update_worker(head, perecent);
	printf("after salary increment:\n");
	printAllWorkers(head);
	freeWorkers(head);
}
void printAllWorkers(WorkerList* head)
{
	WorkerList* current;
	for (current = head; current != NULL; current = current->next)
	{
		printWorker(current->data);
	}
}

Worker* createWorker() {
	char name[20];
	char date[6];
	int  cse, date_e, yeartyp;
	int Id, solory;
	printf("insert Id ");
	scanf("%d", &Id);
	printf("insert name ");
	scanf("%s", name);
	printf("insert solory");
	scanf("%d", &solory);
	char* A = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(A, name);
	printf("please insert barth date in hebrew or in numbers. for numbers insert 0 and for hebrew insert 1 ");
	scanf("%d", &cse);

	switch (cse) {
	case 0:
		printf("insert date in numbers");
		scanf("%d", &date_e);
		break;

	case 1:
		printf("insert date in hebrew");
		scanf("%s", date);
		break;

	}

	Worker* st = (Worker*)malloc(sizeof(Worker));
	if (st) {
		st->Id = Id;
		st->name = A;
		st->salary = solory;
		st->yearType = cse;
		if (cse == 0) st->gregorianDate = date_e;
		if (cse == 1) strcpy(st->hebrewYear, date);
	}
	else {
		printf("no memory");
		return 0;
	}
	return st;
}

void printWorker(Worker* ptrWorker)
{
	printf("%d  %s  %d  ", ptrWorker->Id, ptrWorker->name, ptrWorker->salary);
	if (ptrWorker->yearType == 1)
	{
		printf("%d\n", ptrWorker->gregorianDate);
	}
	else
	{
		printf("%s\n", ptrWorker->hebrewYear);
	}
}



WorkerList* addWorker(WorkerList* head, Worker* w)
{
	WorkerList* node = (WorkerList*)malloc(sizeof(WorkerList));
	if (node == NULL)
	{
		printf("malloc failed\n");
		exit(1);
	}
	node->data = w;
	node->next = NULL;
	if (head == NULL)
	{
		head = node;
		return head;
	}
	WorkerList* prev = NULL, * current;
	for (current = head; current != NULL && current->data->salary < w->salary; current = current->next)
	{
		prev = current;
	}
	node->next = current;
	if (prev == NULL)
	{
		head = node;
	}
	else
	{
		prev->next = node;
	}
	return head;
}

int index(WorkerList* head, long unsigned id)
{
	WorkerList* current;
	int workerIndex;
	for (workerIndex = 1, current = head; current != NULL && current->data->Id < id; current = current->next, workerIndex++)
	{
	}
	if (current == NULL || current->data->Id > id)
	{
		return -1;
	}
	return workerIndex;

}

WorkerList* deleteWorstWorker(WorkerList* head)
{
	if (head == NULL)
	{
		return NULL;
	}
	WorkerList* node = head->next;
	free(head);
	return node;
}

WorkerList* reverse(WorkerList* head)
{
	WorkerList* current, * next, * ptr3;
	current = head;
	next = current->next;
	if (head == NULL)
	{
		return NULL;
	}
	while (next != NULL)
	{
		ptr3 = next->next;
		next->next = current;
		current = next;
		next = ptr3;
	}
	head->next = NULL;
	head = current;
	return head;
}

void update_worker(WorkerList* head, float percent)
{
	WorkerList* current;
	for (current = head; current != NULL; current = current->next)
	{
		current->data->salary += (long long)((float)current->data->salary * percent / 100.0);
	}
}

void freeWorkers(WorkerList* head)
{
	WorkerList* current, * next;
	for (current = head; current != NULL; current = next)
	{
		next = current->next;
		free(current);
	}
}