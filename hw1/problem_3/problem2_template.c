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

    // Bubble sort repeatedly passes through the list
    bool swap_flag = true;
    while (swap_flag) {
        swap_flag = false;  // (This pass needs a swap to do another pass)

        // Create a current pointer initially pointing to the head
        elem_t *curr = *head;

        // One pass through the list (takes advantage of short-circuiting)
        while (curr != NULL && curr->next != NULL) {

            // If any element is greater than its next element, swap their values
            if (curr->value > curr->next->value) {
                int temp = curr->value;
                curr->value = curr->next->value;
                curr->next->value = temp;

                // A swap occurred during this pass through the list; do another pass
                swap_flag = true;
            }

            // Advance the current pointer
            curr = curr->next;
        }

    }

}

void bubble_sort_copy_ref(elem_t **head) {

    // Bubble sort repeatedly passes through the list
    bool swap_flag = true;
    while (swap_flag) {
        swap_flag = false;  // (This pass needs a swap to do another pass)

        // Create a current pointer initially pointing to the head
        elem_t *curr = *head;

        // One pass through the list (takes advantage of short-circuiting)
        while (curr != NULL && curr->next != NULL) {

            elem_t *a = curr;
            elem_t *b = curr->next;

            // If any element is greater than its next element, swap their pointers
            if (a->value  >  b->value) {

                if (a->prev != NULL) {
                    a->prev->next = b;
                } else {
                    *head = b;          // IMPORTANT: Swapping at start of list requires swapping head!
                }
                if (b->next != NULL) {
                    b->next->prev = a;
                }

                a->next = b->next;
                b->next = a;

                b->prev = a->prev;
                a->prev = b;

                // A swap occurred during this pass through the list; do another pass
                swap_flag = true;
            }

            // Advance the current pointer
            curr = curr->next;
        }

    }

}

elem_t *build_list(int num_elements) {
    srand(1234);

    elem_t *head = NULL;
    for (int i = 0; i < num_elements; i++) {
        elem_t *e = (elem_t *) malloc(sizeof(elem_t));

        e->value = i; //random() % 100;
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
    //bubble_sort_copy_value(&head);
    bubble_sort_copy_ref(&head);
    print_list(head);

    return 0;
}