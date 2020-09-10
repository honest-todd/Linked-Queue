/*
 * Developed by R. E. Bryant, 2017
 * Extended to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
  queue_t *q =  malloc(sizeof(queue_t));
  if ( q != NULL ) {
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
  }
  return NULL;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
  {
    if ( q == NULL) {
      return;
    }
    if(q->head == NULL ){
      free(q);
      return;
    }
    //
    // traverse list and free each node
    //
    list_ele_t *temp;
    while (q->head != NULL) {
      temp = q->head;
      q->head = q->head->next;
      free(temp->value);
      free(temp);
    }
    //
    // free queue
    //
    free(q);

}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL) {
      return false;
    }
    //
    // create new node 
    //
    list_ele_t *new_head = malloc(sizeof(list_ele_t));
    if (new_head == NULL) {
          return false;
    }
    //
    // create new value 
    //
    char * new_value = malloc((strlen(s) + 1)*sizeof(char));
    if (new_value == NULL) {
      free(new_head);
      return false;
    }
    //
    // copy value into node
    //
    strcpy(new_value, s);
    new_head->value = new_value;
    //
    // Add node + update refs.
    // 
    if(q->head == NULL){
      new_head->next = NULL;
      q->tail = new_head;
    } else {
      new_head->next = q->head;
    }
    q->head = new_head;
    q->size++;
    return true;
}
/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
  if (q == NULL) {
      return false;
  }
  //
  //create new node
  //
  list_ele_t *new_tail = malloc(sizeof(list_ele_t));
  if (new_tail == NULL) {
        return false;
      }
  //
  //create new value
  //
  char *new_value = malloc((strlen(s) + 1)*sizeof(char));
  if(new_value == NULL){
      free(new_tail);
      return false;
    }
  //
  // copy value into node
  //
  strcpy(new_value, s);
  new_tail->value = new_value;
  //
  // Add node + update refs.
  // 
  new_tail->next = NULL;
  if(q->head == NULL) {
      q->head = new_tail;
  }
  if(q->tail != NULL){
    q->tail->next = new_tail;
  }
  q->tail = new_tail;
  q->size++;
  return true;
  }



/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
  if ( q == NULL){
    return false;
  }
  if (q->head == NULL){
    return false;
  }
  if ( q->size == 0 ){
    return false;
  }
  //
  // Copy removed string. 
  //
  if (sp != NULL) {
    strncpy(sp, q->head->value, bufsize - 1);
  }
  list_ele_t * new_head = q->head->next;
  //
  // Free list elem and string
  // 
  free(q->head->value);
  free(q->head);
  //
  // Update head ref.
  //
  q->head = new_head;
  q->size--;

  if (q_size(q) <= 1) {
    q->tail = new_head;
  }
  return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
  if ( q == NULL) {
    return 0;
  }
  return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
  if (q == NULL) {
    return;
  }
  if( q->head == NULL ){
    return;
  }

  list_ele_t *cur = q->head;
  list_ele_t *next = q->head->next;
  list_ele_t *prev = NULL;
  //
  // Traverse list
  //
  while (cur->next != NULL) {
    cur->next = prev;
    prev = cur;
    cur = next;
    next = cur->next;
  }
  //
  // Update head and tail refs.
  //
  cur->next = prev;
  q->tail = q->head;
  q->head = cur;

}
