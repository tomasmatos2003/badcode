#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    void *data;
    struct node *next;
} node;

typedef struct queue
{
    size_t size;
    size_t allocationSize;
    node *head;
    node *tail;
} queue;

queue *createQueue(size_t allocSize);
queue *enqueue(queue *q, void *data);
queue *dequeue(queue *q, void *data);
queue *front(queue *q, void *data);
queue *reverse(queue *q);
queue *clearQueue(queue *q);
void destroyQueue(queue **q);
size_t getSize(queue *q);
bool isEmpty(queue *q);
size_t getAllocationSize(queue *q);
queue *copyQueue(queue *src);
