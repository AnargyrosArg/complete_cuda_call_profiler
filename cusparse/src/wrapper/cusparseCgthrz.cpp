#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCgthrz(cusparseHandle_t handle, int nnz, cuComplex *y, cuComplex *xVal, const int *xInd, cusparseIndexBase_t idxBase)
{
	cusparseStatus_t retval = cusparseCgthrz(handle, nnz, y, xVal, xInd, idxBase);
	return retval;
}