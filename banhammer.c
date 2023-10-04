//	banhammer.c
//	Assignment 7

//	Ana Melissa
//	Prof. Long
//	10/25/2021
//	CSE 13S Fall 2021

//	Citations:
//		I attended Eric's virtual section on 12/1/2021 and have used his psuedo code from that section in this file.
//		I also attended Sloans TA session both wednesdays (12/1/2021 and 11/25/2021) and have used psuedo code from those sessions.

#include "bf.h"
#include "bst.h"
#include "bv.h"
#include "ht.h"
#include "messages.h"
#include "node.h"
#include "parser.h"
#include "salts.h"
#include "speck.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <regex.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <ctype.h>

// ? 1 or zero
// + is one or more
// * none or as many as you want
#define WORD "[a-zA-Z0-9_]+(('|-)[A-Za-z0-9_]+)*"

// define options for switch cases.
#define OPTIONS "ht:f:s"

int main(int argc, char **argv) {

    int opt = 0; // initialize options
    int t_size = 65536; // default t_size for hash table is 2^16
    int f_size = 1048576; // default f_size for bloom filter is 2^20
    bool stats = false; // set stats to false

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            // print useful help message.
            printf("SYNOPSIS\n");
            printf("   A word filtering program for the GPRSC.\n");
            printf("   Filters out and reports bad words parsed from stdin.\n");
            printf("\n");
            printf("USAGE\n");
            printf("   ./banhammer [-hs] [-t size] [-f size]\n");
            printf("\n");
            printf("OPTIONS\n");
            printf("   -h         Program usage and help.\n");
            printf("   -s         Print program statistics.\n");
            printf("   -t size    Specify hash table size (default: 2^16).\n");
            printf("   -f size    Specify Bloom filter size (default: 2^20).\n");

            break;

        case 't':
            // -t size specifies that the hash table will have size entries (the default is 2^16).
            t_size = atoi(optarg);
            break;

        case 'f':
            // -f size specifies that the Bloom filter will have size entries (the defailt is 2^20).
            f_size = atoi(optarg);
            break;

        case 's':
            // s will enable the printing of statistics to stdout.
            stats = true;
            break;

        default:
            // print help message and exit
            printf("SYNOPSIS\n");
            printf("   A word filtering program for the GPRSC.\n");
            printf("   Filters out and reports bad words parsed from stdin.\n");
            printf("\n");
            printf("USAGE\n");
            printf("   ./banhammer [-hs] [-t size] [-f size]\n");
            printf("\n");
            printf("OPTIONS\n");
            printf("   -h         Program usage and help.\n");
            printf("   -s         Print program statistics.\n");
            printf("   -t size    Specify hash table size (default: 2^16).\n");
            printf("   -f size    Specify Bloom filter size (default: 2^20).\n");

            return 1;
        }
    }

    // Check to make sure the Bloom filter size is not zero or below.
    if (f_size <= 0) {
        fprintf(stderr, "Bloom filter size is 0 or less. Invalid size.\n");
        return 1; // exit program.
    }

    // Check to make sure the hash table size is not zero or below.
    if (t_size <= 0) {
        fprintf(stderr, "Hash table size is 0 or less. Invalid size.\n");
        return 1; // exit program.
    }

    // Initialize the Bloom filter and Hash table.
    BloomFilter *bf = bf_create(f_size);
    HashTable *ht = ht_create(t_size);

    // use fopen file permissions to load badspeak and newspeak.
    FILE *badspeak_words = fopen("badspeak.txt", "r");
    FILE *newspeak_words = fopen("newspeak.txt", "r");

    char badspeak[1024]; // create variable for badspeak words.

    // run through the badspeak txt file and construct the bloom filter and hash table.
    while (fscanf(badspeak_words, "%s\n", badspeak) != EOF) {
        // Insert badspeak into the Bloom filter and Hash table.
        bf_insert(bf, badspeak);
        ht_insert(ht, badspeak, NULL);
    }

    fclose(badspeak_words); // close badspeak file

    char oldspeak[1024]; // create variable for oldspeak words.
    char newspeak[1024]; // create variable for newspeak words.

    // run through the newspeak txt file and construct the bloom filter and hash table.
    while (fscanf(newspeak_words, "%s %s\n", oldspeak, newspeak) != EOF) {
        // Insert oldspeak into the Bloom filter.
        bf_insert(bf, oldspeak);
        // Insert oldspeak and newspeak into the Bloom filter.
        ht_insert(ht, oldspeak, newspeak);
    }

    fclose(newspeak_words); //close newspeak file:

    // This regex code is from the Assignment 7 pdf.
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1; // exit program
    }

    char *word = NULL; // Create variable for your words you will filter through.
    Node *mixed = bst_create(); // Create a binary search tree for mixedspeak.
    Node *bad = bst_create(); // Create a binary search tree for badspeak.

    // Start to filter out words.
    // Read words in from stdin using the supplied parsing module.
    while ((word = next_word(stdin, &re)) != NULL) {

        // convert the word to a lower case word.
        for (int i = 0; i < word[i]; i++) {
            word[i] = tolower(word[i]);
        }

        // For each word that is read in, check to see if it is in the Bloom filter.
        if (bf_probe(bf, word) == true) {

            // After you check bloom filter, check your hash table.
            Node *n = ht_lookup(ht, word);

            // if newspeak DOES NOT equal NULL (has translation), insert to mixed speak.
            if ((n != NULL) && (n->newspeak != NULL)) {
                mixed = bst_insert(mixed, n->oldspeak, n->newspeak);

                // if newspeak is equal to NULL (no translation), insert badspeak.
            } else if ((n != NULL) && (n->newspeak == NULL)) {
                bad = bst_insert(bad, n->oldspeak, n->newspeak);
            }
        }
    }

    // If the user wants stats, print stats.
    if (stats == true) {

        //	average binary search tree size
        double bst_average_size = ht_avg_bst_size(ht);
        printf("Average BST size: %f\n", bst_average_size);

        //	average binary search tree height
        double bst_average_height = ht_avg_bst_height(ht);
        printf("Average BST height: %f\n", bst_average_height);

        //	average branches traversed branches / double(lookups)
        double avg_branches_traversed = (branches / (double) lookups);
        printf("Average branches traversed: %f\n", avg_branches_traversed);

        //	hash table load
        // 100 * (ht_count() / ht_size())
        double ht_load = (100 * (ht_count(ht) / (double) ht_size(ht)));
        printf("Hash table load: %f%%\n", ht_load);

        //	bloom filter load
        // 100 * (bf_count() / bf_size())
        double bf_load = (100 * (bf_count(bf) / ((double) bf_size(bf))));
        printf("Bloom filter load: %f%%\n", bf_load);

    } else {
        if ((bst_size(mixed) > 0) && (bst_size(bad) == 0)) {
            // print goodspeak message from messages.h
            printf("%s", goodspeak_message);
            bst_print(mixed);

        } else if ((bst_size(mixed) > 0) && (bst_size(bad) > 0)) {
            // print mixspeak message from messages.h
            printf("%s", mixspeak_message);
            bst_print(bad);
            bst_print(mixed);

        } else if ((bst_size(mixed) == 0) && (bst_size(bad) > 0)) {
            // print badspeak message from messages.h
            printf("%s", badspeak_message);
            bst_print(bad);
        }
    }
    // delete everything to prevent memory leaks.
    bf_delete(&bf);
    ht_delete(&ht);
    bst_delete(&mixed);
    bst_delete(&bad);
    clear_words();
    regfree(&re);
    return 0;
}
