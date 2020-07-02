CC=gcc -ansi -pedantic-errors -Wall -Wextra -g

all: stack vector slist slist_additional queue dlist c_buffer sorted_list pqueue uid scheduler


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


#compiles sorted_list
sorted_list: sorted_list_test.o sorted_list.o dlist.o
	$(CC) sorted_list_test.o sorted_list.o dlist.o -o sorted_list.out
	
sorted_list_test.o: sorted_list_test.c 
	$(CC) -c sorted_list_test.c 

sorted_list.o: sorted_list.c 
	$(CC) -c sorted_list.c 


#compiles pqueue
pqueue: pqueue_test.o pqueue.o dlist.o sorted_list.o
	$(CC) pqueue_test.o pqueue.o dlist.o sorted_list.o -o pqueue.out
	
pqueue_test.o: pqueue_test.c 
	$(CC) -c pqueue_test.c 

pqueue.o: pqueue.c 
	$(CC) -c pqueue.c 


#compiles uid
uid: c_buffer_test.o uid.o
	$(CC) c_buffer_test.o uid.o -o uid.out
	
uid_test.o: uid_test.c 
	$(CC) -c uid_test.c 

uid.o: uid.c 
	$(CC) -c uid.c 


#compiles scheduler
scheduler: scheduler.o scheduler_test.o pqueue.o dlist.o sorted_list.o uid.o
	$(CC) scheduler.o scheduler_test.o pqueue.o dlist.o sorted_list.o uid.o -o scheduler.out
	
scheduler_test.o: scheduler_test.c 
	$(CC) -c scheduler_test.c 

scheduler.o: scheduler.c 
	$(CC) -c scheduler.c 

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

clean_sorted_list:
	rm sorted_list_test.o sorted_list.o sorted_list.out

clean_pqueue:
	rm pqueue_test.o pqueue.o pqueue.out

clean_uid:
	rm uid.o uid_test.o uid.out

clean_scheduler:
	rm scheduler.o scheduler_test.o scheduler.out



