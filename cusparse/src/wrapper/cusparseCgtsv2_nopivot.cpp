#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCgtsv2_nopivot(cusparseHandle_t handle, int m, int n, const cuComplex *dl, const cuComplex *d, const cuComplex *du, cuComplex *B, int ldb, void *pBuffer)
{
	cusparseStatus_t retval = cusparseCgtsv2_nopivot(handle, m, n, dl, d, du, B, ldb, pBuffer);
	return retval;
}