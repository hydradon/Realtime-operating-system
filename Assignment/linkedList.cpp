  //
//  linkedList.c
//  memmang
//
//  Created by Colin Tan on 25/10/13.
//  Copyright (c) 2013 ceg. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "nodes.h"

// Memory management utility routines

// The linked list head node
TMemoryNode *_head=NULL;

// Create a new node. startAddress = starting address of segment, len = length of segment
// in bytes, allocated = 0 if segment is free, 1 if used.
TMemoryNode *newNode(unsigned long startAddress, unsigned long len, unsigned int allocated)
{
//    TMemoryNode *ret=(TMemoryNode *) malloc(sizeof(TMemoryNode));
    TMemoryNode *ret=(TMemoryNode *) getNode();
    
    if(ret)
    {
        ret->startAddress=startAddress;
        ret->len=len;
        ret->allocated=allocated;
        ret->prev=NULL;
        ret->next=NULL;
    }
    return ret;
}

// Inserts a new node into the linked list according to address, in ascending order
void insertNode(TMemoryNode *node)
{
    
    if(_head==NULL)
        _head=node;
    else
    {
        TMemoryNode *trav = _head;
        
        // Find the correct insertion point. We always insert in ascending order and
        // depend on isBigger to reverse the order for worst fit.
        while(trav->next != NULL && trav->startAddress<node->startAddress)
            trav=trav->next;
        
        if(trav->next == NULL && trav->startAddress<node->startAddress)
        {
            trav->next=node;
            node->prev=trav;
        }
        else
        {
            if(trav->prev)
                trav->prev->next=node;
            else
                _head=node;
            
            node->prev=trav->prev;
            node->next=trav;
            trav->prev=node;
        }
    }
}

// Returns true if two nodes represent memory locations that are adjacent
// Tests location and location->next
char testAdjacent(TMemoryNode *location)
{
    if(location==NULL)
        return 0;
    
    if(location->next==NULL)
        return 0;
    
    return (!location->allocated && !location->next->allocated && (location->startAddress + location->len)==location->next->startAddress);
    
}

// Deletes a node. location = node to delete.
void deleteNode(TMemoryNode *location)
{
    if(location->next)
        location->next->prev=location->prev;
    
    if(location->prev)
        location->prev->next=location->next;
    
    // Special case; head node
    
    if(location==_head)
        _head=location->next;
    
    returnNode(location);
}

// Merges two nodes and deallocates one. location = address of first node to merge.
// Nodes at location and location->next will be merged and node at location->next deleted.
void mergeNodes(TMemoryNode *location)
{
    // Check to make sure we can actually merge
    if(location==NULL)
        return;
    
    if(location->next==NULL)
        return;
    
    // Perform merge
    location->len+=location->next->len;
    deleteNode(location->next);
}

// First argument gets total memory, second gets largest block size, third gets fragmentation
void computeMemoryStats(double *totalFree, double *largestBlockSize, double *frag)
{
    TMemoryNode *trav=_head;
    double totalMemory=0.0;
    double largestMemoryBlock=0.0;
    
    while(trav)
    {
        if(!trav->allocated)
        {
            totalMemory+=trav->len;
            if(trav->len > largestMemoryBlock)
                largestMemoryBlock=trav->len;            
        }
        trav=trav->next;
    }
    
    *totalFree=totalMemory;
    *largestBlockSize=largestMemoryBlock;
    *frag=1.0 - (largestMemoryBlock/totalMemory);
}