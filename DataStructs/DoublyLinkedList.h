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
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
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
    newNode->prev = list->tail;
    newNode->next = NULL;

    if (list->head == NULL)
    {
        list->head = newNode;
    }

    if (list->tail != NULL)
    {
        list->tail->next = newNode;
    }

    list->tail = newNode;
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

void* ElementAt(List* list, size_t index)
{
    Node* node = list->head;
    if (index >= list->size)
    {
        printf("Index %d out of range, auto return last element if index out of range\n", index);
        return list->tail->data;
    }
    else
    {
        size_t begin = 0;
        size_t end = list->size / 2;
        if (index > list->size / 2)
        {
            begin = list->size / 2;
            end = list->size;
        }
        for (; begin < end && node != NULL; begin++) {
            node = node->next;
        }
        if (node == NULL) return NULL;
    }

    return node->data;
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
