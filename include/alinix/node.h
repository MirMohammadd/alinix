
#include <alinix/types.h>
#include <alinix/interruptmanager.h>

typedef struct Node {
    void (*handler)(uint8_t);
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    Node* tail;
} List;

void List_push(List* list, void (*handler)(uint8_t)) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->handler = handler;
    newNode->next = NULL;

    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

List* interruptCallbacks[256] = {NULL};


void AddHandler(uint8_t interrupt, void (*handler)(uint8_t)) {
    if (interruptCallbacks[interrupt] == NULL) {
        interruptCallbacks[interrupt] = (List*)malloc(sizeof(List));
        interruptCallbacks[interrupt]->head = NULL;
        interruptCallbacks[interrupt]->tail = NULL;
    }

    List_push(interruptCallbacks[interrupt], handler);
}