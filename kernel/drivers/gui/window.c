/**
 * @author Ali Mirmohammad
 * @file window.c
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
 *  - Provide utils over the window of the kernel GUI.
*/
#include <alinix/mm.h>
#include <alinix/paging.h>
#include <alinix/gui/window.h>
#include <alinix/string.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Window utils")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")



static window_list_t *list;

/**
 * @brief Initializes the window list.
 *
 * This function dynamically allocates memory for a window list and initializes it.
 * The window list is a singly linked list where each node contains a pointer to a window.
 * The list is initialized with a single node where the `next` pointer is set to `NULL`
 * and the `window` pointer is set to `NULL`.
 *
 * @return void
 *
 * @throws None
 */
void windows_list_init() {
    list = (window_list_t *) kmalloc(sizeof(window_list_t));
    if(list) {
        list->next = NULL;
        list->window = NULL;
    }
}

/**
 * @brief Creates a new window with the given title, position, and dimensions.
 *
 * This function dynamically allocates memory for a new window and initializes it with the given title, position, and dimensions.
 * The function also adds the new window to the linked list of windows.
 *
 * @param title The title of the window.
 * @param x The x-coordinate of the top-left corner of the window.
 * @param y The y-coordinate of the top-left corner of the window.
 * @param w The width of the window.
 * @param h The height of the window.
 *
 * @return A pointer to the newly created window, or `NULL` if memory allocation fails.
 *
 * @throws None
 */
window_t *window_create(char *title, int x, int y, int w, int h) {
    window_t *window = (window_t *) kmalloc(sizeof(window_t));
    if(!window)
        return NULL;
    strcpy(window->title, title);
    window->x = x;
    window->y = y;
    window->w = w;
    window->h = h;
    window_list_t *new = (window_list_t *) kmalloc(sizeof(window_list_t));
    new->window = window;
    new->next = list->next;
    list->next = new;
    
    window->components = (components_list_t *) kmalloc(sizeof(components_list_t));
    window->components->component = NULL;
    window->components->next = NULL;
    
    return window;
}

/**
 * @brief Adds a component to the given window.
 *
 * This function adds a new component to the linked list of components of the given window.
 * The function dynamically allocates memory for a new component node and initializes it with the given component.
 * The new node is added at the beginning of the list.
 *
 * @param window The window to which the component should be added.
 * @param component The component to be added.
 *
 * @return void
 *
 * @throws None
 */
void add_component(window_t *window, void *component) {
    components_list_t *app = window->components;
    window->components = (components_list_t *) kmalloc(sizeof(components_list_t));
    window->components->component = (uint32_t *) component;
    window->components->next = app;
}

/**
 * @brief Paints all the windows in the linked list.
 *
 * This function iterates through the linked list of windows and calls the `paint_window()` function for each window.
 * The `paint_window()` function is responsible for rendering the window on the screen.
 *
 * @return void
 *
 * @throws None
 */
void paint_windows() {
    window_list_t *app = list;
    while(app != NULL) {
        if(app->window != NULL) {
            paint_window(app->window);
        }
        app = app->next;
    }
}

/**
 * @brief Paints the given window on the screen.
 *
 * This function draws the borders, background, and title of the given window on the screen.
 * It also iterates through the linked list of components of the window and calls the appropriate
 * drawing function for each component.
 *
 * @param window The window to be painted.
 *
 * @return void
 *
 * @throws None
 */
void paint_window(window_t *window) {
    draw_rect(window->x, window->y, window->w, window->h, WINDOW_EDGE_COLOR);
    draw_rect(window->x + 10, window->y + 20, window->w - 20, window->h - 35, WINDOW_BACKGROUND_COLOR);
    draw_string(window->x + 5, window->y + 5, window->title);
    
    // Draw components
    components_list_t *app = window->components;
    while(app != NULL) {
        if(app->component != NULL) {
            switch(app->component[0]) {
                case TYPE_TEXT_AREA:
                    draw_text_area(window, (text_area_t *) app->component);
                    break;
            }
        }
        app = app->next;
    }
}

text_area_t *create_text_area(int x, int y, int w, int h) {
    text_area_t *text_area = (text_area_t *) kmalloc(sizeof(text_area_t));
    text_area->type = TYPE_TEXT_AREA;
    text_area->x = x;
    text_area->y = y;
    text_area->w = w;
    text_area->h = h;
    text_area->cursorx = 0;
    text_area->cursory = 0;
    return text_area;
}

void text_area_set_text(text_area_t *text_area, char *text) {
    strcpy(text_area->content, text);
}

void text_area_append(text_area_t *text_area, char *text) {
    strcat(text_area->content, text);
}

void draw_text_area(window_t *window, text_area_t *text_area) {
    draw_rect(window->x + 10 + text_area->x, window->y + 20 + text_area->y, text_area->w, text_area->h, TEXT_AREA_COLOR);
    draw_string(window->x + 10 + text_area->x + text_area->cursorx, window->y + 20 + text_area->y + text_area->cursory, text_area->content);
}