// Exercise 1 

// if a priority queue is implemented with a sorted linked-list.
// what is it complexity?
// add - a sorted linkedlist will need an insertion O(1) and a resorting
// of the list. That would take O(nlogn).
// pop - if the list has the minimum at the head, then it would have 
// O(1)
// peek - also O(1) like in pop 
// remove - would have O(n) to find it and remove it.
// how does it compare to using an array.
// unsorted arrays have O(1) sorted arrays have O(n) for insertion
// This is the linked lists worst disadvantage, every add operation
// causes a reordered of the linked list
// For the unsorted list rem and peek are O(n), and for the 
// sorted its O(1) which is the same as the linked list so it's not
// that much of an advantage

// The real solution:
// So I was dumb and I thought up of a really dumb way to insert
// obviously I can insert with O(n) because you can just look for where
// to insert into the linkedlist. The advantage is that 
// the space taken by the linkedlist is proportional to the number of elements
// The disadvantage is that it doesn't have good insertion/deletion times.

// Exercise 2 

//                   1
//                 /   \
//                6     2
//              / \     / \
//            7    9   5   2
//          / \   / \          .
//        10   8  10  9
//
// Exercise 3 

// i swapped mine with the smaller value. but it should have been the larger value
// because its a max heap
//                   12
//                 /   \
//                9     14 
//              / \     / \
//            6    9   7  10 
//           /              
//          2   


// Solution:
//                   14
//                 /   \
//                12     10 
//              / \     / \
//            9    9   7   6
//           /              
//          2   
