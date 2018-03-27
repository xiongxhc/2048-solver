#ifndef __NODE__
#define __NODE__

#include "utils.h"

/**
 * Data structure containing the node information
 */
struct node_s{
    uint32_t score;
    uint32_t priority;
    int depth;
    int num_childs;
    move_t move;
    int max_score;
    uint32_t new_child_score;
    uint8_t board[SIZE][SIZE];
    struct node_s* parent;
};

typedef struct node_s node_t;


#endif
