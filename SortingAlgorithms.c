#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SortingAlgorithms.h"
#include "enum.h"

/*********************Auxiliary functions************************/

static void QuickSortRec(Vector* _vec, int _start, int _end);
static int Partition(Vector* _vec, int _start, int _end);
static void InsertionSortByGap(Vector* _vec, int _gap, int _start);
static void Merge (Vector* _vec, int* temp,  size_t _start, size_t _end, int _mid);
static void MergeRec(Vector* _vec, int* temp, size_t _start, size_t _end);
int static sortEndToStart (Vector* _vec, int _start, int _end);
int static sortStartToEnd (Vector* _vec, int _start, int _end);
static void RadixSortByDigit(Vector* _vec, int _digitIndex, int* count, int* orderly);
static int checkDigit(int _digitIndex, int num);
static void zeroArray(int* arr, int len);
static void returnSorted(Vector* _vec, int* _arr, int _len);

/*********************BubbleSort************************/

ADTErr BubbleSort(Vector* _vec)
{
int i;
int j;
size_t len;
int item1;
int item2;
int flag = 0;

	if(_vec == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum (_vec,&len);
	
	if(len == 0)
	{
		return ERR_NO_ELEMENTS;
	}
	
	for (i = 0; i < len - 1; i++)
        {
        	for(j = 0; j < len - i - 1; j++)
        	{
        		VectorGet(_vec, j, &item1);
        		VectorGet(_vec, j + 1, &item2);
        		
       			if(item1 > item2)
       			{
       				VectorSet(_vec, j, item2);
       				VectorSet(_vec, j + 1, item1);
       				flag = 1;
       			}
       		}
       		if(flag == 0)
       		{
       			return ERR_OK;
       		}

       		flag = 0;
        }
        
return ERR_OK;
}

/*********************ShakeSort************************/

ADTErr ShakeSort(Vector* _vec)
{
int i;
int start = 0;
int end;
size_t len;
int flag = 0;

	if(_vec == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum (_vec,&len);
	
	if(len == 0)
	{
		return ERR_NO_ELEMENTS;
	}
	
	end = len - 1;
	
	for (i = 0; i < len - 1 ; i++)
        {
        	if(i%2 == 0) 
        	{    
       			flag = sortStartToEnd(_vec, start, end);
       			end--;
       		}
       		
       		if(i%2 != 0) 
       		{    
       			flag = sortEndToStart(_vec, start, end);
       			start++;
       		}
       		
       		if(flag == 0)
       		{
       			return ERR_OK;
       		}

       		flag = 0;
        }
        
return ERR_OK;
}

int static sortStartToEnd (Vector* _vec, int _start, int _end)
{
int j;
int item1;
int item2;
int flag = 0;

	for(j = _start; j < _end; j++)
        {
        	VectorGet(_vec, j, &item1);
        	VectorGet(_vec, j + 1, &item2);
        		
       		if(item1 > item2)
       		{
       			VectorSet(_vec, j, item2);
       			VectorSet(_vec, j + 1, item1);
       			flag = 1;
       		}
       	}
       	
return flag;
}

int static sortEndToStart (Vector* _vec, int _start, int _end)
{
int j;
int item1;
int item2;
int flag = 0;

	for(j = _end; j > _start; j--)
        {
        	VectorGet(_vec, j, &item1);
        	VectorGet(_vec, j - 1, &item2);
        		
       		if(item1 < item2)
       		{
       			VectorSet(_vec, j, item2);
       			VectorSet(_vec, j - 1, item1);
       			flag = 1;
       		}
       	}
       		
return flag;
}

/*********************InsertionSort************************/

ADTErr InsertionSort(Vector* _vec)
{
int i;
int j;
size_t len;
int checkItem;
int runningItem;
int checkIndex;

	if(_vec == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum (_vec,&len);
	
	if(len == 0)
	{
		return ERR_NO_ELEMENTS;
	}
	
	checkIndex = 1;
	
	for(i = 0; i < len - 1; i++)
	{
	  	VectorGet(_vec, checkIndex, &checkItem);
		for(j = checkIndex; j > 0; j--)
		{
			VectorGet(_vec,j - 1 , &runningItem);
			if(checkItem  >= runningItem)
			{
				break;
			}
			if(checkItem  < runningItem)
			{
				VectorSet(_vec, j - 1, checkItem);
       				VectorSet(_vec, j , runningItem);
       			}	
		}
		checkIndex++;		
	}
return ERR_OK;
}

/*********************QuickSort************************/

ADTErr QuickSort(Vector* _vec)
{
size_t len;

	if(_vec == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum (_vec, &len);
	
	if(len == 0)
	{
		return ERR_NO_ELEMENTS;
	}
	
	QuickSortRec(_vec, 0, len -1);
	
return ERR_OK;
}

static void QuickSortRec(Vector* _vec, int _start, int _end)
{
size_t pivot;
	
	if(_start >= _end)
	{
		return;
	}
	
	pivot = Partition(_vec, _start, _end);
	QuickSortRec(_vec, _start, pivot -1);
	QuickSortRec(_vec, pivot + 1, _end);
}

static int Partition(Vector* _vec, int _start, int _end)
{
int pivotIndex = _start;
int start = _start + 1;
int end = _end;
int pivotItem;
int leftItem;
int rightItem;
		
		VectorGet(_vec, pivotIndex, &pivotItem);
		VectorGet(_vec, start, &leftItem);
		VectorGet(_vec, end, &rightItem);

	while(start <= end)
	{
		while(start <= _end && leftItem <= pivotItem)
		{
			start++;
			VectorGet(_vec, start, &leftItem);
		}
		
		while(end > _start && rightItem >= pivotItem)
		{
			end--;
			VectorGet(_vec, end, &rightItem);
		}
		
		if(start > end)
		{
			VectorSet(_vec, end, pivotItem);
			VectorSet(_vec,pivotIndex ,rightItem);
		}
		else
		{
			VectorSet(_vec, end, leftItem);
			VectorSet(_vec,start ,rightItem);
			VectorGet(_vec, end, &rightItem);
			VectorGet(_vec, start, &leftItem);	
		}	 			
	}
	
return end;
}

/*********************ShellSort************************/

ADTErr ShellSort(Vector* _vec)
{
size_t len;
int gap;
int start = 0;

	if(_vec == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum (_vec, &len);
	
	if(len == 0)
	{
		return ERR_NO_ELEMENTS;
	}
	
	for(gap = len/2; gap > 0; gap = gap/2)
	{
		for (start = 0; start < gap; start++)
		{
			InsertionSortByGap(_vec, gap, start);
		}
	}
return ERR_OK;	
}

static void InsertionSortByGap(Vector* _vec, int _gap, int _start)
{
int i;
int j;
size_t len;
int checkItem;
int runningItem;
int checkIndex;
	
	VectorItemsNum (_vec,&len);
	checkIndex = _start + _gap;
	
	for(i = _start; i < len - _gap; i = i + _gap)
	{
	  	VectorGet(_vec, checkIndex, &checkItem);
		for(j = checkIndex; j > _start; j = j - _gap)
		{
			VectorGet(_vec ,j - _gap ,&runningItem);
			if(checkItem  >= runningItem)
			{
				break;
			}
			if(checkItem  < runningItem)
			{
				VectorSet(_vec, j - _gap, checkItem);
       				VectorSet(_vec, j , runningItem);
       			}	
		}
		checkIndex = checkIndex + _gap;		
	}

}

/*********************SelectionSort************************/

ADTErr SelectionSort(Vector* _vec)
{
int startIndex;
int startItem;
size_t len;
int minItem;
int minIndex;
int ranItem;
int ranIndex;

	if(_vec == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum (_vec,&len);
	
	if(len == 0)
	{
		return ERR_NO_ELEMENTS;
	}
	
	for(startIndex = 0; startIndex < len - 1; startIndex++)
	{
		VectorGet(_vec, startIndex, &minItem);
		
		for(ranIndex = startIndex + 1; ranIndex < len ; ranIndex++)
		{
			VectorGet(_vec, ranIndex, &ranItem);
			if(ranItem < minItem)
			{
				minItem = ranItem;
				minIndex = ranIndex;
			}
		}
		
		VectorGet(_vec, startIndex, &startItem);	
		if(minItem < startItem)
		{
			VectorSet(_vec, startIndex, minItem);
			VectorSet(_vec, minIndex, startItem);		
		}
	}
return ERR_OK;
}

/*********************MergeSort************************/

ADTErr MergeSort(Vector* _vec)
{
size_t len;
int* temp;

	if(_vec == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum (_vec, &len);
	
	if(len == 0)
	{
		return ERR_NO_ELEMENTS;
	}
	
	if((temp = ((int*)malloc(sizeof(int)*len))) == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	MergeRec(_vec, temp, 0, len -1);	
	free(temp);
	
return ERR_OK;
}

static void MergeRec(Vector* _vec, int* temp, size_t _start, size_t _end)
{
int mid;

	if(_end <= _start)
	{
		return;
	}

mid = (_start + _end)/2;
	
	MergeRec(_vec,temp, _start, mid);
	MergeRec(_vec,temp, mid + 1 , _end);
	Merge(_vec, temp, _start, _end, mid);
}

static void Merge (Vector* _vec, int* temp,  size_t _start, size_t _end, int _mid)
{
int i = _start;
int j = _mid + 1;
int k = _start;
int p;
int leftItem;
int rightItem;

	while(i <= _mid && j <= _end)
	{
		VectorGet(_vec, i, &leftItem);
		VectorGet(_vec, j, &rightItem);
		if(leftItem > rightItem)
		{
			temp[k] = rightItem;
			k++;
			j++;	
		}
		else
		{
			temp[k] = leftItem;
			k++;
			i++;
		}		
	}
	

	while(i <= _mid)	
	{
		VectorGet(_vec, i, &leftItem);
		temp[k] = leftItem;
		k++;
		i++;	
	}
	
	while(j <= _end)
	{
		VectorGet(_vec, j, &rightItem);
		temp[k] = rightItem;
		k++;
		j++;
	}
	
	for(p = _start; p <= _end; p++)
	{
		VectorSet(_vec, p, temp[p]);	
	}
}



/*********************CountingSort************************/

ADTErr CountingSort(Vector* _vec, int _maxValue)
{
int i;
int* count;
int* orderly;
int item;
size_t len;

	VectorItemsNum (_vec, &len);
	
	if(_vec == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(len == 0)
	{
		return ERR_NO_ELEMENTS;
	}
 
	if((count = (int*)calloc(sizeof(int), _maxValue + 1)) == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if((orderly = ((int*)calloc(sizeof(int), len))) == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	for(i = 0; i < len; i++)
	{
		VectorGet(_vec, i, &item);
		count[item]++;
	}
	
	for(i = 1; i <= _maxValue; i++)
	{
		count[i] = count[i - 1] + count[i];
	}

	for(i = len - 1; i >= 0; i--)
	{
		VectorGet(_vec, i, &item);
		orderly[count[item]-1] = item;
		count[item]--;				
	}
	
	returnSorted(_vec, orderly, len);

	free(count);
	free(orderly);
	
return ERR_OK;
}


/*********************RadixSort************************/

ADTErr RadixSort(Vector* _vec, int _digitsNum)
{
int i;
int* count;
int* orderly;
size_t len;

	VectorItemsNum (_vec, &len);
	
	if(_vec == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(len == 0)
	{
		return ERR_NO_ELEMENTS;
	}
 
	if((count = (int*)calloc(sizeof(int), 10)) == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if((orderly = ((int*)calloc(sizeof(int), len))) == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	for (i = 0; i < _digitsNum; i++)
	{
		RadixSortByDigit(_vec, i, count, orderly);
	}
		
	free(count);
	free(orderly);
	
return ERR_OK;
}


static void RadixSortByDigit(Vector* _vec, int _digitIndex, int* count, int* orderly)
{
int i;
int item;
size_t len;
int digit;

	zeroArray(count, 10);
	
	VectorItemsNum (_vec, &len);
		
	for(i = 0; i < len; i++)
	{
		VectorGet(_vec, i, &item);
		digit = checkDigit(_digitIndex, item);
		count[digit]++;
	}
	
	for(i = 1; i <= 9; i++)
	{
		count[i] = count[i - 1] + count[i];
	}

	for(i = len - 1; i >= 0; i--)
	{
		VectorGet(_vec, i, &item);	
		digit = checkDigit(_digitIndex, item);
		orderly[count[digit]-1] = item;
		count[digit]--;	
	}
	
	returnSorted(_vec,orderly,len);
}

static void returnSorted(Vector* _vec, int* _arr, int _len)
{
int i;
	for(i = 0; i < _len; i++)
	{
		VectorSet(_vec,i ,_arr[i]);
	}
}
static int checkDigit(int _digitIndex, int _num)
{
int i;
int p = 1;
int digit;
int j;
	
	if(_digitIndex == 0)
	{
		digit = _num%10;
	}
	else
	{	
		for(j = 0; j<_digitIndex; j++)
		{
			p = p*10;
		}

		digit  = (_num/p)%10;		
	}
}

static void zeroArray(int* _arr, int _len)
{
int i;
	for(i = 0; i < _len; i++)
	{
		_arr[i] = 0;
	}
}

/*********************Auxiliary functions************************/

static void swap (Vector* _vec, int i, int j)
{
int iIten;
int jItem;

	VectorGet(_vec, i, &iIten);
	VectorGet(_vec, j, &jItem);	
	VectorSet(_vec,i, jItem);
	VectorSet(_vec,j, iIten);
}













