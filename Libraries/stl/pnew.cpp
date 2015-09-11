#include "pnew.h"
void* operator new(size_t size_,void *ptr_)
{
	return ptr_;
}
