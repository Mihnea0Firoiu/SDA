#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_
#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------
/**
 *  Linked list representation -- R2 Curs2 (Slide 8)
 */
typedef struct ListNode{
	Item elem; // Stored node value
	struct ListNode* next; // link to next node
	struct ListNode* prev; // link to prev node
} ListNode;

/**
 *  Double linked list representation -- desen Curs 3 (Slide 19)
 */
typedef struct List{
	ListNode* first; // link to the first node
	ListNode* last; // link to the last node
}List;
// -----------------------------------------------------------------------------

/**
 * Create a new node
 *  [input]: Item
 *  [output]: List*
 */
ListNode *createNode(Item elem) {
	// TODO: Cerinta 1a
	ListNode *node = malloc(sizeof(*node));
	node->next = NULL;
	node->prev = NULL;
	node->elem = elem;	
	return node;
}

/**
 * Create a new (empty)  list  -- Silde-urile 13/14 Curs 2
 *  [input]: None
 *  [output]: List*
 */
List* createList(void){
	// TODO: Cerinta 1a
	List *list = malloc(sizeof(*list));
	list->first = NULL;
	list->last = NULL;
	return list;
}
// -----------------------------------------------------------------------------


/**
 * Determines if the list is empty
 *  [input]: List*
 *  [output]: 1 - empty/ 0 - not empty
 */
int isEmpty(List *list){
	// TODO: Cerinta 1b
	return list->first == NULL;
}
// -----------------------------------------------------------------------------


/**
 * Determines if a list contains a specified element
 *  [input]: List*, Item
 *  [output]: int (1 - contains/ 0 - not contains)
 */
int contains(List *list, Item elem){
	// TDOO: Cerinta 1c
	ListNode *head = list->first;
	while (head != NULL) {
		if(head->elem == elem) {
			return 1;
		}
		head = head->next;
	}
	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Insert a new element in the list at the specified position.
 * Note: Position numbering starts with the position at index zero
 *  [input]: List*, Item, int
 *  [output]: void
 */
void insertAt(List* list, Item elem, int pos){
	if (list != NULL && isEmpty(list) == 1 && pos == 0) {
		list->first = createNode(elem);
		list->last = list->first;
		return ;
	}
	// Guard against young player errors
	if (list == NULL && pos != 0) {
		return ;
	} else if (list == NULL && pos == 0) {
		List *list = createList();
		list->first = createNode(elem);
		list->last = list->first;
	} else {
		ListNode *head = list->first;
		while (head != NULL) {
			if(pos == 0) {
				ListNode *node = createNode(elem);
				node->prev = head->prev;
				node->next = head;
				head->prev->next = node;
				head->prev = node;
				return ;
			}
			head = head->next;
			pos--;
		}
		if(head == NULL && pos == 0) {
			ListNode *node = createNode(elem);
			node->prev = list->last;
			list->last->next = node;
			list->last = node;
		}
	}
	// TODO: Cerinta 1d
}
// -----------------------------------------------------------------------------


/**
 * Delete the first element instance form a list.
 *  [input]: List*, Item
 *  [output]: void
 */
void deleteOnce(List *list, Item elem){
	// Guard against young player errors
	if(list == NULL) return;

	//TODO: Cerinta 1e
}
// -----------------------------------------------------------------------------


/**
 * Compute list length
 *  [input]: List*
 *  [output]: int
 */
int length(List *list){
	// Guard against young player errors
	if (list == NULL || list->first == NULL) return 0;
	ListNode *head = list->first;
	int counter = 0;
	while (head != NULL) {
		counter++;
		head = head->next;
	}
	// TODO: Cerinta 1f
	return counter;
}
// -----------------------------------------------------------------------------



/**
 * Destroy a list.
 *  [input]: List*
 *  [output]: void
 */
List* destroyList(List* list){
	// Guard against young player errors
	if(list == NULL) return NULL;

	//TODO: Cerinta 1g
	return NULL;
}
// -----------------------------------------------------------------------------


#endif //_DOUBLE_LINKED_LIST_H_
