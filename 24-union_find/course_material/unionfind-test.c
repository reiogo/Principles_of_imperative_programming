/*
 * Testing Union-Find
 *
 * 15-122 Principles of Imperative Computation
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "unionfind.h"

int main () {
  int n = 6;

  printf("Test #1:\n");
  ufs_t eqs = ufs_new(n); ufs_print("init", eqs);

  ufs_union(eqs, ufs_find(eqs, 0), ufs_find(eqs, 1)); ufs_print("0-1:", eqs);
  ufs_union(eqs, ufs_find(eqs, 1), ufs_find(eqs, 2)); ufs_print("1-2:", eqs);
  ufs_union(eqs, ufs_find(eqs, 0), ufs_find(eqs, 2)); ufs_print("0-2:", eqs);
  ufs_union(eqs, ufs_find(eqs, 3), ufs_find(eqs, 4)); ufs_print("3-4:", eqs);
  ufs_union(eqs, ufs_find(eqs, 2), ufs_find(eqs, 3)); ufs_print("2-3:", eqs);
  ufs_union(eqs, ufs_find(eqs, 3), ufs_find(eqs, 5)); ufs_print("3-5:", eqs);
  ufs_find(eqs, 0);                                   ufs_print("fd0:", eqs);
  for (int i = 0; i < n-1; i++)
    assert(ufs_find(eqs,i) == ufs_find(eqs,i+1)); // a spanning tree?
  ufs_free(eqs);

  printf("\nTest #2:\n");
  //  n = 1<<12;
  n = 1<<4;
  eqs = ufs_new(n);
  for(int i = 0; i < n-1; i++) {
    ufs_union(eqs, ufs_find(eqs, i), ufs_find(eqs, i+1));
    ufs_print("i-i+1:", eqs);
  }
  assert(ufs_find(eqs, 0) == ufs_find(eqs, n-1));

  printf("All tests passed!\n");
  return 0;
}
