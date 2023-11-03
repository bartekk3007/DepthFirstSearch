#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListHeadNode
{
	int value;
	struct ListHeadNode* left;
	struct ListHeadNode* right;
	struct ListHeadNode* down;
};

struct TreeNode
{
	int value;
	struct TreeNode* left;
	struct TreeNode* right;
};

struct TreeNode* createTreeNode(int value)
{
	struct TreeNode* vertex = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	if (vertex)
	{
		vertex->value = value;
		vertex->left = NULL;
		vertex->right = NULL;
	}
	return vertex;
}

void insertVisited(struct TreeNode** visited, int value)
{
	if (*visited == NULL)
	{
		*visited = createTreeNode(value);
	}
	else
	{
		if (value <= (*visited)->value)
		{
			insertVisited(&(*visited)->left, value);
		}
		else
		{
			insertVisited(&(*visited)->right, value);
		}
	}
}

bool isVisited(struct TreeNode** visited, int value)
{
	if (*visited == NULL)
	{
		return false;
	}
	else if ((*visited)->value == value)
	{
		return true;
	}
	else
	{
		if (value <= (*visited)->value)
		{
			isVisited(&(*visited)->left, value);
		}
		else
		{
			isVisited(&(*visited)->right, value);
		}
	}
}

struct ListHeadNode* createNode(int n)
{
	struct ListHeadNode* vertex = (struct ListHeadNode*) malloc(sizeof(struct ListHeadNode));
	if (vertex)
	{
		vertex->value = n;
		vertex->left = NULL;
		vertex->right = NULL;
		vertex->down = NULL;
	}
	return vertex;
}

void insertNode(struct ListHeadNode** array, int n)
{
	if (*array == NULL)
	{
		*array = createNode(n);
	}
	else if ((*array)->right == NULL)
	{
		(*array)->right = createNode(n);
		(*array)->right->left = (*array);
	}
	else
	{
		insertNode(&(*array)->right, n);
	}
}

void insertChild(struct ListHeadNode** array, int m)
{
	if ((*array)->down == NULL)
	{
		(*array)->down = createNode(m);
	}
	else
	{
		insertChild(&(*array)->down, m);
	}
}

void insertSingleEdge(struct ListHeadNode** array, int n, int m)
{
	if (*array == NULL)
	{
		return;
	}
	else if ((*array)->value == n)
	{
		insertChild(array, m);
	}
	else
	{
		insertSingleEdge(&(*array)->right, n, m);
	}
}

void insertEdge(struct ListHeadNode** array, int n, int m)
{
	insertSingleEdge(array, n, m);
	insertSingleEdge(array, m, n);
}

struct ListHeadNode** childHeadNode(struct ListHeadNode** array, int n)
{
	while ((*array)->left)
	{
		(*array) = (*array)->left;
	}

	while ((*array))
	{
		if ((*array)->value == n)
		{
			return array;
		}
		else
		{
			(*array) = (*array)->right;
		}
	}

	return NULL;
}

void printList(struct ListHeadNode* array)
{
	while (array != NULL)
	{
		printf("Wierzcholek %d: ", array->value);
		struct ListHeadNode* bottom = array->down;
		while (bottom != NULL)
		{
			printf("%d ", bottom->value);
			bottom = bottom->down;
		}
		printf("\n");
		array = array->right;
	}
}

void dfsSingle(struct ListHeadNode** array, struct TreeNode** visited)
{
	struct ListHeadNode* temp = (*array);
	printf("Odwiedzono wierzcholek %d\n", temp->value);
	insertVisited(visited, temp->value);
	while (temp->down)
	{
		if (!isVisited(visited, temp->down->value))
		{
			dfsSingle(childHeadNode(array, temp->down->value), visited); //zle
		}
		temp->down = temp->down->down;
	}
}

void depthFirstSearch(struct ListHeadNode** array)
{
	struct TreeNode* visited = NULL;
	dfsSingle(array, &visited);
}

int main(void)
{
	struct ListHeadNode* array = NULL;

	insertNode(&array, 0);
	insertNode(&array, 1);
	insertNode(&array, 2);
	insertNode(&array, 3);
	insertNode(&array, 4);

	insertEdge(&array, 1, 2);
	insertEdge(&array, 3, 4);
	insertEdge(&array, 2, 3);
	insertEdge(&array, 2, 0);

	printList(array);

	depthFirstSearch(&array);

	return 0;
}