#ifndef C_LINKED_LIST_H
#define C_LINKED_LIST_H

#define _POSIX_C_SOURCE 200809L

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct _node {
	void *data; // Pointer to data
	struct _node *next; // Pointer to next Node
	bool in_memory; // Stack allocation must make this false, only functions that work with the heap should operate on this
} Node;

typedef struct {
	Node *head; // Pointer to first Node
	Node *tail; // Pointer to last Node
	size_t size; // Number of Nodes
	bool in_memory; // Same with this one
} LinkedList;

// --- //

#define SIZEOF_NODE (sizeof(Node))
#define SIZEOF_LINKED_LIST (sizeof(LinkedList))

// --- //

/**
 * @brief Creates a new `Node`.
 * @param nodeptr_addr The address of a `Node *`
 * @param data The data to point to.
 * @param next The next `Node` for the given `Node *` to point to.
 * @return -1 if `nodeptr_addr` is `NULL`, 0 on success, and 1 if `malloc` fails.
 */
int8_t Node__new(Node * *const nodeptr_addr, void *data, Node *next) {
	if (nodeptr_addr == NULL) return -1; // No Node to operate on

	*nodeptr_addr = malloc(sizeof *nodeptr_addr); // Try to allocate
	if (*nodeptr_addr == NULL) return 1; // Failed allocation

	(*nodeptr_addr)->data = data; // Make Node's data point to given data
	(*nodeptr_addr)->next = next; // Set next to NULL (no next)
	(*nodeptr_addr)->in_memory = true; // Indicate it's on the heap

	return 0; // Return
}

/**
 * @brief Initialize an existing `Node`, or make one if there isn't one.
 * If there is no `Node`, then one will be allocated on the heap. If there is a `Node`, then it will be assumed to be on the stack and intiialize it with `in_memory = false`.
 * @note Please do not send a `Node` that is on the heap into this function, as this function assumes any existing `Node` to be on the stack.
 * @param nodeptr_addr The address of a `Node *`
 * @param data The data to point to once successfully allocated
 * @param next The next `Node` to point to once successfully allocated
 * @return -1 if `nodeptr_addr == NULL`, 0 on success, and 1 if `Node__new` returns 1.
 */
int8_t Node__init(Node * *const nodeptr_addr, void *data, Node *next) {
	if (nodeptr_addr == NULL) return -1; // No Node to operate on

	// If there's no Node...
	if (*nodeptr_addr == NULL) // Make a new Node on the heap
		return Node__new(nodeptr_addr, data, next); // returns 0 on success or 1 if malloc fails

	// If there is a Node, then assume it's on the stack
	(*nodeptr_addr)->data = data;
	(*nodeptr_addr)->next = next;
	(*nodeptr_addr)->in_memory = false; // Avoid passing Nodes on the heap into this function

	return 0;
}

/**
 * @brief A shorter and simpler function for creating a `Node` in memory.
 * @param data The data to point to
 * @param next The next `Node` struct to point to
 * @return A `Node *` or NULL if malloc fails
 * @note This function uses `Node__new`.
 */
Node *Node__from(void *data, Node *next) {
	Node *ret = NULL; // Set up for Node__new
	Node__new(&ret, data, next); // Node__new ends with ret either being an actual allocated Node or NULL
	return ret; // Return a Node or NULL
}

/**
 * @brief Free a `Node` from the heap.
 * @param nodeptr_addr The address of a `Node *`
 * @return -1 if `nodeptr_addr == NULL`, 0 on success, and 1 if the actual `Node *` is `NULL`, and 2 if the Node's `in_memory` member holds `false`.
 */
int8_t Node__free(Node * *const nodeptr_addr) {
	if (nodeptr_addr == NULL) return -1; // No Node to free

	if (*nodeptr_addr == NULL) return 1; // Check if the actual Node object is NULL before accessing it
	if (!((*nodeptr_addr)->in_memory)) return 2; // Node is not on the heap

	free(*nodeptr_addr); // Free the Node
	*nodeptr_addr = NULL; // Prevent dangling pointer

	return 0;
}

/**
 * @brief Frees all Nodes after the specified Node. This excludes that Node.
 * @param nodeptr_addr The address of a `Node *`.
 * @return -1 if `nodeptr_addr == NULL` or 0 on success.
 */
int8_t Node__free_nexts(Node * *const nodeptr_addr) {
	if (nodeptr_addr == NULL) return -1; // No Node to operate on

	Node *next = (*nodeptr_addr)->next; // Storing next
	Node *after_next = NULL; // Storing after next

	while (next != NULL) {
		after_next = next->next; // Set after next to the new next's next first so that we don't dereference NULL
		Node__free(&next); // Free next
		next = after_next; // Set next to after next
	}

	return 0;
}

/**
 * @brief Frees the specified Nodes and the Nodes after it. This includes that Node.
 * @param nodeptr_addr The address of a `Node *`.
 * @return -1 if `nodeptr_addr == NULL` or 0 on success.
 */
int8_t Node__free_now_and_nexts(Node * *const nodeptr_addr) {
	if (nodeptr_addr == NULL) return -1; // No Node to operate on

	Node__free_nexts(nodeptr_addr); // Call Node__free_nexts to free consecutive Nodes and to store the current to also free it
	Node__free(nodeptr_addr); // Free the current Node

	return 0;
}

// --- //

#endif // C_LINKED_LIST_H
