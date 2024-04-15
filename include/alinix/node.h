
#include <alinix/types.h>
#include <alinix/interruptmanager.h>

typedef struct Node {
    InterruptHandler* data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    Node* tail;
} List;

List* createList() {
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void addNode(List* list, InterruptHandler* handler) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = handler;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void AddHandler(List** interruptCallbacks, InterruptHandler* handler, uint8_t interrupt) {
    if (interruptCallbacks[interrupt] == NULL) {
        interruptCallbacks[interrupt] = createList();
    }

    addNode(interruptCallbacks[interrupt], handler);
}