#include "addressbook.h"
#include "addressbook_list.h"
#include "commands.h"
#include "helpers.h"

int main(int argc, char ** argv)
{
	char * var;
	char * fileName;
	int moves;
	char * token;
	int id;
	char name[NAME_LENGTH];
	char telephone[TELEPHONE_LENGTH];
	Boolean valid = FALSE;

	TelephoneBookList * loadedList;

	char userInput[LINE_SIZE + MARGIN];

	/*REQ1: Print Student Information at startup.*/
	showStudentInformation();

	while (1)
	{
		printf("Enter your command: ");

		/*Console expects string/data and saves as UserInput*/
		fgets(userInput, LINE_SIZE + MARGIN, stdin);
		/*If input is not endline char (hard-enter)*/
		if (userInput[strlen(userInput) - 1] != '\n')
		{
			printf("Error: Invalid Input\n\n");
			readRestOfLine();
		}

		if (userInput[0] == '\n')
		{
			printf("Error: Invalid Input\n\n");
			readRestOfLine();
		}

		else /*Input is other forms of valid command*/
		{
			/*Removes end char*/
			userInput[strlen(userInput) - 1] = 0;

			/*var is equal to the command (load..)*/
			var = strtok(userInput, " ");

			/*REQ2: Load telepone book file into memory.
			* User has inputted 'load' command.
			* Gets second string, and saves to filename.
			* Calls commandLoad('afilename.txt').
			*/
			if (strcmp(var, COMMAND_LOAD) == 0)
			{
				var = strtok(NULL, " ");
				fileName = var;
				loadedList = commandLoad(fileName);

			}
			/*REQ4: Unload list and release memory. EDIT
			* User has inputted 'unload' command.
			* Calls commandUnload().
			*/
			else if (strcmp(var, COMMAND_UNLOAD) == 0)
			{
				if (loadedList->size != 0)
				{
					if (var != NULL)
					{
						commandUnload(loadedList);
					}
					else
					{
						printf("> Error, command Load needs a fileName.\n");
					}
				}
				else
				{
					printf("> There is no list to unload.\n\n");

				}
			}

			/*REQ5: Quit program. - Unload 1st then quit. EDIT
			* User has inputted 'quit' command.
			* Calls releaseEntries().
			* Exits program.
			*/
			else if (strcmp(var, COMMAND_QUIT) == 0)
			{
				if (loadedList->size != 0)
				{
					commandUnload(loadedList);
				}

				printf("> Goodbye. \n\n");
				return EXIT_SUCCESS;
			}

			/*REQ6: Display telephone book content.
			* User has inputted 'display' command.
			* Calls commandDisplay().
			*/
			else if (strcmp(var, COMMAND_DISPLAY) == 0)
			{
				commandDisplay(loadedList);
			}

			/*REQ7a: Move cursor forward in telephone book list.
			* User has inputted 'forward int' command.
			* Calls commandForward()
			*/
			else if (strcmp(var, COMMAND_FORWARD) == 0)
			{
				if (loadedList->size != 0)
				{
					if (var != NULL)
					{
						var = strtok(NULL, " ");
						moves = atoi(var);
						commandForward(loadedList, moves);
					}
					else
					{
						printf("> Error, command Forward needs a variable.\n");
					}
				}
				else
				{
					printf("> There is no list currently loaded to memory.\n\n");
				}
			}

			/*REQ7b: Move cursor backward in telephone book list.
			* User has inputted 'backward int' command.
			* Calls commandBackward()
			*/
			else if (strcmp(var, COMMAND_BACKWARD) == 0)
			{
				if (loadedList->size != 0)
				{
					var = strtok(NULL, " ");
					if (var != NULL)
					{
						moves = atoi(var);
						commandBackward(loadedList, moves);
					}
					else
					{
						printf("> Error, command Backward needs a variable.\n");
					}
				}
				else
				{
					printf("> There is no list currently loaded to memory.\n\n");
				}
			}

			/*REQ8: Inserts new entry in telephone book list.
			* User has inputted 'insert int, char *, char *' command.
			* Calls commandInsert()
			*/
			else if (strcmp(var, COMMAND_INSERT) == 0)
			{
				if (loadedList->size != 0)
				{
					valid = TRUE;
					token = strtok(NULL, ", ");
					if (token != NULL)
					{
						id = atoi(token);
					}
					else
					{
						valid = FALSE;
						printf("> ID cannot be NULL.\n");
					}

					token = strtok(NULL, ", ");
					if (token != NULL)
					{
						strcpy(name, token);
					}
					else
					{
						valid = FALSE;
						printf("> Name cannot be NULL.\n");
					}

					token = strtok(NULL, " ");
					if (token != NULL)
					{
						strcpy(telephone, token);
					}
					else
					{
						valid = FALSE;
						printf("> Telephone cannot be NULL.\n");
					}
				}
				else
				{
					valid = FALSE;
					printf("> Attempted to add to empty list.\n");
				}

				if (valid == FALSE)
				{
					printf("> Insert entry failed.\n");
				}

				else if (id > loadedList->size &&
					strlen(name) <= NAME_LENGTH && strlen(name) >= 1 &&
					strlen(telephone) == TELEPHONE_LENGTH - 1)
				{
					valid = TRUE;
				}

				else
				{
					printf("> Insert entry failed, incorrect format.\n\n");
				}

				/*Add new entry to loaded list*/
				if (valid == TRUE)
				{
					commandInsert(loadedList, id, name, telephone);
				}
			}

			/*REQ10: Finds an entry in list.
			* User has inputted 'find, char * name' command.
			* Calls commandFind()
			*/
			else if (strcmp(var, COMMAND_FIND) == 0)
			{
				if (loadedList->size != 0)
				{
					var = strtok(NULL, " ");
					if (var != NULL)
					{
						if (loadedList != NULL)
						{
							commandFind(loadedList, var);
						}
						else
						{
							printf("> Error: Unable to find node.\n\n");
						}
					}
					else
					{
						printf("> Error, command Find needs a Name.\n");
					}
				}
				else
				{
					printf("> There is no list currently loaded to memory.\n\n");
				}
			}

			/*REQ12: Reverse order of list.
			* User has inputted 'reverse' command.
			* Calls commandReverse()
			*/
			else if (strcmp(var, COMMAND_REVERSE) == 0)
			{
				if (loadedList->size != 0)
				{
					commandReverse(loadedList);
				}
				else
				{
					printf("> There is no list currently loaded to memory.\n\n");
				}
			}

			/*REQ14: Save list to csv file.
			* User has inputted 'save, char* fileName' command.
			* Calls commandSave()
			*/
			else if (strcmp(var, COMMAND_SAVE) == 0) 
			{
				var = strtok(NULL, " ");
				if (var != NULL)
				{
					commandSave(loadedList, var);
				}
				else
				{
					printf("> Error, command Save needs a fileName.\n");
				}
			}

			else /*Input unrecognized by console.*/
			{
				printf("Error: Invalid input.\n\n");
				readRestOfLine();
			}
		}
	}
	return EXIT_SUCCESS;
}

/*REQ1: Print Student Information at startup.
* showStudentInformation() - prints student information at startup.
*
* Parameters:
*
* Returns:
*/
void showStudentInformation()
{
	printf("-----------------------------------------------------------------\n");
	printf("Student name: %s\n", STUDENT_NAME);
	printf("Student number: %s\n", STUDENT_ID);
	printf("Advanced Programming Techniques, Assignment Two, Semester 1, 2016\n");
	printf("-----------------------------------------------------------------\n\n");
}
