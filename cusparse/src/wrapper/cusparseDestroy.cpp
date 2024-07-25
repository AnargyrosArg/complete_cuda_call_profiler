#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDestroy(cusparseHandle_t handle)
{
	cusparseStatus_t retval = cusparseDestroy(handle);
	return retval;
}