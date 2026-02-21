#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct elem {
    int value;
    struct elem *next;
    struct elem *prev;
} elem_t;

void print_list(elem_t *head) {
    elem_t *elem = head;
    while(elem != NULL) {
        printf("%d ", elem->value);
        elem = elem->next;
    }
    printf("\n");
}

void bubble_sort_copy_value(elem_t **head) {
    // implement me
}

void bubble_sort_copy_ref(elem_t **head) {
    // implement me
}

elem_t *build_list(int num_elements) {
    srand(1234);

    elem_t *head = NULL;
    for (int i = 0; i < num_elements; i++) {
        elem_t *e = (elem_t *) malloc(sizeof(elem_t));

        e->value = random() % 100;
        e->next = NULL;
        e->prev = NULL;

        if (head == NULL) {
            head = e;
        } else {
            e->next = head;
            head->prev = e;
            head = e;
        }
    }
    return head;
}

int main() {
    elem_t *head = build_list(100);
    print_list(head);
    printf("==================================\n");
    bubble_sort_copy_value(&head);
    bubble_sort_copy_ref(&head);
    print_list(head);

    return 0;
}