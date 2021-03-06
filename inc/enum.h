#ifndef __ENUM_H__
#define __ENUM_H__

typedef enum{
    ERR_NOT_INITIALIZED = -1,
    ERR_OK,
    ERR_GENERAL,
    ERR_ALLOCATION_FAILED,
    ERR_REALLOCATION_FAILED,
    ERR_UNDERFLOW, 
    ERR_OVERFLOW, 
    ERR_WRONG_INDEX,
    ERR_SIZE,
    ERR_UNBALANC,
    ERR_BALANC,
    ERR_NO_ELEMENTS,
    ERR_THERE_ARE_ELEMENTS,
    ERR_ELEMENT_EXIST,
    ERR_ELEMENT_DONT_EXIST,
    ERR_DUPLICATE,
    FULL,
    NOT_FULL,
    VALID_CARD,
NOT_VALID_CARD}ADTErr;


#endif //__ENUM_H__
