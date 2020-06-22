CC=gcc -ansi -pedantic-errors -Wall -Wextra -g

all: stack vector slist slist_additional queue dlist c_buffer

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

#compiles slist_additional
slist_additional: slist_additional_test.o slist_additional.o
	$(CC) slist_additional_test.o slist_additional.o -o slist_additional.out
	

slist_additional_test.o: slist_additional_test.c 
	$(CC) -c slist_additional_test.c 

slist_additional.o: slist_additional.c 
	$(CC) -c slist_additional.c 

#compiles queue
queue: queue_test.o queue.o
	$(CC) queue_test.o queue.o -o queue.out
	

queue_test.o: queue_test.c 
	$(CC) -c queue_test.c 

queue.o: queue.c 
	$(CC) -c queue.c 

#compiles dlist
dlist: dlist_test.o dlist.o
	$(CC) dlist_test.o dlist.o -o dlist.out
	

dlist_test.o: dlist_test.c 
	$(CC) -c dlist_test.c 

dlist.o: dlist.c 
	$(CC) -c dlist.c 

#compiles c_buffer
c_buffer: c_buffer_test.o c_buffer.o
	$(CC) c_buffer_test.o c_buffer.o -o c_buffer.out
	

c_buffer_test.o: c_buffer_test.c 
	$(CC) -c c_buffer_test.c 

c_buffer.o: c_buffer.c 
	$(CC) -c c_buffer.c 


#clean up
clean_stack:
	rm stack_test.o stack.o stack.out

clean_vector:
	rm vector_test.o vector.o vector.out

clean_slist:
	rm slist_test.o slist.o slist.out

clean_slist_additional:
	rm slist_additional_test.o slist_additional.o slist_additional.out

clean_queue:
	rm queue_test.o queue.o queue.out

clean_dlist:
	rm dlist_test.o dlist.o dlist.out

clean_c_buffer:
	rm c_buffer_test.o c_buffer.o c_buffer.out





