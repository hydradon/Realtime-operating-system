//
//  linkedList.h
//  memmang
//
//  Created by Colin Tan on 25/10/13.
//  Copyright (c) 2013 ceg. All rights reserved.
//

#ifndef memmang_linkedList_h
#define memmang_linkedList_h

// Memory management utility routines

// Memory manager data structure describing free and allocated memroy segments
typedef struct tmn
{
    unsigned long startAddress; // Starting address of this section of free/allcoated memory
    unsigned long len; // Length of this section of free/allcoated memory
    
    char allocated; // True if memory block is allocated, false if free.
    
    struct tmn *prev, *next; // Double-linked-list pointers
    
} TMemoryNode;


// Create a new node. startAddress = starting address of segment, len = length of segment
// in bytes, allocated = 0 if segment is free, 1 if used.
TMemoryNode *newNode(unsigned long startAddress, unsigned long len, unsigned int allocated);

// Inserts a new node into the linked list according to address, in ascending order
void insertNode(TMemoryNode *node);

// Returns true if two nodes represent FREE memory locations that are adjacent
// Tests location and location->next
char testAdjacent(TMemoryNode *location);

// Deletes a node. location = node to delete.
void deleteNode(TMemoryNode *location);

// Merges two nodes and deallocates one. location = address of first node to merge.
// Nodes at location and location->next will be merged and node at location->next deleted.
void mergeNodes(TMemoryNode *location);

// Compute memory allocation statistics;
void computeMemoryStats(double *totalFree, double *largestBlockSize, double *frag);

#endif
