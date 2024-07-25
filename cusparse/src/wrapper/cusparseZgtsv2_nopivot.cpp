#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseZgtsv2_nopivot(cusparseHandle_t handle, int m, int n, const cuDoubleComplex *dl, const cuDoubleComplex *d, const cuDoubleComplex *du, cuDoubleComplex *B, int ldb, void *pBuffer)
{
	cusparseStatus_t retval = cusparseZgtsv2_nopivot(handle, m, n, dl, d, du, B, ldb, pBuffer);
	return retval;
}