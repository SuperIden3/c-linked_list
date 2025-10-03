#include <stdbool.h>
#include <stddef.h>

// --- //

#define SIZEOF_NODE (sizeof(struct node_))
#define SIZEOF_LINKED_LIST (sizeof(struct linked_list_))

// --- //

struct node_ {
	struct _node *next; // Pointer to next Node
	void *data; // Pointer to data
	bool in_memory; // Stack allocation must make this false, only functions that work with the heap should operate on this
};

struct linked_list_ {
	Node *head; // Pointer to first Node
	Node *tail; // Pointer to last Node
	size_t size; // Number of Nodes
	bool in_memory; // Same with this one
};

typedef struct node_ Node;
typedef struct linked_list_ LinkedList;

// --- //

/**
 * @brief Count how many `Node`s, including the one passed in, until a `NULL` has been hit for `next`.
 * @param start The `Node` to start counting from.
 * @return The number of sequential `Node`s there are, until `NULL`.
 */
size_t count_nodes(Node *start) {
	if (start == NULL) return 0; // No Node to operate on

	size_t count = 1; // Count starting at the one passed in
	while (start->next != NULL) { // Keep counting until hitting NULL
		start = start->next; // Go to next Node
		count++; // Count that Node, too
	}

	return count;
}
