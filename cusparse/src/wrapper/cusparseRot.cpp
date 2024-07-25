#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseRot(cusparseHandle_t handle, const void *c_coeff, const void *s_coeff, cusparseSpVecDescr_t vecX, cusparseDnVecDescr_t vecY)
{
	cusparseStatus_t retval = cusparseRot(handle, c_coeff, s_coeff, vecX, vecY);
	return retval;
}