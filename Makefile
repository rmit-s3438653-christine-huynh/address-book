SOURCES=addressbook.c addressbook_list.c commands.c helpers.c
HEADERS=addressbook.h addressbook_list.h commands.h helpers.h
OBJECTS=addressbook.o addressbook_list.o commands.o helpers.o
PROGRAM=addressbook
FLAGS=-ansi -pedantic -Wall -g

all:	$(OBJECTS) $(HEADERS)
	gcc $(FLAGS) -o $(PROGRAM) $(OBJECTS)
	
addressbook.o : addressbook.c addressbook.h
	gcc -c addressbook.c
	
addressbook_list.o: addressbook_list.c addressbook_list.h
	gcc -c addressbook_list.c
	
commands.o: commands.c commands.h
	gcc -c commands.c
	
helpers.o: helpers.c helpers.h
	gcc -c helpers.c

clean:
	rm $(PROGRAM) $(OBJECTS)
    
archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) Makefile
