CC=gcc -ansi -pedantic-errors -Wall -Wextra -g
all: stack vector
# compiles stack
stack: ilrd_stack_test.o ilrd_stack.o
	$(CC) ilrd_stack_test.o ilrd_stack.o -o stack.out
	

ilrd_stack_test.o: ilrd_stack_test.c 
	$(CC) -c ilrd_stack_test.c 

ilrd_stack.o: ilrd_stack.c 
	$(CC) -c ilrd_stack.c 


#compiles vector
vector: ilrd_vector_test.o ilrd_vector.o
	$(CC) ilrd_vector_test.o ilrd_vector.o -o vector.out
	

ilrd_vector_test.o: ilrd_vector_test.c 
	$(CC) -c ilrd_vector_test.c 

ilrd_vector.o: ilrd_vector.c 
	$(CC) -c ilrd_vector.c 


clean_stack:
	rm ilrd_stack_test.o ilrd_stack.o stack.out

clean_vector:
	rm ilrd_vector_test.o ilrd_vector.o vector.out
