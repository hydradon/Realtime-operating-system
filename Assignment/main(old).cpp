//
//  main.c
//  memmang
//
//  Created by Colin Tan on 22/10/13.
//  Copyright (c) 2013 ceg. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "memmang.h"
#include "timing.h"

/* ----------------------------------------------
 
    Memory test routines. Do not modify this file
   ----------------------------------------------- */

unsigned long totalTimeSpent=0;
unsigned long recordedTime[MAXSAMPLES];
unsigned long cumInternalFragmentation=0;
unsigned long cum=0;
void *ptr[20];

void testAlloc(void **ptr, unsigned long allocLen)
{
    unsigned long timeSpent, frag;
    startClock();
    *ptr=NSAlloc(allocLen);
    
    if(*ptr!=NULL)
    {
        timeSpent=endClock();
        totalTimeSpent+=timeSpent;
        recordedTime[cum]=timeSpent;
        cum++;
        frag=(int) fabs((long double)(NSGetLastAllocLen() - allocLen));
        
        cumInternalFragmentation+=frag;
        
        printf("Address: %ld Allocation Time: %lu Size Requested: %lu Size Allocated: %lu Internal Frag: %lu\n\n", (unsigned long)*ptr, timeSpent, allocLen, NSGetLastAllocLen(), frag);
    }
    else
        printf("Allocation failed. Out of memory?\n");
}

void testFree(void *ptr)
{
    unsigned long timeSpent;
    
    if(ptr==NULL)
        return;
    
    startClock();
    NSFree(ptr);
    timeSpent=endClock();
    printf("Time taken to free location %lu is %lu\n\n", (unsigned long) ptr, timeSpent);
}

void showMemStats()
{
    double totalFree, largestBlock, frag;
    
    computeMemoryStats(&totalFree, &largestBlock, &frag);
    
    printf("\nTotal Free: %4.2f Largest Block: %4.2f Fragmentation: %4.2f\n\n", totalFree, largestBlock, frag);
    

}
double variance(double mean)
{
    double sum=0.0;
    
    for(unsigned int i=0; i<cum; i++)
        sum+=((recordedTime[i]-mean) * (recordedTime[i]-mean));
    
    return sum/(cum-1.0);
}

void fillMemory()
{
    // Fill up memory completely
    testAlloc(&ptr[0], 1);
    testAlloc(&ptr[1], 2);
    testAlloc(&ptr[2], 4);
    testAlloc(&ptr[3], 8);
    testAlloc(&ptr[4], 16);
    testAlloc(&ptr[5], 32);
    testAlloc(&ptr[6], 64);
    testAlloc(&ptr[7], 128);
    testAlloc(&ptr[8], 256);
}

int main(int argc, const char * argv[])
{
    
    
    initializeMemory();


#if EXP_TYPE == RUNTIME
    int i;

    // Finding running times
    for(i=0; i<MAXRUNS; i++)
    {
        // Fill memory
        fillMemory();
        
        // Start making holes
        testFree(ptr[8]);
        testFree(ptr[2]);
        testFree(ptr[5]);
        
        // Allocate new items
        testAlloc(&ptr[2], 4);
        testAlloc(&ptr[5], 16);
        testAlloc(&ptr[8], 128);
        
        // Free everything
        for(int i=0; i<9; i++)
            testFree(ptr[i]);

    }
#else
    // Find statistics to compare memory allocation schemes
    
    // Fill the entire memory
    fillMemory();
    
    // Now start creating holes and filling them
    testFree(ptr[4]);
    testFree(ptr[6]);
    
    testAlloc(&ptr[4], 4);
    testAlloc(&ptr[6], 48);
    testAlloc(&ptr[9], 4);
    testAlloc(&ptr[10], 9);

    testFree(ptr[3]);
    testAlloc(&ptr[3], 4);
    
#endif
    
    double mean=(double) totalTimeSpent / cum;
    
    printf("Average Time: %4.2f\n", mean);
    printf("Variance: %4.2f\n", variance(mean));
    printf("Total internal fragmentation: %6.2f kilobytes\n", cumInternalFragmentation/1024.0);
    printf("Average internal fragmentation: %4.2f bytes\n", (double) cumInternalFragmentation/cum);
    showMemStats();
    
    return 0;
}

