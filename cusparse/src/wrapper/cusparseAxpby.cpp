#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseAxpby(cusparseHandle_t handle, const void *alpha, cusparseSpVecDescr_t vecX, const void *beta, cusparseDnVecDescr_t vecY)
{
	cusparseStatus_t retval = cusparseAxpby(handle, alpha, vecX, beta, vecY);
	return retval;
}