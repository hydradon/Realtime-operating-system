//
//  nodes.h
//  memmang
//
//  Created by Colin Tan on 28/10/13.
//  Copyright (c) 2013 ceg. All rights reserved.
//

#ifndef memmang_nodes_h
#define memmang_nodes_h

#include "linkedList.h"


typedef TMemoryNode nodeType;

// Initializes the list of nodes
void createList(unsigned int numNodes);

// Gets a free memory management node or NULL if none are free
nodeType *getNode();

// Restore a memory management node to the list
void returnNode(nodeType *node);


#endif
