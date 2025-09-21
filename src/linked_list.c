#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct _node {
	void *data;
	struct _node *next;
	bool in_memory; // Stack allocation must make this false, only functions that work with the heap should operate on this
} Node;

typedef struct {
	Node *head;
	Node *tail;
	size_t size;
	bool in_memory; // Same with this one
} LinkedList;

/**
 * @brief Creates a new `Node`.
 * @param nodeptr_addr The address of a `Node *`
 * @param data The data to point to.
 * @param next The next `Node` for the given `Node *` to point to.
 * @return -1 if `nodeptr_addr` is `NULL`, 0 on success, and 1 if `malloc` fails.
 */
int8_t Node__new(Node * *const nodeptr_addr, void *data, Node *next) {
	if (nodeptr_addr == NULL) return -1; // No Node to operate on

	*nodeptr_addr = (Node *)malloc(sizeof(Node)); // Try to allocate
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
	if (*nodeptr_addr == NULL) { // Make new Node on heap
		if (Node__new(nodeptr_addr, data, next) == 1) return 1; // Node__new's malloc failed
		return 0;
	}

	// If there is a Node, then assume it's on the stack
	(*nodeptr_addr)->data = data;
	(*nodeptr_addr)->next = next;
	(*nodeptr_addr)->in_memory = false; // Avoid passing Nodes on the heap into this function

	return 0;
}

/**
 * @brief Free a `Node` from the heap.
 * @param nodeptr_addr The address of a `Node *`
 * @return -1 if `nodeptr_addr == NULL`, 0 on success, and 1 if the Node's `in_memory` member holds `true`.
 */
int8_t Node__free(Node * *const nodeptr_addr) {
	if (nodeptr_addr == NULL) return -1; // No Node to free

	if (!((*nodeptr_addr)->in_memory)) return 1; // Node is not on the heap

	free(*nodeptr_addr); // Free the Node
	*nodeptr_addr = NULL; // Prevent dangling pointer

	return 0;
}

