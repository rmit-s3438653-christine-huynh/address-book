#include "commands.h"

/*REQ2: Load telepone book file into memory.
* commandLoad() - loads file into memory, tokenize and assign to nodes
*
* Parameters:
* fileName: char* - file to be loaded
*
* Returns: list
*/
TelephoneBookList * commandLoad(char * fileName) /*comment*/
{
	TelephoneBookList * list = malloc(sizeof(TelephoneBookList));
	TelephoneBookNode * node = malloc(sizeof(TelephoneBookNode));
	FILE * fp;
	char fileData[LINE_SIZE];
	char * token = NULL;
	Boolean corrupt = FALSE;

	printf("> Opening the file %s \n", fileName);

	/*Opens filename in read mode*/
	fp = fopen(fileName, "r");

	/*File opened successfully:*/
	if (fp != NULL)
	{
		printf("> Loading the file ...\n");

		/*Use strtok, split args into command and options*/
		while (fgets(fileData, LINE_SIZE, fp) != NULL)
		{
			/*If stringCompare*/
			if (strchr(fileData, '#') != NULL)
			{
				/*Ignore '#' and continue to next.*/
				continue;
			}

			createTelephoneBookList();

			/*add Buffering, check for nulls*/
			do
			{
				/*split the string*/
				node = createTelephoneBookNode();

				token = strtok(fileData, ",");
				if (strlen(token) >= NODE_MINIMUM_ID)
				{
					node->id = atoi(token);
				}
				else
				{
					corrupt = TRUE;
					token = NULL;
				}

				token = strtok(NULL, ",");
				if (strlen(token) <= NAME_LENGTH && strlen(token) >= 1)
				{
					memmove(token, token + 1, strlen(token));
					strcpy(node->name, token);
				}
				else
				{
					corrupt = TRUE;
					token = NULL;
				}

				token = strtok(NULL, "\n");
				if (strlen(token) == TELEPHONE_LENGTH)
				{
					memmove(token, token + 1, strlen(token));
					strcpy(node->telephone, token);
				}
				else
				{
					corrupt = TRUE;
					token = NULL;
				}

				insert(list, node);

				token = strtok(NULL, fileData);
			} while (token != NULL && !corrupt);
		}

		if (corrupt)
		{
			free(list);
			printf("> Error: The specified file is in the wrong format and cannot be loaded.\n");
		}
		else
		{
			printf("> %d phone book entries have been loaded from the file.\n", list->size);
		}
		printf("> Closing the file.\n\n");
		fclose(fp);
	}
	else
	{
		printf("> Error: Unable to find the specified file.\n\n");
		readRestOfLine();
	}
	return list;
}

/*REQ4: commandUnload(): releases loaded file from memory
*
* Parameters:
* list: TelephoneBookList* - struct to be populated with Address data.
*
* Returns:
*/
void commandUnload(TelephoneBookList * list)
{
	/*TelephoneBookNode* temp = (TelephoneBookNode*)malloc(sizeof(TelephoneBookNode));

	while ((temp = list->head) != NULL)
	{
		list->head = list->head->nextNode;
		free(temp);
	}
	list->size = 0;
	free(list);
	*/
	freeTelephoneBookList(list);
	printf("> The list is unloaded.\n\n");
}

/*REQ6: commandDisplay() - prints contents of TelephonebookList.
*
* Parameters:
* list: TelephoneBookList* - struct to be populated with Address data.
*
* Returns:
*/
void commandDisplay(TelephoneBookList * list)
{
	TelephoneBookNode * current = list->head;
	char * cursor = "";
	int count = 0;

	if (list->size != 0)
	{
		printf("\n---------------------------------------------\n");
		printf("| Pos | Serial | ID  | Name    | Telephone  |\n");
		printf("---------------------------------------------\n");
		while (current != NULL)
		{
			if (current == list->current)
			{
				cursor = "CUR";
			}
			else
			{
				cursor = " ";
			}
			count++;
			printf("| %-4s| %-7d| %-4d| %-8s| %-11s|\n", cursor, count, current->id, current->name, current->telephone);
			current = current->nextNode;
		}
		printf("---------------------------------------------\n");
		printf("| Total phone book entries: %2d              |\n", list->size);
		printf("---------------------------------------------\n\n");
	}
	else
	{
		printf("\n---------------------------------------------\n");
		printf("| Pos | Serial | ID  | Name    | Telephone  |\n");
		printf("---------------------------------------------\n");
		printf("|                                           |\n");
		printf("---------------------------------------------\n");
		printf("| Total phone book entries: %2d              |\n", list->size);
		printf("---------------------------------------------\n\n");
	}
}

/*REQ7a: commandForward() - moves cursor forward in list.
*
* Parameters:
* list: TelephoneBookList* - struct to be populated with Address data.
* moves: int - number of moves for cursor.
*
* Returns:
*/
void commandForward(TelephoneBookList * list, int moves)
{
	if (forward(list, moves))
	{
		printf("> Cursor moved successfully.\n\n");
	}
	else
	{
		printf("> Current Position pointer cannot go beyond boundaries of the linked-list.\n\n");
	}
}

/*REQ7b: commandBackward() - moves cursor backward in list.
*
* Parameters:
* list: TelephoneBookList* - struct to be populated with Address data.
* moves: int - number of moves for cursor.
*
* Returns:
*/
void commandBackward(TelephoneBookList * list, int moves)
{
	if (backward(list, moves))
	{
		printf("> Cursor moved successfully.\n\n");
	}
	else
	{
		printf("> Current Position pointer cannot go beyond boundaries of the linked-list.\n\n");
	}
}

/*REQ8: commandInsert() - insert new phone book entry.
*
* Parameters:
* list: TelephoneBookList* - struct to be populated with Address data.
* id: int - of NODE_MINIMUM_ID
* name: char * - of NAME_LENGTH
* telephone: char * - of TELEPHONE_LENGTH
*
* Returns:
*/
void commandInsert(TelephoneBookList * list, int id, char * name, char * telephone)
{
	TelephoneBookNode* newNode = createTelephoneBookNode();
	newNode->id = id;
	strcpy(newNode->name, name);
	strcpy(newNode->telephone, telephone);

	if (insert(list, newNode))
	{
		printf("> New entry added successfully.\n\n");
	}
	else
	{
		printf("> Insert failed.\n\n");
	}
}

/*REQ10: commandFind() - find entry in list.
*
* Parameters:
* list: TelephoneBookList* - struct to be populated with Address data.
* name: char * - of NAME_LENGTH
*
* Returns:
*/
void commandFind(TelephoneBookList * list, char * name) 
{
	TelephoneBookNode* findNode = findByName(list, name);
	if (findNode != NULL)
	{
		list->current = findNode;
	}
}

/*REQ11-BONUS: commandDelete() - delete an entry in list.
*
* Parameters:
* list: TelephoneBookList* - struct to be populated with Address data.
*
* Returns:
*/
void commandDelete(TelephoneBookList * list)
{
	/*calls commandFind
	* deletes entry and node
	* re-shuffles the list
	* update size*/
}

/*REQ12: commandReverse() - reverse order of list.
*
* Parameters:
* list: TelephoneBookList* - struct to be populated with Address data.
*
* Returns:
*/
void commandReverse(TelephoneBookList * list)
{
	/*Sourced from: www.geeksforgeeks.org/reverse-a-doubly-linked-list/*/
	TelephoneBookNode * temp;
	TelephoneBookNode * current = list->head;

	while (current != NULL)
	{
		temp = current->previousNode;
		current->previousNode = current->nextNode;
		current->nextNode = temp;
		current = current->previousNode;
	}

	if (temp != NULL)
	{
		list->head = temp->previousNode;
	}

}

/*REQ14: commandSave() - save list to cvs format.
*
* Parameters:
* list: TelephoneBookList* - struct to be populated with Address data.
* fileName: char* - name of file to save to
*
* Returns:
*/
void commandSave(TelephoneBookList * list, char * fileName)
{
	TelephoneBookNode * node = list->head;
	FILE * fp;

	printf("> Opening the file %s \n", fileName);

	/*Opens filename in write mode*/
	fp = fopen(fileName, "w");

	/*File opened successfully:*/
	if (fp != NULL)
	{
		fprintf(fp, "# This is the address book file: %s.\n#\n", fileName);
		while (node != NULL)
		{
			fprintf(fp, "%d, %s, %s\n", node->id, node->name, node->telephone);
			node = node->nextNode; /*24/05: currently prints 21 alice records <<FIX-THIS*/
		}
	}

	/*write contents to file*/
	printf("> Writing list content to file... \n");

	printf("> Closing file.\n\n");
	fclose(fp);
}

/*REQ13-BONUS: Sort address book entries by name.*/
void commandSortName(TelephoneBookList * list)
{

}

/*REQ15-BONUS: Sort address book entries randomly.*/
void commandSortRandom(TelephoneBookList * list)
{

}