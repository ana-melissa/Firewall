// 	ht.c
//	Hash Table
// 	Assignment 7

// Ana Melissa
// Prof. Long
// 12/1/2021
// CSE 13S Fall 2021

// Citations:
//		I attened Eric's section on Wednesday 11/24/2021 and I have used his psuedo code in this file.

#include "ht.h"
#include "node.h"
#include "bst.h"
#include "salts.h"
#include "bf.h"
#include "bv.h"
#include "bst.h"
#include "speck.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint64_t lookups;

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **trees;
};

HashTable *ht_create(uint32_t size) {
    // Allocate space for the hash table.
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    // initialize the size
    ht->size = size;

    // set the hash table salts.
    ht->salt[0] = SALT_HASHTABLE_LO;
    ht->salt[1] = SALT_HASHTABLE_HI;

    // allocate space for the tree.
    ht->trees = (Node **) calloc(size, sizeof(Node *));
    return ht;
}

void ht_delete(HashTable **ht) {
    // call bst delete on every single BST.

    // Check to make sure there is a hash table.
    if ((*ht) != NULL) {

        // iterate through hash table
        for (uint32_t i = 0; i < (*ht)->size; i++) {

            // as long as there is content in the tree, delete.
            if ((*ht)->trees[i] != NULL) {

                // Delete the hash table binary search tree at index i.
                bst_delete(&(*ht)->trees[i]);
            }
        }
    }

    free((*ht)->trees);
    free(*ht);
    *ht = NULL;

    return;
}

uint32_t ht_size(HashTable *ht) {
    // This function returns the size of the hash table.
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    // first hash it with hashtable salt to get your index.
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;

    lookups = lookups + 1; // increment the lookups external variable.

    // use bst_find() to look up the word on specific tree on specific word.
    // find a binary search tree and search that binary tree
    return bst_find(ht->trees[index], oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    // bst insert to get index hash it first
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;

    // find the correct binary search tree, and insert oldspeak and newspeak
    ht->trees[index] = bst_insert(ht->trees[index], oldspeak, newspeak);

    lookups = lookups + 1; // increment the lookups external variable.
    return;
}

uint32_t ht_count(HashTable *ht) {

    uint32_t count = 0; // initialize the count variable.

    // iterate through the hash table from zero to the hash table size.
    for (uint32_t i = 0; i < ht->size; i++) {
        // as long as there is content in the tree:
        if (ht->trees[i] != NULL) {
            count += 1; // increment the count.
        }
    }
    return count; // return the total count
}

double ht_avg_bst_size(HashTable *ht) {
    // This function returns the average binary search tree size.

    // This is computed as the sum of the sizes over all the binary search trees
    // divided by the number of non-NULL binary search trees in the hash table.

    double average_size = 0; // create the average size variable.

    for (uint32_t i = 0; i < ht->size; i++) {
        // increase the average size.
        average_size += bst_size(ht->trees[i]);
    }
    // return the average size divided by the count of the hash table.
    return (average_size / ht_count(ht));
}

double ht_avg_bst_height(HashTable *ht) {
    // This function returns the average binary search tree size.

    // This is computed as the sum of the height over all the binary search trees
    // divided by the number of non-NULL binary search trees in the hash table.

    double average_height = 0; // create the average height variable.

    for (uint32_t i = 0; i < ht->size; i++) {
        // increase the average height.
        average_height += (bst_height(ht->trees[i]));
    }
    // return the average height divided by the count of the hash table.
    return average_height / ht_count(ht);
}

void ht_print(HashTable *ht);
