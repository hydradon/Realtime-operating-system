//
//  memmang.h
//  memmang
//
//  Created by Colin Tan on 22/10/13.
//  Copyright (c) 2013 ceg. All rights reserved.
//

#ifndef memmang_memmang_h
#define memmang_memmang_h
//
//  memmang.c
//  memmang
//
//  Created by Colin Tan on 22/10/13.
//  Copyright (c) 2013 ceg. All rights reserved.
//

#include <stdio.h>
#include "linkedList.h"

// -------- Type definitions for experiment types and memory allocation policy types ------
// Experiment types
#define ALLOCFREE       0
#define RUNTIME         1

// Memory Manager Types
#define MEMMANG_FIRSTFIT        0
#define MEMMANG_BESTFIT         1
#define MEMMANG_WORSTFIT        2

/* ==================================================================== */

// Set the two constants below to control type of experiment and type
// of memory allocation policy

// Set the experiment type here
//#define EXP_TYPE    ALLOCFREE
#define EXP_TYPE    RUNTIME

// Sets the memory manager type
//#define MEMMANG_TYPE            MEMMANG_FIRSTFIT
//#define MEMMANG_TYPE            MEMMANG_BESTTFIT
#define MEMMANG_TYPE            MEMMANG_WORSTFIT

/* ==================================================================== */

// You do not need to modify the constants below
// Number of runs for runtime experiment
#define MAXRUNS     200
#define MAXSAMPLES  MAXRUNS*10

// Total number of memory management blocks
#define MEMMANG_MAXBLOCKS       1024

// Total size of the memory block in bytes to allocate
#define MEMMANG_MAXSIZE         512           // 512B for our toy application
#define MEMMANG_NUMBUCKETS      10              // log2(MEMMANG_MAXSIZE)+1


// Sets base address that memory manager returns
#define MEMMANG_BASEADDR        16384
/* -----------------------------------------------------------------
 
 Memory Allocation Routines
 --------------------------
 
 These are the actual routines you will implement.
 
 ----------------------------------------------------------------- */

// You do not need to modify these two routines
void initializeMemory();
unsigned long NSGetLastAllocLen();

// You need to implement these

// Pre: requestedLen = Amount of memory requested in bytes
// Post: Memory is allocated and address of the start of the memory segment allocated is
//       returned. Return a NULL if there is no more memory to allocate.

void *NSAlloc(unsigned long requestedLen);


// Pre: pointerToFree = Starting address of memroy segment to free
// Post: Memory segment is freed
void NSFree(void *pointerToFree);


#endif
