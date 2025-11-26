// Exercise 1 

// prove after n unions, the longest chain from 
// an element to its representative is O(log n)
// if we make sure the class with the longer chain
// is the canonical representation
// (without path compression)
// n is bound by v, the number of vertices,
// so the length of the chain is O(log(v))

// worst case a tree grows with unions that 
// are alway the same length.
// when heights are equivalent then the length increases by 1
// on each union.
// to make each union the same height then 
// each component needs 2v vertices. This creates the log(n) bound.

// When the two connected components are asymmetrical in size
// then the length of the farthest element does not change.
// for the length to change the lengths need to be equal.
// in which case there is plus one in length.
// To make unions of components that have the same size
// the unions need to be mirrored in size. The worst
// case therefore has as many symmetrical joins as possible
// which is O(log n) unions.


// ai-guided solution:
// node x has depth h then tree containing x has size at least 2^h
//
// proof by induction
// base case:
// if x is root then h = 0. the tree containing x has at least one node,
// 1 = 2^0 so the claim holds
// assume 2 trees that have 2^(h-1) then 2^(h-1)+ 2^(h-1) = 2^h
//

// Exercise 2 

// modify the basic union find so it does strong path compression:
// every find, every intermediate node will be redirected to point 
// to the root
// in exercise_2.c
// mostly only edits to the find function

// Exercise 3 

// modify the height tracking union find to do path compression
// may require loosening the invariants 



