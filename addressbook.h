#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "helpers.h"

#define LINE_SIZE 128
#define MARGIN 2
#define NULL_SPACE 1


#define STUDENT_NAME "Christine Huynh"
#define STUDENT_ID "s3438653"
#define STUDENT_EMAIL "s3438653@student.rmit.edu.au"

/*REQ1: Print Student Information at startup.*/
void showStudentInformation();

void loadFile(char* fn, TelephoneBookList* tbl);

void releaseEntries();

/*REQ2: Load file into memory.*/
/*void loadFile()*/

#endif

