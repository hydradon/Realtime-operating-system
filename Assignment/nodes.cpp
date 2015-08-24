//
//  nodes.c
//  memmang
//
//  Created by Colin Tan on 28/10/13.
//  Copyright (c) 2013 ceg. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"

// Nodes manager

nodeType *_listHead=NULL;

// Adds node to the list
void addNode(nodeType *newNode)
{
    if(!_listHead)
        _listHead=newNode;
    else
    {
        newNode->next=_listHead;
        _listHead->prev=newNode;
        _listHead=newNode;
    }
}

// Create list of nodes
void createList(unsigned int numNodes)
{
    unsigned int i;
    nodeType *newNode;
    
    for(i=0; i<numNodes; i++)
    {
        newNode=(nodeType *) malloc(sizeof(nodeType));
        newNode->next=NULL;
        newNode->prev=NULL;
        addNode(newNode);
    }
}

// Return a free node
nodeType *getNode()
{
    nodeType *returnNode=NULL;
    
    if(_listHead)
    {
        returnNode=_listHead;
        _listHead=_listHead->next;
        
        returnNode->next=NULL;
        returnNode->prev=NULL;
    }
    
    return returnNode;
}

// Restore nodes to the list
void returnNode(nodeType *node)
{
    // Remove all links
    node->prev=NULL;
    node->next=NULL;
    node->allocated=0;
    addNode(node);
}