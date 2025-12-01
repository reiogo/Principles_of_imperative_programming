typedef bool has_higher_priority_fn(elem e1, elem e2);

typedef struct heap_header heap;
struct heap_header{
    int limit; // limit = capacity + 1 && limit <= int_max()/2
    int next; // 1 <= next && next <= limit
    elem[] data; // \length(data) == limit
    has_higher_priority_fn* prior; // != NULL
};

bool is_heap_safe(heap *H){
    return H != NULL
        && (1 < H->limit && H->limit <= int_max()/2)
        //&& is_array_expected_length(H->data, H->limit)
        && (1 <= H->next && H->next <= H->limit)
        && H->prior != NULL;
}

bool ok_above(heap *H, int i1, int i2)
{
    REQUIRES(is_heap_safe(H));
    REQUIRES( 1 <= i1 && i1 < H->next);
    REQUIRES(1 <= i2 && i2 < H->next);
    elem e1 = H->data[i1];
    elem e2 = H->data[i2];
    return !(*H->prior)(e2, e1);
}

void swap_up (heap *H, int child){
    REQUIRES(is_heap_safe(H));
    REQUIRES(2 <= child && child < H->next);
    REQUIRES(!ok_above(H, child/2, child));

    int parent = child/2;
    elem tmp = H->data[child];
    H->data[child] = H->data[parent];
    H->data[parent] = tmp;

    ENSURES(ok_above(H, child/2, child));
}


bool is_heap_ordered(heap *H){
    REQUIRES(is_heap_safe(H));
    // skips the root and the root starts at 1 for ease of counting
    for (int child = 2; child < H->next; child++)
    // loop invariant: 2 <= child
    {
        int parent = child/2;
        if (!ok_above(H, parent, child)) return false;
    }
    return true;
}

bool is_heap(heap *H) {
    return is_heap_safe(H) && is_heap_ordered(H);
}

bool pq_empty(heap *H)
{
    REQUIRES(is_heap(H));
    return H->next == 1;
}

bool pq_full(heap *H)
{
    REQUIRES(is_heap(H));
    return H->next == H->limit;
}

heap *pq_new(int capacity, has_higher_priority_fn *prior){
    REQUIRES(0 < capacity && capacity <= int_max()/2 - 1);
    REQUIRES(prior != NULL);
    heap *H = xmalloc(sizeof(heap));
    H->limit = capacity + 1;
    H->next = 1;
    H->data = xmalloc(sizeof(elem)*H->limit);
    H->prior = prior;

    ENSURES(is_heap(H) && pq_empty(H));
    return H;

}

bool is_heap_except_up(heap *H, int x){
    REQUIRES(is_heap_safe(H));
    REQUIRES(1 <= x && x < H->next);

    for (int child = 2; child < H->next; child++)
    //loop_invariant 2 <= child;
    {
        int parent = child/2;
        if (!(child == x ||
                ok_above(H,parent,child))) return;
        ASSERT( 2 <= child);
    }
    return true;
}


bool grandparent_check(heap *H, int i){
    REQUIRES(is_heap_safe(H));
    REQUIRES(1<= i && i < H->next);

    int left = 2*i;
    int right = left + 1;
    int grandparent = i/2;

    if (i == 1) return true;
    if (left >= H->next) return true;
    if (right == H->next) 
        return ok_above(H, grandparent, left);
    ASSERT(right < H->next);
    return ok_above(H,grandparent, left)
        && ok_above(H,grandparent,right);
}

void pq_add(heap *H, elem x){
    REQUIRES(is_heap(H) && !pq_full(H));
    H->data[H->next] = x;
    (H->next)++;

    int i = H->next -1;
    ASSERT(1 <= i && i < H->next);
    ASSERT(is_heap_except_up(H,i));
    ASSERT(grandparent_check(H,i));
    while (i > 1 && !ok_above(H,i/2,i))
    //loop invariant: 1 <= i && i < H->next;
    //loop invariant: is_heap_except_up(H,i);
    //loop invariant: grandparent_check(H);
    {
        swap_up(H,i);
        i = i/2;
        ASSERT(1 <= i && i < H->next);
        ASSERT(is_heap_except_up(H,i));
        ASSERT(grandparent_check(H,i));
    }

    ENSURES(is_heap(H));
}


bool is_heap_except_down(heap *H, int x){
    REQUIRES(is_heap_safe(H));
    REQUIRES(1 <= x && x < H->next);
    for (int child = 2; child < H->next; child++)
    // loop invariant: 2 <= child;
    {
        int parent = child/2;
        if(!(parent == x ||
                    ok_above(H, parent, child))) return false;
        ASSERT(2 <= child);
    }
    return true;
}

bool done_sifting_down(heap *H, int i){
    REQUIRES(is_heap_safe(H));
    REQUIRES(1 <= i && 2*i < H->next);
    REQUIRES(is_heap_except_down(H,i));

    int left = 2*i;
    int right = left + 1;

    return ok_above(H,i,left)
        && (right >= H->next
                || ok_above(H,i,right));
}
int child_to_swap_up(heap *H, int i){
    REQUIRES(is_heap_safe(H));
    REQUIRES(1 <= i && 2*i < H->next);
    REQUIRES(is_heap_except_down(H,i));
    int left = 2*i;
    int right = left + 1;

    if (right >= H->next ||
            ok_above(H, left, right)){
        ENSURES(left/2 == i);
        return left;
    }
    ASSERT(right < H->next);
    ASSERT(ok_above(H, right, left));
    ENSURES(right/2 == i);
    return right;
}

void sift_down(heap * H)
{
    REQUIRES(is_heap_safe(H));
    REQUIRES(H->next > 1 && is_heap_except_down(H, 1));
    int i = 1;
    ASSERT(1 <= i && i < H->next);
    ASSERT(is_heap_except_down(H,i));
    ASSERT(grandparent_check(H,i));
    while (2*i < H->next)
        // loop invariant: 1 <= i && i < H->next;
        // loop invariant: is_heap_except_down(H,i);
        // loop invariant: grandparent_check(H,i);
    {
        if (done_sifting_down(H,i)) return;

        int p = child_to_swap_up(H,i);
        swap_up(H,p);
        i = p;
        ASSERT(1 <= i && i < H->next);
        ASSERT(is_heap_except_down(H,i));
        ASSERT(grandparent_check(H,i));
    }
    ASSERT(i < H->next && 2*i >= H->next);
    ENSURES(is_heap(H));
}

elem pq_rem(heap *H){
    REQUIRES(is_heap(H) && !pq_empty(H));
    elem min = H->data[1];
    (H->next)--;
    if (H->next > 1){
        H->data[1] = H->data[H->next];
        sift_down(H);
    }
    ENSURES(is_heap(H));
    return min;
}


// heap sort testing
int main (){
    int n = (1 << 9) -1; // 1 <<9 for -d; 1 << 13 for timing
    int num_tests = 10; // 10 for -d; 100 for timing
    int seed = 0xc0c0ffee;
    rand_t gen = init_rand(seed);
    int *A = xmalloc(sizeof(int)*n);
    heap* H = pq_new(n, &int_lt);
    printf("Testing heap of size %d, %d times\n", n, num_tests);
    
    for (int j = 0; j < num_tests; j++){
        for (int i = 0; i < n; i++){
            pq_add(H,rand(gen));
        }
        for (int i = 0; i < n; i++){
            A[i] = pq_rem(H);
        }
        assert(pq_empty(H));
        assert(is_sorted(A,0,n));
    }
    printf("Passed all tests!\n");
    return 0;
}
