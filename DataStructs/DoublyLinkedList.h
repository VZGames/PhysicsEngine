#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>

typedef void (*TaskFnc)(void*);

struct Node
{
    void* data;
    Node *next = NULL;
    Node *prev = NULL;
};

struct List
{
    Node* head = NULL;
    Node* tail = NULL;
    size_t size = 0;
};

List* CreateList()
{
    return (List*)malloc(sizeof(List));
}

void Clear(List* list)
{
    Node* head = list->head;
    while (head != NULL) {
        Node* next = head->next;
        free(head);
        head = next;
    }
    list->size = 0;
}

void PushBack(List* list, void* data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    if (list->head == NULL)
    {
        list->head = list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
    list->size++;
}

void PushFront(List* list, void* data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = list->head;

    if (list->head != NULL)
    {
        list->head->prev = newNode;
    }

    list->head = newNode;

    list->size++;
}

void Travel(List* list, TaskFnc cb)
{
    Node* node = list->head;
    while (node != NULL) {
        Node* next = node->next;
        cb(node->data);
        node = next;
    }
}

#endif // DOUBLYLINKEDLIST_H
