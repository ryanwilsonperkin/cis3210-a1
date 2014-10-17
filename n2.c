#include "node.h"

int main(int argc, char *argv[])
{
    int children[MAX_CHILDREN] = {4, 0, 0};
    return branch_node(2, 1, 1, children);
}
