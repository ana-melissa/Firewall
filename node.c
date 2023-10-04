//	node.c
//	Assignment 7

//	Ana Melissa
// 	Prof. Long
//	12/3/2021
//	CSE 13S Fall 2021

// 	Citation:
//		I attended Sloan's section on Wednesday 11/24/2021 and 11/1/2021 and got individual help from Ben.

#include "node.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

Node *node_create(char *oldspeak, char *newspeak) {
    // each node is only able to have 2 or less children.
    // It can have no children.

    Node *n = (Node *) malloc(sizeof(Node)); // malloc for the actual node

    // everytime you get a word inside badspeak, you check inside newspeack for a translation
    if (oldspeak) {
        // strdu function()
        n->oldspeak = strdup(oldspeak);
    } else {
        n->oldspeak = NULL;
    }

    // newspeak most of the time is NULL
    if (newspeak) {
        n->newspeak = strdup(newspeak);
    } else {
        n->newspeak = NULL;
    }

    // set pointer to NULL
    n->right = NULL;
    n->left = NULL;

    return n; // return the node
}

void node_delete(Node **n) {
    // free the two words.
    // Then free the whole node.

    if (n && *n) {
        // if oldspeak has a value, free.
        if ((*n)->oldspeak != NULL) {
            // free oldspeak and newspeak
            free((*n)->oldspeak);
        }

        // if newspeak has a value, free.
        if ((*n)->newspeak != NULL) {
            // free oldspeak and newspeak
            free((*n)->newspeak);
        }

        // set node to null and free the node
        free(*n);
        *n = NULL;
    }
    return;
}

void node_print(Node *n) {
    // helper function
    if ((n->oldspeak != NULL) && (n->newspeak != NULL)) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    }

    if ((n->oldspeak != NULL) && (n->newspeak == NULL)) {
        printf("%s\n", n->oldspeak);
    }
    return;
}
