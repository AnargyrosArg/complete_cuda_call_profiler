#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseLoggerSetMask(int mask)
{
	cusparseStatus_t retval = cusparseLoggerSetMask(mask);
	return retval;
}