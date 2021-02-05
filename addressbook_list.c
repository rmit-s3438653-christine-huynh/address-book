#include "addressbook_list.h"

TelephoneBookList * createTelephoneBookList()
{
	/*Sourced from Matt Boldger*/
	TelephoneBookList* list = malloc(sizeof(*list));
	list->head = list->tail = list->current = NULL;
	list->size = 0;
	return list;
}

void freeTelephoneBookList(TelephoneBookList* list)
{
	/*Sourced from stackoverflow.com:
	http://stackoverflow.com/questions/6417158/c-how-to-free-nodes-in-the-linked-list
	*/
	TelephoneBookNode * temp = temp;
	TelephoneBookNode * head = head;

	while (head != NULL)
	{
		temp = head;
		head = head->nextNode;
		freeTelephoneBookNode(temp);
	}
	list->size = 0;
	free(list);
	list = NULL;
}

TelephoneBookNode * createTelephoneBookNode()
{
	/*Sourced from Matt Boldger*/
	TelephoneBookNode * node = malloc(sizeof(*node));
	node->id = 0;
	strcpy(node->name, "");
	strcpy(node->telephone, "");
	node->previousNode = node->nextNode = NULL;
	return node;
}

void freeTelephoneBookNode(TelephoneBookNode * node)
{
	node->previousNode = NULL;
	node->nextNode = NULL;
	free(node);
	node = NULL;

}

Boolean insert(TelephoneBookList * list, TelephoneBookNode * node)
{
	/*Sourced from Matt Boldger*/
	if (list->head == NULL)
	{
		list->head = list->tail = list->current = node;
	}
	else
	{
		node->previousNode = list->tail;
		list->tail->nextNode = node;
		list->tail = node;
		list->current = node;
	}
	list->size++;

	return (TRUE);
}

Boolean forward(TelephoneBookList * list, int forward)
{
	int i = 0;
	for (i = 0; i < forward; i++)
	{
		if (list->current->nextNode != NULL)
		{
			list->current = list->current->nextNode;
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;
}

Boolean backward(TelephoneBookList * list, int backward)
{
	int i = 0;
	for (i = 0; i < backward; i++)
	{
		if (list->current->previousNode != NULL)
		{
			list->current = list->current->previousNode;
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;
}

Boolean delete(TelephoneBookList * list) /*INCOMPLETE*/
{
	/*Sourced from: 
	http://www.geeksforgeeks.org/delete-a-node-in-a-doubly-linked-list/
	*/
	/*TelephoneBookList * deleteList;
	TelephoneBookNode * deleteNode;
	*/
	/*Base case*/
	/*if (deleteNode->head == NULL)
	{
		return FALSE;
	}
	*/
	/* If node to be deleted is head node.*/
	/*if (deleteList->head == 0)
	{
		deleteList->head = deleteNode->nextNode;
	}
	*/
	/* Change next if node to be deleted is NOT the last node.*/
	/*if (deleteNode->nextNode != NULL)
	{

	}*/
	return FALSE;
}

TelephoneBookNode * findByID(TelephoneBookList * list, int id)
{
	return NULL;
}

TelephoneBookNode * findByName(TelephoneBookList * list, char * name)
{
	TelephoneBookNode * temp = list->head;
	while (temp != NULL)
	{
		if (strcmp(temp->name, name) == 0)
		{
			printf("> Record of %s is in the list.\n", name);
			return temp; 
		}
		else
			temp = temp->nextNode;
	}
	printf("> No record of %s is in the list.\n", name);
	return NULL;
}
