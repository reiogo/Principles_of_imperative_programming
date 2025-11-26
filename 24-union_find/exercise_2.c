/*
 * Basic Union-Find
 * 15-122 Principles of Imperative Computation
 */

#include <stdlib.h>
#include <stdio.h>
#include "unionfind.h"
#include "lib/contracts.h"
#include "lib/xalloc.h"

// Types
typedef struct ufs_header ufs;
struct ufs_header {
  int size;    // >= 0
  int *data;   // != NULL
};

// Representation invariants

/* ufs_isin(eqs, i) if i is a valid element in eqs */
bool ufs_isin(ufs *eqs, int i) {
  return eqs != NULL
      && 0 <= i && i < eqs->size;
}

/* is_rep(eqs, i) if i is the representative of an equivalence class */
bool is_rep(ufs *eqs, int i) {
  return ufs_isin(eqs, i)
    && eqs->data[i] == i;
}

bool is_ufs(ufs *eqs) {
  if (eqs == NULL)       return false;
  if (eqs->size < 0)     return false;
  if (eqs->data == NULL) return false;
  //@assert eqs->size == \length(eqs->data);
  for (int i = 0; i < eqs->size; i++)
    if (!(ufs_isin(eqs, eqs->data[i])))
      return false;
  return true;
}

bool is_equiv(ufs *eqs, int i, int j) {
  REQUIRES(is_ufs(eqs));
  REQUIRES(ufs_isin(eqs, i));
  REQUIRES(ufs_isin(eqs, j));

  int i2 = i;
  int j2 = j;
  while (eqs->data[i2] != i2) i2 = eqs->data[i2];
  while (eqs->data[j2] != j2) j2 = eqs->data[j2];
  return i2 == j2;
}

// Implementation

/* ufs_new(n) returns an eqs where each node
 * [0..n) is in its own equivalence class
 */
ufs* ufs_new(unsigned int n) {
  ufs *eqs = xmalloc(sizeof(ufs));
  eqs->data = xcalloc(n, sizeof(int));

  for (int i = 0; i < (int)n; i++)
    eqs->data[i] = i;
  eqs->size = (int)n;

  ENSURES(is_ufs(eqs));
  return eqs;
}

/* ufs_find(eqs, i) finds the representative of the
 * equivalence class of i
 */
int ufs_find(ufs *eqs, int i) {
  REQUIRES(is_ufs(eqs));
  REQUIRES(ufs_isin(eqs, i));

  int j = i;
  while (eqs->data[j] != j) {
    ASSERT(is_equiv(eqs, i, j));
    j = eqs->data[j];
  }
  int m = i;
  while (eqs->data[m] != m){
    ASSERT(is_equiv(eqs, i, m));
    int tmp = m;

    m = eqs->data[m];
    eqs->data[tmp] = j;
  }

  ASSERT(is_equiv(eqs, i, j));

  ENSURES(is_ufs(eqs));
  ENSURES(is_rep(eqs, j));
  return j;
}

/* ufs_union(eqs, i, k) takes the union of equivalence
 * classes of i and k
 */
void ufs_union(ufs *eqs, int i, int k) {
  REQUIRES(is_ufs(eqs));
  REQUIRES(is_rep(eqs, i) && is_rep(eqs, k));

  if (i == k) return;      // same equivalence class already

  eqs->data[i] = k;        // merge i into k, always

  ENSURES(is_ufs(eqs));
  ENSURES(is_equiv(eqs, i, k));
}

void ufs_free(ufs *eqs) {
  REQUIRES(is_ufs(eqs));
  free(eqs->data);
  free(eqs);
}

void ufs_print(char* prefix, ufs* eqs) {
  REQUIRES(is_ufs(eqs));
  printf("%s", prefix);
  for (int i = 0; i < eqs->size; i++)
    printf("%3d ", eqs->data[i]);
  printf("\n");
}
