#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseZgthr(cusparseHandle_t handle, int nnz, const cuDoubleComplex *y, cuDoubleComplex *xVal, const int *xInd, cusparseIndexBase_t idxBase)
{
	cusparseStatus_t retval = cusparseZgthr(handle, nnz, y, xVal, xInd, idxBase);
	return retval;
}