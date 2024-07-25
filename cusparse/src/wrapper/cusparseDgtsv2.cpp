#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDgtsv2(cusparseHandle_t handle, int m, int n, const double *dl, const double *d, const double *du, double *B, int ldb, void *pBuffer)
{
	cusparseStatus_t retval = cusparseDgtsv2(handle, m, n, dl, d, du, B, ldb, pBuffer);
	return retval;
}