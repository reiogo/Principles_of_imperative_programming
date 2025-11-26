/*
 * Union-Find
 * 15-122 Principles of Imperative Computation
 *
 */

#include <stdbool.h>

#ifndef UNION_FIND_H
#define UNION_FIND_H

typedef struct ufs_header *ufs_t;

// Creates a new UFS of n singleton nodes
ufs_t ufs_new(unsigned int n);

// Checks that i is in the range of of eqs
bool ufs_isin(ufs_t eqs, int i);

// Find the canonical representative of i in eqs
int ufs_find(ufs_t eqs, int i);
//@requires ufs_isin(eqs, i);
//@ensures ufs_isin(eqs, \result);

// Take the union of the equivalence clases of i and j
//   i and j must be canonical representatives
void ufs_union(ufs_t eqs, int i, int k);
//@requires ufs_isin(eqs, i) && ufs_find(eqs, i) == i;
//@requires ufs_isin(eqs, k) && ufs_find(eqs, k) == k;

void ufs_free(ufs_t eqs);

// bonus
void ufs_print(char* prefix, ufs_t eqs);

#endif
