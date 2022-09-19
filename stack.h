#include <stdlib.h>
#ifndef STACK_H_
#define STACK_H_
    struct Node{
        int val;
        struct Node *next;
    };
    void push(struct Node **head, int val){
        struct Node *new = (struct Node*)malloc(sizeof(struct Node));
        new->val = val;
        new->next = *head;
        *head = new;
    }

    int pop(struct Node **head){
        if (*head == NULL)
            return -1;
        struct Node* temp = *head;
        int val = temp->val;
        *head = (*head)->next;
        free(temp);
        return val;
    }

    void free_stack(struct Node **head){
        while(pop(head) != -1)
        {
            int i = pop(head);
        }
    }
#endif