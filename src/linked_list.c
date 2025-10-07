#define _POSIX_C_SOURCE 200809L

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

#include "common.h"

// --- //

extern int8_t Node__new(Node * *const nodeptr_addr, void *data, Node *next);

// --- //

/**
 * @brief Creates a new `LinkedList` in memory.
 * @param llptr_addr The address of a `LinkedList *`
 * @param head The first `Node *` that will be assigned to `head` on successful allocation
 * @param tail The last `Node *` that will be assigned to `tail` on successful allocation
 * @return -1 if `llptr_addr == NULL`, 0 on success, and 1 if `malloc` fails.
 */
int8_t LinkedList__new(LinkedList * *const llptr_addr, Node *head, Node *tail) {
	if (llptr_addr == NULL) return -1; // No LinkedList to operate on

	*llptr_addr = malloc(SIZEOF_LINKED_LIST); // Try to allocate
	if (*llptr_addr == NULL) return 1; // Failed allocation

	// Set values
	(*llptr_addr)->head = head;
	(*llptr_addr)->tail = tail;
	(*llptr_addr)->size = count_nodes(head, tail);
	(*llptr_addr)->in_memory = true; // Indicates it's in the heap

	return 0;
}

int8_t LinkedList__auto_new(LinkedList * *const llptr_addr) {
	if (llptr_addr == NULL) return -1;

}
