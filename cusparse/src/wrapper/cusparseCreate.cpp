#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCreate(cusparseHandle_t *handle)
{
	cusparseStatus_t retval = cusparseCreate(handle);
	return retval;
}