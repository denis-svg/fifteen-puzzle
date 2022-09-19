#include <stdlib.h>
#ifndef QUEUE_H_
#define QUEUE_H_
    struct NodeQ{
        int val;
        struct NodeQ *next;
    };
    void qpush(struct NodeQ **front, struct NodeQ **rear, int val){
        struct NodeQ *new_node = (struct NodeQ*)malloc(sizeof(struct NodeQ));
        new_node->val = val;
        new_node->next = NULL;
        if (*front == NULL){
            *front = new_node;
            *rear = new_node;
        }else{
            (*rear)->next = new_node;
            *rear = new_node;
        }
    }

    int qpop(struct NodeQ **front, struct NodeQ **rear){
        if (*front == NULL)
            return -1;
        if ( (*front)->next == *rear )
            *rear = NULL;
        struct NodeQ* temp = *front;
        int val = temp->val;
        *front = (*front)->next;
        free(temp);
        return val;
    }

    void free_queue(struct NodeQ **front, struct NodeQ **rear){
        while(qpop(front, rear) != -1)
        {
            int i = qpop(front, rear);
        }
    }
#endif