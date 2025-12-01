// Exercise 1 

// on paper to save time

// Exercise 2 

// descending? its less and less priority as it goes down.
//
// Solution: neither, the only thing is that as we 
// go further down the nodes the priority never increases.
// (child is lower or equal to parent)

// Exercise 3 

// write an recursive version of is_heap_ordered
bool is_heap_ordered_v2_helper(heap *H, int child){
    if (child <= 1) return true;
    else {
        return ok_above(H, child/2, child) && is_heap_ordered_v2_helper(H, child-1);
    }
}

bool is_heap_ordered_v2(heap *H){
    REQUIRES(is_heap_safe(H));
    return is_heap_ordered_v2_helper(H, H->next - 1);
}

// Exercise 4 

// implement sift up as its own function

void sift_up(heap *H){
    REQUIRES(is_heap_safe(H));
    REQUIRES(H->next > 1 && is_heap_except_up(H,1));
    int i = H->next -1;
    ASSERT(1 <= i && i < H->next);
    ASSERT(is_heap_except_up(H,i));
    ASSERT(grandparent_check(H,i));
    while (i > 1 && !ok_above(H,i/2,i))
    //loop invariant: 1 <= i && i < H->next;
    //loop invariant: is_heap_except_up(H,i);
    //loop invariant: grandparent_check(H);
    {
        if (ok_above(H, i/2, i)) return;

        swap_up(H,i);
        i = i/2;
        ASSERT(1 <= i && i < H->next);
        ASSERT(is_heap_except_up(H,i));
        ASSERT(grandparent_check(H,i));
    }

    ENSURES(is_heap(H));
}
// Exercise 5 

// bump the least priority item for a new add when full:
// overwrite the last element with the new then sift up
// asymptotic complexity is O(log n) still nothing much changes.
void pq_bump(heap *H, elem x){
    REQUIRES(is_heap(H));
    if (pq_full){
        H->data[limit - 1] = x;
    } else {
        H->data[H->next] = x;
        (H->next)++;
    }
    sift_up(H);
}


// this doesn't work since the least priority is not guarateed to be the last element
// alternatively it should be run through the entire heap looking for the lowest priority
// then bump it O(n + log n) which is O(n)


// the solution: get_minimal_element which will go through the leaves looking at the minimal element

// goes from the parent of H->next until back to H->next looking at all the leaf nodes for 
// the minimum element
int get_minimal_element(heap *H){
    REQUIRES(is_heap(H));
    elem min = H->data[H->next/2];
    int min_index = H->next/2;
    for (int i = H->next/2 + 1; i < H->next; i++){
        if (ok_above(H,min, H->data[i])) {
            min = H->data[i];
            min_index = i;
        }
    }
    return min_index;
    ENSURES(H->next/2 <= min_index && min_index < H->next);
}

// Exercise 6 


// diagrammatic proof: write on paper for ease of writing

