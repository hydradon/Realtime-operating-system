#include <stdlib.h>
#include <limits.h>
#include "memmang.h"
#include "linkedList.h"
#include "nodes.h"

/* -----------------------------------------------------------------
 
 Memory Management Utilities
 ---------------------------
 
 These are provided to help you build your memory manager. You do not
 need to modify the codes given here.
 
 ----------------------------------------------------------------- */

extern TMemoryNode *_head;

/* -----------------------------------------------------------------
 
 Memory Allocation Routines
 --------------------------
 
 These are the actual routines you will implement. You should modify only
 findFreeMemory, NSAlloc and NSFree.
 
 ----------------------------------------------------------------- */

// The actual memory to allocate
char _memoryBlock[MEMMANG_MAXSIZE];
unsigned long _allocated_length;

void initializeMemory()
{

    // DO NOT MODIFY THIS CODE
    
    // Initialize the list of nodes
    createList(256);
    
    // Initializes the memory manager with a single node consisting of free memory
    // the size of memmang_maxsize, starting at location zero.
    TMemoryNode *myNewNode=newNode(0, MEMMANG_MAXSIZE, 0);
    myNewNode->startAddress=MEMMANG_BASEADDR;
    insertNode(myNewNode);
}

unsigned long NSGetLastAllocLen()
{
    return _allocated_length;
}


/* -------------------------------------------
 
    Modify only code below this line 
 
    ------------------------------------------- */

// Pre: requestedLen = # of bytes of memory requested
// Post: Returns pointer to memory management node (TMemoryNode) describing the available memory

TMemoryNode *findFreeMemory(unsigned long requestedLen)
{

    /* TODO: Implement algorithm to locate next free memory block
             using the allocation policy indicated */
     
    // ENSURE THAT YOUR CODE IS PROPERLY DOCUMENTED!!
    
#if MEMMANG_TYPE==MEMMANG_BESTFIT
	// algo - loop through the memory to find the pointer 
	// to the node with the minimum and sufficient memory possible
	// return that pointer

	TMemoryNode* current = _head;
	TMemoryNode* current_min = NULL;
	int i = 1;
	while(current != NULL){
		if(current->len >= requestedLen && !current->allocated){
			if(i==1){
				current_min = current;
				current = current->next;
				i++;
			}
			else {
				if(current->len < current_min->len){
					current_min = current;
					current = current->next;
				}else{
					current = current->next;
				}
			}
		}
		else{
			current = current->next;	
		}
	}

	return current_min;
    // Search for free memory using best fit policy
#elif MEMMANG_TYPE==MEMMANG_WORSTFIT
    
    // Search for free memory worst fit policy
	
	TMemoryNode* current = _head;
	TMemoryNode* current_max = NULL;
	int i = 1;
	while(current != NULL){
		if(current->len >= requestedLen && !current->allocated){
			if(i==1){
				current_max = current;
				current = current->next;
				i++;
			}
			else {
				if(current->len > current_max->len){
					current_max = current;
					current = current->next;
				}else{
					current = current->next;
				}
			}
		}
		else{
			current = current->next;	
		}
	}

	return current_max;



#elif MEMMANG_TYPE==MEMMANG_FIRSTFIT
 
    // Search for free memory using first fit policy
	TMemoryNode* current = _head;

	while(current != NULL){
		if(current->len >= requestedLen && !current->allocated){		// memory available in that node is sufficient
			return current;
			}
		current = current->next;
		}
	// in case memory is not found, return NULL
	return current;
    
#endif

    // dummy return to suppress compiler errors. Modify to return a pointer
    // to the TMemoryNode memory management node describing the free memory found.
//    return NULL;
    
}

// Pre: requestedLen = Amount of memory requested in bytes
// Post: Memory is allocated and address of the start of the memory segment allocated is
//       returned. Return a NULL if there is no more memory to allocate.

void *NSAlloc(unsigned long requestedLen)
{
    // TODO: Implement memory allocation algorithm here, returning address of the
    // memory block allocated, cast as (void *).
    
	TMemoryNode * current_find = NULL;
	TMemoryNode * current_remaining = NULL;
	TMemoryNode * toAssign = NULL;
	if(findFreeMemory(requestedLen) != NULL){
		current_find = findFreeMemory(requestedLen);
		// break up the 512 bar
		toAssign = current_find;
		//check if there is any leftover memory
		if(current_find->len - requestedLen == 0){
		// dont create new node
			toAssign->len = requestedLen;
			toAssign->allocated = 1;
		}else{
			current_remaining = newNode(toAssign->startAddress + requestedLen, current_find->len - requestedLen, 0);
			current_remaining->prev = toAssign;
			current_remaining->next = current_find->next;
			toAssign->len = requestedLen;
			toAssign->allocated = 1;
			toAssign->next = current_remaining;
		}
		
		_allocated_length = requestedLen;
		return (void *)toAssign->startAddress;
	}
	else{
		return (void *)current_find;			// return NULL if memory is not found	
	}
    
    /*
        Implement the memory allocation algorithms as shown in the lecture notes.
     
        Hint: You can write a single allocation routine for all 3 strategies. The
                strategies differ only in the way that findFreeMemory is implemented.
     
     */
    
    // IMPORTANT: Set the global variable _allocated_length to the number of bytes
    //            of memory you are allocating in this request.
    
    // Dummy return statement to suppress compiler errors
    
    // ENSURE THAT YOUR CODE IS PROPERLY DOCUMENTED!!

   // return NULL;
}

// Pre: pointerToFree = Starting address of memroy segment to free
// Post: Memory segment is freed

void NSFree(void *pointerToFree)
{
	// algo - first deallocate the memory unit pointed to by the pointerToFree
	// check left and right if can coalese
	TMemoryNode* current = _head;
	// locating the node that pointerToFree is pointing to
	while(current != NULL){
		if(current->startAddress != (unsigned long) pointerToFree){
			current = current->next;	
		}
		else{
			// current is pointing to the desired node
			// exit the while loop
			current->allocated = 0;
			break; 
		}
	}
	
	TMemoryNode* left = NULL;
	//char temp;
	//temp = testAdjacent(current->prev);
	// checking left of the pointerToFree
	if(testAdjacent(current->prev) == true){
		left = current->prev;
		mergeNodes(left);	
		current = left;
	}
	// checking right of the pointerToFree
	if(testAdjacent(current) == true){
		mergeNodes(current);	
	}
    // Implement the free memory routine.
    // Locate the node corresponding to the memory to free, set the allocated flag
    // to false to "deallocate" the memory, and do a merge if possible with neighboring
    // "free memory" nodes.
    
    // ENSURE THAT YOUR CODE IS PROPERLY DOCUMENTED!!

}



