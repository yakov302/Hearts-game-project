#ifndef __VECTOR_H__
#define __VECTOR_H__
#include <stdio.h>
#include "enum.h"

/*new name to the structure type*/
typedef struct Vector Vector;

/*VectorCreate function description:
1. Creates a memory allocation for structure that contains objects that managing the memory allocation.
2. creates memory allocation for array of int.
3.insert values to the structure elements of the structure:
*m_items: Pointer to the array
m_originalSize:Array size, comes as input - first parameter in the function.
m_size: Array size, comes as input - first parameter in the function.
m_nItems: size of the array increases (if necessary) comes as input - the second parameter in the function.
m_blockSize: The number of members in the array. gets the value 0.

input parameters:
_initialSize: Array size.
_extensionBlockSize:Size of the array increases (if necessary).

output parameter:
NULL: if the array size and the array increases size is equal to 0 or if the memory allocation to the structure or array failed.
ptr: pointer to the structure if the allocations were made successfully.*/
Vector *VectorCreate (size_t _initialSize, size_t _extensionBlockSize);

/*VectorDestroy function description:
Release allocation of the array and the structure.

input parameters:
*_vector: pointer to the structure.

output parameter:
ERR_NOT_INITIALIZED: if the *_vector pointer is equal to NUUL.
ERR_OK: if the allocation released done successfully*/
void VectorDestroy (Vector* _vector);

/*VectorAdd function description:
1. checks if the size of elements (m_nItems) is smaller than the size allocated to the array, and if is smaller, insert "_item" to the array and increases the number of elements (m_nItems) by 1;
2. if number of elements (m_nItems) equal to the array size allocation, the function:
re-allocates the size and saves it in a temporary pointer "temp".
if the allocation is performed successfully:
the new pointer is inserted into the original pointer "m_items".
the new size is inserted into the size variable "m_size".
"_item" insert to the array.
number of elements (m_nItems)increases the by 1.

input parameters:
*_vector: pointer to the structure.
_item: the value that needs to enter the array.

output parameter:
NERR_NOT_INITIALIZED: if the *_vector pointer is equal to NUUL or if the re-allocation failed (return NULL).
ERR_OVERFLOW: if re-allocation is needed and the size of array increasesis (m_blockSize) equal to 0.
OK: if the value of "_item" variable enters the array*/
ADTErr VectorAdd (Vector* _vector, int _item);

/*VectorDelete function description:
insert the last member in the array into pointer "_item" and decrease the number of elements(m_nItems) by 1. If the amount of empty members in the array is greater than the array increases size "m_blockSize" (but smaller than the original size) we will reduce the memory allocation to the array in the increases size (once) 

input parameters:
*_vecto: pointer to the structure.
*_item: pointer to "_item" variable, the last element of the array will be inserted into it.

output parameter:
ERR_NOT_INITIALIZED: if the *_vecto pointer or the *_item poinret  is equal to NUUL or if the number of elements in the array is equal to 0 or if the memory reduction failed.
ERR_UNDERFLOW: If the number of elements (m_nItems) is 0.
ERR_OK: If the last element in the array insert to "_item" and the number of elements decreases by 1*/
ADTErr VectorDelete(Vector* _vector, int* _item);

/*VectorPrint function description:
Prints all the members in the array.

input parameters:
*_vecto: pointer to the structure.

output parameter:
ERR_NOT_INITIALIZED: if the *_vecto pointer is equal to NUUL.
ERR_UNDERFLOW: If the number of elements (m_nItems) is 0.
ERR_OK: If the print was made successful*/
void VectorPrint(Vector* _vector);

/*VectorItemsNum function description:
insert the number of elements in the array into the variable _numOfltems.

input parameters:
*_vecto: pointer to the structure.
*_numOfltems: pointer to _numOfltems variable that will contain the number of elements in the array

output parameter:
ERR_NOT_INITIALIZED: if the *_vecto pointer or the *_numOfltemsis pointer is equal to NUUL.
ERR_OK: If the number of elements was successfully inserted into the _numOfltems variable*/
ADTErr VectorItemsNum (Vector* _vector, size_t* _numOfltems);

/*VectorGet function description:
Inserts into _item variable the member in the _index place.

input parameters:
*_vecto: pointer to the structure.
_index: The place from which the member in the array is taken
*_item: pointer to _item variable that will containthe the member in the _index place.

output parameter:
ERR_NOT_INITIALIZED: if the *_vecto pointer or the *_item pointer is equal to NUUL.
ERR_WRONG_INDEX: If the _index is greater than the number of elements in the array (m_items)
ERR_OK: If the member in the _index place inserts into _item variable successful*/
ADTErr VectorGet(Vector* _vector, size_t _index, int* _item);

/*VectorSet function description:
Inserts into the member in the _index place the value in the _item variable .

input parameters:
*_vecto: pointer to the structure.
_index: The place where the value in variable "_item" will enter in the array
*_item: Contains the value that will enter the member in the _index place.

output parameter:
ERR_NOT_INITIALIZED: if the *_vecto pointer is equal to NUUL.
ERR_WRONG_INDEX: If the _index is greater than the number of elements in the array (m_items)
ERR_OK: If _item variable inserts into the member in the _index place successful*/
ADTErr VectorSet(Vector* _vector, size_t _index, int _item);






#endif /*#ifndef__VECTOR_H__*/




























