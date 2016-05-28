objects = intrp2.o dbl_linked_list.o

# Hello there. \
 and more

intrp2: $(objects)
	gcc -Wall -o intrp2 $(objects)

dbl_linked_list.o: dbl_linked_list.h

test_linked_list: test_linked_list.c linked_list.c
	gcc -Wall test_linked_list.c linked_list.c -o test_linked_list

test_dbl_linked_list: test_dbl_linked_list.c dbl_linked_list.c
	gcc -Wall test_dbl_linked_list.c dbl_linked_list.c -o test_dbl_linked_list

.PHONY: clean

clean:
	rm -f intrp2 test_linked_list test_dbl_linked_list *.o
