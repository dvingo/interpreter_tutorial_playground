intrp2: intrp2.c
	gcc -o intrp2 intrp2.c

test_linked_list: test_linked_list.c linked_list.c
	gcc test_linked_list.c linked_list.c -o test_linked_list
.PHONY: clean

clean:
	rm -f intrp2
