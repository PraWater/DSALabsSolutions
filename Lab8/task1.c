#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct student
{
	long long int ID;
	char *name;
};
typedef struct student Student;

Student intos(long long int id, char *name)
{
	Student s;
	s.ID = id;
	s.name = name;
	return s;
}

struct node
{
	Student data;
	struct node *next;
};
typedef struct node node;
typedef node *NODE;

struct linked_list
{
	int count;
	NODE head;
};
typedef struct linked_list linked_list;
typedef linked_list *LIST;

LIST createNewList()
{
	LIST list = (LIST)malloc(sizeof(linked_list));
	if (list != NULL)
	{
		list->count = 0;
	}
	return list;
}

NODE createNewNode(Student data)
{
	NODE n = (NODE)malloc(sizeof(node));
	if (n != NULL)
	{
		n->next = NULL;
		n->data = data;
	}
	return n;
}

void insertNodeIntoList(NODE node, LIST list)
{
	if (list->count == 0)
	{
		list->head = node;
		node->next = NULL;
	}
	else
	{
		node->next = list->head;
		list->head = node;
	}
	++(list->count);
}

int hash1(long long int key, int size)
{
	return (int) key % size;
}

int hash2(long long int key)
{
	return (int) key % 512;
}

int hash3(long long int key)
{
	return (int) key % 997;
}

int mulHash(long long int key, int size)
{
	double A = 0.6180339887;
	double frac = key * A - (long long int)(key * A);
	return (int)(size * frac);
}

int hash5(long long int key)
{
	return (int) key % 887;
}

int hash6(long long int key)
{
	return (int) (key*997) % 1000;
}

struct hashTable
{
	int count;
	LIST* table;	
};
typedef struct hashTable HashTable;

HashTable* createHashTable(int size)
{
	HashTable *ht = (HashTable*) malloc(sizeof(HashTable));
	if (ht)
	{
		ht->count = 0;
		ht->table = (LIST *)malloc(size * sizeof(LIST));
	}
	return ht;
}

int main()
{
	FILE *fp = fopen("t1_data.txt", "r");
	if (!fp)
	{
		printf("Error opening file\n");
		exit(1);
	}
	int n;
	fscanf(fp, "%d\n", &n);
	HashTable *ht = createHashTable(2*n);
	int coll = 0;
	for (int i = 0; i < n; ++i)
	{
		char *name = (char *)malloc(30);
		long long id;
		fscanf(fp, "%lld,%[^\n]\n", &id, name);
		int hash = hash5(id);
		if (!ht->table[hash])
		 	--coll;
			ht->table[hash] = createNewList();
		++coll;
		NODE n = createNewNode(intos(id, name));
		insertNodeIntoList(n, ht->table[hash]);
		++ht->count;
	}
	printf("%d\n", coll);
	free(ht);
	fclose(fp);
}