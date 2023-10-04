//	bv.c
//	Bit Vector
//	Assignment 7

//	Ana Melissa
//	Prof. Long
//	12/3/2021
//	CSE 13S Fall 2021

//		I attended Sloan's section on Wednesday 11/24/2021 and 11/1/2021 and have used some of Sloan's pseudo in this file.
//      I also refered to the code comments repo that contains bit vector operations written by Professor Long.

#include "bv.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    // malloc for your bit vector
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));

    if (bv) {
        // initialize the bit vector length.
        bv->length = length;
        // allocate memory for vector.
        bv->vector = (uint8_t *) calloc(length, sizeof(BitVector));

        // in the event that sufficient memory cannot be allocated, rturn NULL
        if (!bv->vector) {
            free(bv);
            bv = NULL;
        }
    }
    // otherwise, return a BitVector *
    return bv;
}

void bv_delete(BitVector **bv) {
    // destructor for a bit vector.
    if (*bv && (*bv)->vector) {
        free((*bv)->vector);
        free(*bv);
        *bv = NULL;
    }
    return;
}

uint32_t bv_length(BitVector *bv) {
    // This function returns the length of a bit vector.
    return bv->length;
}

bool bv_set_bit(BitVector *bv, uint32_t i) {
    // This function sets the ith bit in a bit vector.

    if (i < bv->length && i >= 0) { // check the range of i.
        bv->vector[i / 8] |= (0x1 << (i % 8)); // set the ith bit.

        return true; // return true to indicate success.
    }
    // If i is out of range, return false.
    return false;
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
    // This function clears the ith bit in the bit vector.

    if (bv && bv->vector) { // make sure bv and bv->vector are not NULL.
        if (i < bv->length && i >= 0) { // check the range of i.
            bv->vector[i / 8] &= ~(0x1 << (i % 8)); // clear the ith bit.

            return true; // return true to indicate success.
        }
    }
    // if i is out of range return false
    return false;
}

bool bv_get_bit(BitVector *bv, uint32_t i) {
    // This function returns the ith bit in the bit vector.

    // Check if bit is 1 or 0.
    // Otherwise, return false if the value of bit i is 0
    // and return true if the value of bit i is 1.
    return ((bv->vector[i / 8] >> (i % 8)) & 0x1);
}

void bv_print(BitVector *bv);
