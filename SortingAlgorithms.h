#ifndef __SORTINGALGORITHMS_H__
#define __SORTINGALGORITHMS_H__
#include "enum.h"
#include "vector.h"

/*Description: 
	the function sorts vector of integers using Bubbl algorithm.
Input:
	_vec - Pointer to the vector.
Output:
	ERR_NOT_INITIALIZED - if _vec == NULL.
	ERR_NO_ELEMENTS - if there are no elements in the vector.
	ERR_OK - If the sort done successfully.*/  
ADTErr BubbleSort(Vector* _vec);

/*Description: 
	the function sorts vector of integers using Shake algorithm.
Input:
	_vec - Pointer to the vector.
Output:
	ERR_NOT_INITIALIZED - if _vec == NULL.
	ERR_NO_ELEMENTS - if there are no elements in the vector.
	ERR_OK - If the sort done successfully.*/ 
ADTErr ShakeSort(Vector* _vec);

/*Description: 
	the function sorts vector of integers using Insertion algorithm.
Input:
	_vec - Pointer to the vector.
Output:
	ERR_NOT_INITIALIZED - if _vec == NULL.
	ERR_NO_ELEMENTS - if there are no elements in the vector.
	ERR_OK - If the sort done successfully.*/ 
ADTErr InsertionSort(Vector* _vec);

/*Description: 
	the function sorts vector of integers using Quick algorithm.
Input:
	_vec - Pointer to the vector.
Output:
	ERR_NOT_INITIALIZED - if _vec == NULL.
	ERR_NO_ELEMENTS - if there are no elements in the vector.
	ERR_OK - If the sort done successfully.*/ 
ADTErr QuickSort(Vector* _vec);

/*Description: 
	the function sorts vector of integers using Shell algorithm.
Input:
	_vec - Pointer to the vector.
Output:
	ERR_NOT_INITIALIZED - if _vec == NULL.
	ERR_NO_ELEMENTS - if there are no elements in the vector.
	ERR_OK - If the sort done successfully.*/ 
ADTErr ShellSort(Vector* _vec);

/*Description: 
	the function sorts vector of integers using Selection algorithm.
Input:
	_vec - Pointer to the vector.
Output:
	ERR_NOT_INITIALIZED - if _vec == NULL.
	ERR_NO_ELEMENTS - if there are no elements in the vector.
	ERR_OK - If the sort done successfully.*/ 
ADTErr SelectionSort(Vector* _vec);

/*Description: 
	the function sorts vector of integers using Merge algorithm.
Input:
	_vec - Pointer to the vector.
Output:
	ERR_NOT_INITIALIZED - if _vec == NULL.
	ERR_NO_ELEMENTS - if there are no elements in the vector.
	ERR_OK - If the sort done successfully.*/ 
ADTErr MergeSort(Vector* _vec);

/*Description: 
	the function sorts vector of integers using Counting algorithm. (The amount of elements in the vector can not be greater than the largest number)
Input:
	_vec - Pointer to the vector.
	_maxValue - The largest number in the Vector. 
Output:
	ERR_NOT_INITIALIZED - if _vec == NULL Or if the memory allocations to count/orderly failed.
	ERR_NO_ELEMENTS - if there are no elements in the vector.
	ERR_OK - If the sort done successfully.*/ 
ADTErr CountingSort(Vector* _vec, int _maxValue);

/*Description: 
	the function sorts vector of integers using Radix algorithm. (Works only on a 10 basis and without negative numbers)
Input:
	_vec - Pointer to the vector.
	_digitsNum - The number of digits of the longest number.
Output:
	ERR_NOT_INITIALIZED - if _vec == NULL Or if the memory allocations to count/orderly failed.
	ERR_NO_ELEMENTS - if there are no elements in the vector.
	ERR_OK - If the sort done successfully.*/
ADTErr RadixSort(Vector* _vec, int _digitsNum);

#endif /*#ifndef__SORTINGALGORITHMS_H__*/





