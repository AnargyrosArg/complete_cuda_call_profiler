#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCreateIdentityPermutation(cusparseHandle_t handle, int n, int *p)
{
	cusparseStatus_t retval = cusparseCreateIdentityPermutation(handle, n, p);
	return retval;
}