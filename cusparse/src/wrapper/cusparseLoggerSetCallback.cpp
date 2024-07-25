#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseLoggerSetCallback(cusparseLoggerCallback_t callback)
{
	cusparseStatus_t retval = cusparseLoggerSetCallback(callback);
	return retval;
}