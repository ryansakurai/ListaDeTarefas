task_list: main.o stack.o ordered_list.o
	gcc main.o stack.o ordered_list.o -o task_list

main.o: main.c libs/macros.h libs/stack.h libs/ordered_list.h
	gcc -c main.c
	
stack.o: libs/stack.c libs/stack.h
	gcc -c libs/stack.c

ordered_list.o: libs/ordered_list.c libs/ordered_list.h
	gcc -c libs/ordered_list.c

clean:
	rm task_list main.o stack.o ordered_list.o
