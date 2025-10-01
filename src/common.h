#include <stdbool.h>
#include <stddef.h>

// --- //

#define SIZEOF_NODE (sizeof(struct node_))
#define SIZEOF_LINKED_LIST (sizeof(struct linked_list_))

// --- //

struct node_ {
	void *data; // Pointer to data
	struct _node *next; // Pointer to next Node
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
