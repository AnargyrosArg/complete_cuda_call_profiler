#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSgtsv2_nopivot(cusparseHandle_t handle, int m, int n, const float *dl, const float *d, const float *du, float *B, int ldb, void *pBuffer)
{
	cusparseStatus_t retval = cusparseSgtsv2_nopivot(handle, m, n, dl, d, du, B, ldb, pBuffer);
	return retval;
}