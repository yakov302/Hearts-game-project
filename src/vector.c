#include "vector.h"

struct Vector
{
int *m_items;
size_t m_originalSize;
size_t m_size;
size_t m_nItems;
size_t m_blockSize;
int m_magicNumber;
};

Vector *VectorCreate (size_t _initialSize, size_t _extensionBlockSize)
{
	Vector *ptr;
	
	if (_initialSize == 0 && _extensionBlockSize == 0)
	{
		return NULL;
	}
	
		
	/*memory allocation to structure*/
	if((ptr = ((Vector*)malloc(sizeof(Vector)))) == NULL)
	{
		return NULL;
	}
	/*memory allocation to array*/
	if (( ptr -> m_items = ((int*) malloc(_initialSize * sizeof(int)))) == NULL)
	{
		free(ptr);
		return NULL;
	}
	/*Entering values to the structure parameters*/
	ptr -> m_originalSize = _initialSize;
	ptr -> m_size = _initialSize;
	ptr -> m_nItems = 0;
	ptr -> m_blockSize = _extensionBlockSize;
	ptr -> m_magicNumber = MAGIC_NUMBER;
	
	return ptr;
}

void VectorDestroy (Vector* _vector)
{
	if(_vector == NULL || _vector -> m_magicNumber != MAGIC_NUMBER)
	{
		return;
	}
	
	_vector -> m_magicNumber = 0;
	free (_vector -> m_items);
	free(_vector);
}

ADTErr VectorAdd (Vector* _vector, int _item)
{
int *temp;

	if(_vector == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}

	if((_vector -> m_nItems) >= (_vector -> m_size))
	{
		if(_vector -> m_blockSize == 0)
		{
			return ERR_OVERFLOW;
		}
		
		temp = (int*)realloc(_vector -> m_items, (_vector -> m_size + _vector -> m_blockSize) * sizeof(int));
		if(temp == NULL)
		{
			return ERR_NOT_INITIALIZED;
		}
		
		_vector -> m_items = temp;
		_vector ->  m_size = _vector ->  m_size + _vector -> m_blockSize;	
	}
	
	_vector -> m_items[_vector -> m_nItems] = _item;
	_vector -> m_nItems++;
	return ERR_OK;

}

ADTErr VectorDelete(Vector* _vector, int* _item)
{

int *temp;

	if(_vector == NULL || _item == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (_vector -> m_nItems == 0)
	{
		return ERR_UNDERFLOW;
	}
	
	if ((_vector -> m_size) - (_vector -> m_nItems) >= (_vector -> m_blockSize)*2 && (_vector -> m_size) - (_vector ->  m_blockSize) >= (_vector ->  m_originalSize))
	{
		temp = (int*)realloc(_vector -> m_items, (_vector -> m_size - _vector -> m_blockSize) * sizeof(int));
		if(temp != NULL)
		{
			_vector -> m_items = temp;
			_vector -> m_size = (_vector -> m_size - _vector -> m_blockSize);		 
		}
		
	}
		*_item =  _vector -> m_items [_vector -> m_nItems - 1];
		_vector -> m_nItems--;
		return ERR_OK;
}
  
void VectorPrint(Vector* _vector)
{
int index;

	if(_vector == NULL)
	{
		return;
	}

	for(index = 0; index < _vector -> m_nItems ; index++)
	{
		printf("%d\n",  _vector -> m_items [index]);
	}
}

ADTErr VectorItemsNum (Vector* _vector, size_t* _numOfltems)
{
	if(_vector == NULL || _numOfltems == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	*_numOfltems = _vector -> m_nItems;
	return ERR_OK;
}

ADTErr VectorGet(Vector* _vector, size_t _index, int* _item)
{
	if(_vector == NULL || _item == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_index >= _vector -> m_nItems)
	{
		return ERR_WRONG_INDEX;
	}
	
	*_item =  _vector -> m_items[_index];
	return ERR_OK;
} 

ADTErr VectorSet(Vector* _vector, size_t _index, int _item)
{
	if(_vector == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_index >=  _vector -> m_nItems)
	{
		return ERR_WRONG_INDEX;
	}
	
	_vector -> m_items[_index] = _item;
	return ERR_OK;
} 

/************testFunction**************/

int Getm_originalSize (Vector* _vector)
{
	return _vector -> m_originalSize;
} 

size_t Getm_size (Vector* _vector)
{
	return _vector -> m_size;
}
 
size_t Getm_nItems (Vector* _vector)
{
	return _vector -> m_nItems;
} 

size_t Getm_blockSize (Vector* _vector)
{
	return _vector -> m_blockSize;
} 

int getn(Vector*_vector,  int i)
{
	return _vector -> m_items[i];
}

