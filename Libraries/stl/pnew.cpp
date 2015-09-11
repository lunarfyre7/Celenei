/*
 * pnew.cpp
 *
 *  Created on: Sep 9, 2015
 */

#include "pnew.h"
void* operator new(size_t size_,void *ptr_)
{
	return ptr_;
}
