//	bst.c
//	Assignment 7

//	Ana Melissa
//	Prof. Long
//	12/3/2021
// 	CSE 13S 2021

//	Citations:
//		I attended Eric's virtual section on 11/24/2021 and have used his psuedo code from that section in this file.
//		I used the code provided by Professor Long in Lecture-18-Trees-and-BST.pdf on pages 57 and 62.
//		I attended Sloan's section on Wednesday 11/24/2021 and 11/1/2021 and got individual help from Ben.

#include "bst.h"
#include "node.h"
#include "speck.h"
#include "salts.h"
#include "ht.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

// make an extern variable
uint64_t branches;

Node *bst_create(void) {
    // null <- create empty tree which is just NULL
    return NULL;
}

void bst_delete(Node **root) {
    // Call recursively so you can make sure you free all the nodes.
    // Depth-First-Search
    // post order traversal

    // first check if the root is even there, if it is, then you can recurse.
    if (*root != NULL) {
        // if the left node is not null, delete that node.
        if ((*root)->left != NULL) {
            bst_delete(&(*root)->left);
        }

        // if the right node is not null, delete that node.
        if ((*root)->right != NULL) {
            bst_delete(&(*root)->right);
        }
        // call node_delete on root.
        node_delete(&(*root));
    }
    return;
}

uint32_t bst_height(Node *root) {
    // This function returns the height of teh binary search tree rooted at (root).
    // find how deep the tree is.

    // First, if there is no tree, the height is 0.
    if (root == NULL) {
        return 0;
    }

    //if x is greater than y, x, else y
    if (bst_height(root->left) >= bst_height(root->right)) {
        return (bst_height(root->left) + 1);
    } else {
        return (bst_height(root->right) + 1);
    }
}

uint32_t bst_size(Node *root) {
    // This function returns the size of the binary search tree rooted at root.
    // The size of a tree is equivalent to the number of nodes in the tree.

    // First, if there is no tree, the size is 0.
    if (root == NULL) {
        return 0;
    }
    return bst_size(root->left) + bst_size(root->right) + 1;
}

Node *bst_find(Node *root, char *oldspeak) {
    // This function searches for a node containing oldspeak in the BST rooted at (root).

    if (root != NULL && oldspeak != NULL) {

        // if root->oldspeak is greater than oldspeak we are on left side of tree.
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            // If a node is found, the pointer to the node is returned.
            return bst_find(root->left, oldspeak);

            // Increment the external variable.
            branches = branches + 1;

            // if root->oldspeak is less than oldspeak we are on right side of tree.
        } else if (strcmp(root->oldspeak, oldspeak) < 0) {
            // If a node is found, the pointer to the node is returned.
            return bst_find(root->right, oldspeak);

            // Increment the external variable.
            branches = branches + 1;
        }
    }
    // Else, a NULL pointer is returned.
    return root;
}

Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    // This function inserts a new node containing the specified oldspeak and newspeak into the BST rooted at (root).
    // This acts like insertion sort on a tree.

    if ((root != NULL) && (oldspeak != NULL)) {

        // if root->oldspeak is greater than oldspeak we are on left side of tree.
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            // insert node into BST.
            root->left = bst_insert(root->left, oldspeak, newspeak);

            // Increment the external branch counter.
            branches = branches + 1;

            // if root->oldspeak is greater than oldspeak we are on left side of tree.
        } else if (strcmp(root->oldspeak, oldspeak) < 0) {
            // insert node into BST.
            root->right = bst_insert(root->right, oldspeak, newspeak);

            // Increment the external branch counter.
            branches = branches + 1;
        }
        return root;
    }
    return node_create(oldspeak, newspeak);
}

void bst_print(Node *root) {
    // in order traversal
    if (root) {
        bst_print(root->left);
        // use node_print
        node_print(root);
        bst_print(root->right);
    }
}
