#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseGetPointerMode(cusparseHandle_t handle, cusparsePointerMode_t *mode)
{
	cusparseStatus_t retval = cusparseGetPointerMode(handle, mode);
	return retval;
}