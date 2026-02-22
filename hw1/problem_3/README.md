# Doubly-Linked Bubble Sort

In `problem2_template.c`, I implemented the methods `bubble_sort_copy_value()`, 
which performs bubble sort on a provided doubly-linked list by
swapping consecutive values; and `bubble_sort_copy_ref()`, which performs
bubble sort by rearranging its elements' `prev` and `next` pointers.

Interestingly, running the code provided by the professor lead to
a memory leak!!! So, I also decided to implement a method `free_list()` to
make valgrind happy.