#include <time.h>
#include <stdlib.h>
#include "ai.h"
#include "utils.h"
#include "priority_queue.h"
#include "list.h"

struct heap h;
struct list l;
struct action actarr[4];

void initialize_ai(){
	heap_init(&h);
    list_init(&l);
    // global variable to record generated nodes and expanded nodes;
    GENERATED = 0;
    EXPANDED = 0;
}

void resetActarr(){
    for(int move = left; move < down; move++){
        actarr[move].max_score = -1;
        actarr[move].total_child_score = 0;
        actarr[move].num_childs = 0;
    }
}
move_t chooseAction(propagation_t propagation){
    move_t best_move = rand() % 4;
    for(int move = left; move < down; move++){
        //printf("%d ", actarr[move].max_score);
        if(propagation == max){
            if(actarr[move].max_score > actarr[best_move].max_score){
                best_move = move;
            }
        }else if(propagation == avg){
            if(actarr[best_move].num_childs == 0){
                best_move = move;
                continue;
            }
            if(actarr[move].num_childs == 0){
                continue;
            }
            float t = ((float)actarr[move].total_child_score) / actarr[move].num_childs;
            float t1 = ((float)actarr[best_move].total_child_score) / actarr[best_move].num_childs;
            if(t > t1){
                best_move = move;
            }
        }
    }
    //printf("\n");
    //printf("%d, %d", actarr[best_move].total_child_score, actarr[best_move].num_childs);
    return best_move;
}
void update_info(node_t* node, propagation_t propagation){
    if(node->parent == NULL){
        return;
    }
    if(propagation == max){
        if(node->parent->parent == NULL){
            //printf("update 1, %d %d\n", node->max_score, actarr[node->move].max_score);
            if(node->max_score > actarr[node->move].max_score){

                //printf("update\n");
                actarr[node->move].max_score = node->max_score;
            }
        }
        node_t* p = node->parent;
        if(p->max_score <= node->max_score){
            p->max_score = node->max_score;
            update_info(p, propagation);
        }
    }else if(propagation == avg){
        if(node->parent->parent == NULL){

            actarr[node->move].total_child_score += node->new_child_score;
            actarr[node->move].num_childs++;
        }
        node_t* p = node->parent;
        p->new_child_score = node->new_child_score;
        update_info(p, propagation);
    }
}

/**
 * Find best action by building all possible paths up to depth max_depth
 * and back propagate using either max or avg
 */

move_t get_next_move( uint8_t board[SIZE][SIZE], int max_depth, propagation_t propagation ){
	if(max_depth == 0){
        move_t best_action = rand() % 4;
        return best_action;
    }

	//FILL IN THE GRAPH ALGORITHM

    resetActarr();
    node_t* start = malloc(sizeof(node_t));
    start->score = 0;
    start->priority = 0;
    start->depth = 0;
    start->max_score = 0;
    start->new_child_score = 0;
    copy_board(board, start->board);
    start->parent = NULL;

    heap_push(&h, start);

    node_t *newNode, *node;
    uint32_t i;
    uint8_t tmpBoard[SIZE][SIZE];
    uint32_t tmpScore;
    while(h.count > 0){
        node = h.heaparr[0];
        EXPANDED++;
        list_pushback(&l, node);
        heap_delete(&h);
        if(node->depth >= max_depth){
            continue;
        }
        for(i = 0; i < 4; i++){
            copy_board(node->board, tmpBoard);
            tmpScore = node->score;
            //printf("before = %d\t", tmpScore);
            switch(i){
                case left: moveLeft(tmpBoard, &tmpScore); break;
                case right: moveRight(tmpBoard, &tmpScore); break;
                case up: moveUp(tmpBoard, &tmpScore); break;
                case down: moveDown(tmpBoard, &tmpScore); break;
            }
            //printf("after = %d\n", tmpScore);
            GENERATED++;
            if(!compare_board(tmpBoard, node->board)){
                //printf("push\n");
                newNode = malloc(sizeof(node_t));
                newNode->score = tmpScore;
                newNode->priority = tmpScore;
                newNode->depth = node->depth+1;
                newNode->move = i;
                newNode->max_score = tmpScore;
                newNode->new_child_score = tmpScore;
                copy_board(tmpBoard, newNode->board);
                newNode->parent = node;

                update_info(newNode, propagation);
                heap_push(&h, newNode);
            }

        }
    }
    move_t best_action = chooseAction(propagation);
    emptyList(&l);
	return best_action;
}
