/**
 * @author Ali Mirmohammad
 * @file node.c
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @abstraction:
 *  - Provides utility for the kernel nodes.
*/
#include <alinix/node.h>

List* interruptCallbacks[256] = {NULL};


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



void AddHandler(uint8_t interrupt, void (*handler)(uint8_t)) {
    if (interruptCallbacks[interrupt] == NULL) {
        interruptCallbacks[interrupt] = (List*)malloc(sizeof(List));
        interruptCallbacks[interrupt]->head = NULL;
        interruptCallbacks[interrupt]->tail = NULL;
    }

    List_push(interruptCallbacks[interrupt], handler);
}