#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseZgthrz(cusparseHandle_t handle, int nnz, cuDoubleComplex *y, cuDoubleComplex *xVal, const int *xInd, cusparseIndexBase_t idxBase)
{
	cusparseStatus_t retval = cusparseZgthrz(handle, nnz, y, xVal, xInd, idxBase);
	return retval;
}