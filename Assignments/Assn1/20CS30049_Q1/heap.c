#include "heap.h"

//function to create empty heap
HEAP createHeap()
{
    HEAP H;
    H.size = 0;
    return H;
}

//function to return min element of heap
int findMin(HEAP H)
{
    return H.arr[1];
}

//function to delete min element from heap
HEAP extractMin(HEAP H)
{
    //deletion
    H.arr[1] = H.arr[H.size];
    H.size--;
    //heapify after deletion
    int curr = 1;
    while (curr <= H.size)
    {

        int l = 2 * curr;
        int r = 2 * curr + 1;
        int min;
        if (l > H.size)
            return H;
        else if (r > H.size)
            min = l;
        else
            min = (H.arr[l] < H.arr[r]) ? l : r;
        if (H.arr[curr] < H.arr[min])
            return H;

        int temp = H.arr[curr];
        H.arr[curr] = H.arr[min];
        H.arr[min] = temp;
        curr = min;
    }
    return H;
}

//function to insert element in heap
HEAP insertHeap(HEAP H, int k)
{
    //insertion
    H.arr[H.size + 1] = k;
    H.size++;
    int curr = H.size;
    int par;
    //heapify after insertion
    while (curr >= 1)
    {

        par = curr / 2;
        if (H.arr[par] < H.arr[curr])
            return H;
        int temp = H.arr[par];
        H.arr[par] = H.arr[curr];
        H.arr[curr] = temp;
        curr = par;
    }
    return H;
}

//function that returns if heap is full or not
int isFullHeap(HEAP H)
{
    return (H.size == max - 1) ? 1 : 0;
}

//function that returns if heap is empty or not
int isEmptyHeap(HEAP H)
{
    return (H.size == 0) ? 1 : 0;
}

