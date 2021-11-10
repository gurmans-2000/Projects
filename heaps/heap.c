#include "heap.h"

HEAP *new_heap(int capacity)
{
  HEAP *nheap = (HEAP *) malloc(sizeof(HEAP));
  nheap->capacity = capacity;
  nheap->size = 0;
  nheap->hnap = (HNODE *) malloc(sizeof(HNODE) * capacity);
  
  return nheap;
}

void insert(HEAP *heap, HNODE new_node)
{
  if (!heap) return;

  // Overflow if inserted, resize
  if (heap->size == heap->capacity)
  {
    HNODE *temp;

    heap->capacity *= 2;  // Double the current capacity
    temp = realloc(heap->hnap, sizeof(HNODE) * heap->capacity);
    if (temp) // Reallocation successful
    {
      // Move pointer to new memory location
      heap->hnap = temp;
      display_heap(heap);
    } else  // Unable to reallocate
    {
      // Just allocate new memory
      temp = malloc(sizeof(HNODE) * heap->capacity);
      if (temp)
      {
        // Copy previous contents to new memory space
        memcpy(temp, heap->hnap, sizeof(HNODE) * heap->size);
        // Free previously allocated memory
        free(heap->hnap);
        // Set pointer to new memory location
        heap->hnap = temp;
      } else
      {
        printf("Array resize failed!\n");
      }
    }
  }
  // Heap has been resized if needed, so safe to just insert
  heap->hnap[heap->size] = new_node;

  // Update size
  heap->size++;

  // Heapify
  int curr_index = heap->size - 1;
  int parent_index = (curr_index - 1) / 2;
  while (cmp(heap->hnap[curr_index].key, heap->hnap[parent_index].key) == -1)
  {
    // Swap curr node and parent node
    HNODE temp = heap->hnap[curr_index];
    heap->hnap[curr_index] = heap->hnap[parent_index];
    heap->hnap[parent_index] = temp;
    curr_index = parent_index;
    parent_index = (curr_index - 1) / 2;
  }
}

HNODE extract_min(HEAP *heap)
{
  // Since this is a min tree, the min should be
  // at the root of the tree
  HNODE min = heap->hnap[0];
  // Set root to last element
  heap->hnap[0] = heap->hnap[heap->size - 1];
  // Free the last element's memory
  // DEBUG
  //printf("\n::> Min: (%d %d)\n", min.key, min.data);
  /*printf("::> Freed (%d %d)\n",
      heap->hnap[heap->size - 1].key,
      heap->hnap[heap->size - 1].data
  );*/
  free(heap->hnap + heap->size - 1);
  // Decrease heap size, as we have removed a node
  heap->size--;

  // Heapify
  int curr_index = 0;
  int child_index = 2 * curr_index + 2 < heap->size
                    ?
                      cmp(heap->hnap[2 * curr_index + 1].key, heap->hnap[2 * curr_index + 2].key) == -1
                      ?
                        2 * curr_index + 1
                      :
                        2 * curr_index + 2
                    :
                      2 * curr_index + 1 < heap->size
                      ?
                        2 * curr_index + 1
                      :
                        curr_index;
  while (cmp(heap->hnap[curr_index].key, heap->hnap[child_index].key) == 1)
  {
    // Swap the current node and its child node
    HNODE temp = heap->hnap[curr_index];
    heap->hnap[curr_index] = heap->hnap[child_index];
    heap->hnap[child_index] = temp;

    curr_index = child_index;
    child_index = 2 * curr_index + 2 < heap->size
                    ?
                      cmp(heap->hnap[2 * curr_index + 1].key, heap->hnap[2 * curr_index + 2].key) == -1
                      ?
                        2 * curr_index + 1
                      :
                        2 * curr_index + 2
                    :
                      2 * curr_index + 1 < heap->size
                      ?
                        2 * curr_index + 1
                      :
                        curr_index;
  }

  // Heap contents less than half of capacity,
  // resize capacity
  if (heap->size < heap->capacity / 2)
  {
    HNODE *temp;

    heap->capacity /= 2;
    temp = realloc(heap->hnap, sizeof(HNODE) * heap->capacity);
    if (temp)
    {
      heap->hnap = temp;
    } else
    {
      temp = malloc(sizeof(HNODE) * heap->capacity);
      if (temp)
      {
        memcpy(temp, heap->hnap, sizeof(HNODE) * heap->size);
        free(heap->hnap);
        heap->hnap = temp;
      }
      else
        printf("Array resize failed\n");
    }
  }
  return min;
}

void decrease_key(HEAP *heap, int node_index, KEYTYPE key_value)
{
  if (!heap) return;
  if (node_index > heap->size) return;

  heap->hnap[node_index].key = key_value;

  // Heapify as needed
  int curr_index = heap->size - 1;
  int parent_index = (curr_index - 1) / 2;
  while (cmp(heap->hnap[curr_index].key, heap->hnap[parent_index].key) == -1)
  {
    // Swap curr node and parent node
    HNODE temp = heap->hnap[curr_index];
    heap->hnap[curr_index] = heap->hnap[parent_index];
    heap->hnap[parent_index] = temp;
    curr_index = parent_index;
    parent_index = (curr_index - 1) / 2;
  }
}

int find_index(HEAP *heap, DATA value) {
  if (!heap) return -1;

  int index = 0;
  HNODE *curr = &(heap->hnap[index]);

  while (curr && index < heap->size)
  {
    if (curr->data == value)
      return index;
    index++;
    curr = &(heap->hnap[index]);
  }

  return -1;
}

void display_heap(HEAP *hp) {
  printf("\nsize:%d\ncapacity:%d\n", hp->size, hp->capacity);
    printf("(index, key, data):\n");
    int i;
    for (i=0; i < hp->size; i++) {
    printf("(%d %d %d) ", i, hp->hnap[i].key, hp->hnap[i].data);
    if (i % 10 == 9) printf("\n");    
  }
    printf("\n");
}

int cmp(KEYTYPE a, KEYTYPE b) {
  if (a < b) 
     return -1;
  else if (a==b) 
     return 0;
  else 
     return 1;
}