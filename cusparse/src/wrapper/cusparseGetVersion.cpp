#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseGetVersion(cusparseHandle_t handle, int *version)
{
	cusparseStatus_t retval = cusparseGetVersion(handle, version);
	return retval;
}