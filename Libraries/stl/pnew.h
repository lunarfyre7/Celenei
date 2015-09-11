/*
 * pnew.h
 *
 *  Created on: 24 Dec 2011
 *      Author: Andy Brown
 */

/**
 * Global placement operator new
 */
#ifndef _PNEW_H_
#define _PNEW_H_
#include <stddef.h>
void* operator new(size_t size_,void *ptr_);
#endif
