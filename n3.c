#include "node.h"

int main(int argc, char *argv[])
{
    int children[MAX_CHILDREN] = {5, 6, 7};
    return branch_node(3, 1, 3, children);
}
