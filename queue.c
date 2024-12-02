#include "queue.h"
#include <string.h>

node *createNode(void *data, size_t size)
{
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL)
        return NULL;

    new_node->data = malloc(size);
    if (new_node->data == NULL)
    {
        free(new_node);
        return NULL;
    }

    memcpy(new_node->data, data, size);
    new_node->next = NULL;

    return new_node;
}

queue *createQueue(size_t size)
{
    queue *q = (queue *)malloc(sizeof(queue));
    if (q == NULL)
        return NULL;

    q->allocationSize = size;
    q->size = 0;    
    q->head = q->tail = NULL;
    return q;
}

queue *enqueue(queue *q, void *data)
{
    if (q == NULL)
    {
        return NULL;
    }

    node *new_node = createNode(data, q->allocationSize);
    if (new_node == NULL)
        return NULL;

    if (q->size == 0)
    {
        q->head = q->tail = new_node;
    }
    else
    {
        q->tail->next = new_node;
        q->tail = new_node;
    }

    q->size++;
    return q;
}

queue *dequeue(queue *q, void *data)
{
    if (q == NULL)
    {
        return NULL;
    }

    if (q->size == 0)
    {
        return NULL;
    }

    node *to_del = q->head;
    if (q->size == 1)
    {
        memcpy(data, to_del->data, q->allocationSize);
        free(to_del->data);
        free(to_del);
        q->head = q->tail = NULL;
        q->size--;
        return q;
    }

    q->head = q->head->next;
    memcpy(data, to_del->data, q->allocationSize);
    free(to_del->data);
    free(to_del);
    q->size--;

    return q;
}

queue *front(queue *q, void *data)
{
    if (q == NULL)
    {
        return NULL;
    }

    if (q->size == 0)
    {
        return NULL;
    }

    memcpy(data, q->head->data, q->allocationSize);
    return q;
}

queue *reverse(queue *q)
{
    if (q == NULL)
    {
        return NULL;
    }

    if (q->size == 0)
    {
        return q;
    }
    else
    {
        void *data = malloc(q->allocationSize);
        if (data != NULL)
        {
            dequeue(q, data);
            reverse(q);
            enqueue(q, data);
            free(data);
        }

        return q;
    }
}

queue *clearQueue(queue *q)
{
    if (q == NULL)
        return NULL;

    while (!isEmpty(q))
    {
        node *temp = q->head;
        q->head = q->head->next;
        free(temp->data);
        free(temp);
        q->size--;
    }

    return q;
}

size_t getSize(queue *q)
{
    if (q == NULL)
        return 0;

    return q->size;
}

bool isEmpty(queue *q)
{
    return q->size == 0 ? true : false;
}

size_t getAllocationSize(queue *q)
{
    if (q == NULL)
        return 0;   // ERRO 1 : NULL

    return q->allocationSize;
}

queue *copyQueue(queue *src)
{
    if (src == NULL)
    {
        return NULL;
    }

    queue *new = createQueue(src->allocationSize);
    if (new == NULL)
        return NULL;

    // iterate through original queue and copy nodes
    node *currentOriginalNode = src->head;
    while (currentOriginalNode != NULL)
    {
        enqueue(new, currentOriginalNode->data);
        currentOriginalNode = currentOriginalNode->next;
    }

    return new;
}

void destroyQueue(queue **q)
{
    if (q == NULL)
    {
        return;
    }

    clearQueue(*q);
    free(*q);
    *q = NULL;
}
