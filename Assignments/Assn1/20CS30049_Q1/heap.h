#ifndef LIBMYIMPL_HEAP_H
#define LIBMYIMPL_HEAP_H

#define max 100

typedef struct{
    int arr[max];
    int size;
}HEAP;

HEAP createHeap();
int findMin(HEAP H);
HEAP extractMin(HEAP H);
HEAP insertHeap(HEAP H, int k);
int isFullHeap(HEAP H);
int isEmptyHeap(HEAP H);

#endif
