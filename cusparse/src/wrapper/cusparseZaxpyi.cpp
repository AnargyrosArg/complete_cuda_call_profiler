#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseZaxpyi(cusparseHandle_t handle, int nnz, const cuDoubleComplex *alpha, const cuDoubleComplex *xVal, const int *xInd, cuDoubleComplex *y, cusparseIndexBase_t idxBase)
{
	cusparseStatus_t retval = cusparseZaxpyi(handle, nnz, alpha, xVal, xInd, y, idxBase);
	return retval;
}