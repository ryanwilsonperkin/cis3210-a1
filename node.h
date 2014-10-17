#ifndef CIS3210_A1_NODE_H
#define CIS3210_A1_NODE_H

#define MAX_CHILDREN 3

/*
 * get_child_index
 *  Search for value within array of children.
 *
 *  value: the value to search for
 *  num_children: the number of children in the array
 *  children: the array to search
 */
int get_child_index(int value, int num_children, int children[MAX_CHILDREN]);

/*
 * branch_node
 *  Run the state machine for a branch node.
 *
 *  this_node: the id of the running node
 *  parent_node: the id of the running node's parent
 *  num_children: number of children this branch has
 *  children: the ids of the children this branch has (suffixed with 0s for num_children < MAX_CHILDREN)
 *
 *  returns: 0 for success
 */
int branch_node(int this_node, int parent_node, int num_children, int children[MAX_CHILDREN]);

/*
 * leaf_node
 *  Run the state machine for a leaf node.
 *
 *  this_node: the id of the running node
 *  parent_node: the id of the running node's parent
 *
 *  returns: 0 for success
 */
int leaf_node(int this_node, int parent_node);

#endif // CIS3210_A1_NODE_H
