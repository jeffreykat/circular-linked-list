#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
   TYPE value;
   struct Link* next;
   struct Link* prev;
};

struct CircularList
{
   int size;
   struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
   list->sentinel = malloc(sizeof(struct Link));
   list->sentinel->next = list->sentinel;
   list->sentinel->prev = list->sentinel;
   list->size = 0;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
   struct Link* newLink = malloc(sizeof(struct Link));
   newLink->value = value;
   newLink->next = NULL;
   newLink->prev = NULL;
   return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
   struct Link* newLink = createLink(value);
   newLink->prev = link;
   newLink->next = link->next;
   link->next->prev = newLink;
   link->next = newLink;
   list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
   link->next->prev = link->prev;
   link->prev->next = link->next;
   free(link);
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
   struct CircularList* list = malloc(sizeof(struct CircularList));
   init(list);
   return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
   struct Link* cur = list->sentinel->next;
   while(cur != list->sentinel){
      struct Link* tmp = cur;
      cur = cur->next;
      free(tmp);
   }
   free(list->sentinel);
   free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
   struct Link* newLink = createLink(value);
   newLink->next = list->sentinel->next;
   newLink->prev = list->sentinel;
   list->sentinel->next->prev = newLink;
   list->sentinel->next = newLink;
   list->size++;
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
   struct Link* newLink = malloc(sizeof(struct Link));
   newLink->value = value;
   newLink->next = list->sentinel;
   newLink->prev = list->sentinel->prev;
   list->sentinel->prev->next = newLink;
   list->sentinel->prev = newLink;
   list->size++;
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
   return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
   return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
   struct Link* bye = list->sentinel->next;
   list->sentinel->next->next->prev = list->sentinel;
   list->sentinel->next = list->sentinel->next->next;
   free(bye);
   list->size--;
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
   struct Link* bye = list->sentinel->prev;
   list->sentinel->prev->prev->next = list->sentinel;
   list->sentinel->prev = list->sentinel->prev->prev;
   free(bye);
   list->size--;
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
   if(list->size == 0)
      return 1;
   return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
   struct Link* cur = list->sentinel->next;
   while(cur != list->sentinel){
      printf("%f  ", cur->value);
      cur = cur->next;
   }
   printf("\n");
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
   struct Link* tmp = list->sentinel->prev;
   list->sentinel->prev = list->sentinel->next;
   list->sentinel->next = tmp;
   struct Link* cur = list->sentinel->next;
   while(cur != list->sentinel){
      tmp = cur->prev;
      cur->prev = cur->next;
      cur->next = tmp;
      cur = cur->next;
   }
}
