#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCsctr(cusparseHandle_t handle, int nnz, const cuComplex *xVal, const int *xInd, cuComplex *y, cusparseIndexBase_t idxBase)
{
	cusparseStatus_t retval = cusparseCsctr(handle, nnz, xVal, xInd, y, idxBase);
	return retval;
}