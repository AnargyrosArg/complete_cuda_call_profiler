#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCgthr(cusparseHandle_t handle, int nnz, const cuComplex *y, cuComplex *xVal, const int *xInd, cusparseIndexBase_t idxBase)
{
	cusparseStatus_t retval = cusparseCgthr(handle, nnz, y, xVal, xInd, idxBase);
	return retval;
}