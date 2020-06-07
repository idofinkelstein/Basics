CC=gcc -ansi -pedantic-errors -Wall -Wextra -g
all: compile execute

compile: ilrd_stack_test.o ilrd_stack.o
	$(CC) ilrd_stack_test.o ilrd_stack.o -o stack.out
	

ilrd_stack_test.o: ilrd_stack_test.c 
	$(CC) -c ilrd_stack_test.c 

ilrd_stack.o: ilrd_stack.c 
	$(CC) -c ilrd_stack.c 

execute: stack.out
	stack.out
	
