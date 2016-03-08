intrp2: intrp2.c linked_list.c
	gcc -o intrp2 intrp2.c linked_list.c

test_linked_list: test_linked_list.c linked_list.c
	gcc test_linked_list.c linked_list.c -o test_linked_list

test_dbl_linked_list: test_dbl_linked_list.c dbl_linked_list.c
	gcc test_dbl_linked_list.c dbl_linked_list.c -o test_dbl_linked_list

.PHONY: clean

clean:
	rm -f intrp2 test_linked_list test_dbl_linked_list
