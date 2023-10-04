//	bf.c
//	BloomFilter ADT
//	Assignment 7

// 	Ana Melissa
// 	Prof. Long
// 	12/3/2021
// 	CSE 13S Fall 2021

// Citations:
//		I attened Eric's section on Wednesday 11/24/2021 and I have used his psuedo code in this file.
//		I aslo attended Sloan's section on Wednesday 11/24/2021 and 11/1/2021 and have used some of Sloan's pseudo in this file.
#include "bv.h"
#include "bf.h"
#include "salts.h"
#include "ht.h"
#include "bst.h"
#include "speck.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct BloomFilter {
    // three main salts stored in these fields
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    //	Constructor for the Bloom filter.

    //	create a bit vector ADT -> array of bits for the Bloom filter.
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));

    //	Primary, Secondary, and Tertiary salts provided in salts.h
    // primary
    bf->primary[0] = SALT_PRIMARY_LO; // upper
    bf->primary[1] = SALT_PRIMARY_HI; // lower

    // secondary
    bf->secondary[0] = SALT_SECONDARY_LO; // upper
    bf->secondary[1] = SALT_SECONDARY_HI; // lower

    // tertiary
    bf->tertiary[0] = SALT_TERTIARY_LO; // upper
    bf->tertiary[1] = SALT_TERTIARY_HI; // lower

    bf->filter = bv_create(size);

    return bf;
}

void bf_delete(BloomFilter **bf) {
    //	Desctructor for a Bloom filter.
    //	Free any memory allocated by the constructor and NULL out the pointer that was passed in.

    if ((*bf != NULL) && ((*bf)->filter != NULL)) {
        // delete the bit vector.
        bv_delete(&(*bf)->filter);
        free(*bf); // Free the bloom filter.
        *bf = NULL; // Set the bloom filter to NULL.
    }
    return;
}

uint32_t bf_size(BloomFilter *bf) {
    //	Returns the size of the Bloom filter.
    //	Returns the number of bits that the Bloom filter can access.
    //	This is the length of the underlying bit vector.

    // call bv_length
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    //	This function takes oldspeak and inserts it into the Bloom filter.
    //	Hash oldspeak with the three salts for the three indices.
    //	and sett the bits at those indices in the underlying bit vector.

    // primary
    bv_set_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf));
    // secondary
    bv_set_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf));
    // tertiary
    bv_set_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf));

    return;
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    //	This function probes the Bloom filter for oldspeak.
    //	The oldspeak is hashed with the three salts for the three indices.
    //	If bits are set, return true, meaning that oldspeak is in Bloom Filter.

    // Use '&' to return true or false.
    return bv_get_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf))
           & bv_get_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf))
           & bv_set_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf));
}

uint32_t bf_count(BloomFilter *bf) {
    //	This function returns the number of set bits in the Bloom filter.

    uint32_t count = 0; // initialize the count variable.

    // Count up all the bits that are 1.
    // loop over the length of the bit vector inside the filter.
    for (uint32_t i = 0; i < bf_size(bf); i++) {
        // Increment the count.
        count += bv_get_bit(bf->filter, i);
    }
    return count; // Return the total count.
}

void bf_print(BloomFilter *bf);
//	A debug function to print out the bits of a bloom filter.
