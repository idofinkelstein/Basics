CC=gcc -ansi -pedantic-errors -Wall -Wextra -g

all: stack vector slist

# compiles stack
stack: stack_test.o stack.o
	$(CC) stack_test.o stack.o -o stack.out
	

stack_test.o: stack_test.c 
	$(CC) -c stack_test.c 

stack.o: stack.c 
	$(CC) -c stack.c 


#compiles vector
vector: vector_test.o vector.o
	$(CC) vector_test.o vector.o -o vector.out
	

vector_test.o: vector_test.c 
	$(CC) -c vector_test.c 

vector.o: vector.c 
	$(CC) -c vector.c 

#compiles slist
slist: slist_test.o slist.o
	$(CC) slist_test.o slist.o -o slist.out
	

slist_test.o: slist_test.c 
	$(CC) -c slist_test.c 

slist.o: slist.c 
	$(CC) -c slist.c 


clean_stack:
	rm stack_test.o stack.o stack.out

clean_vector:
	rm vector_test.o vector.o vector.out

clean_slist:
	rm slist_test.o slist.o slist.out




