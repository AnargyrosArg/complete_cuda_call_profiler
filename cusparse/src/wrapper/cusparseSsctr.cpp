#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSsctr(cusparseHandle_t handle, int nnz, const float *xVal, const int *xInd, float *y, cusparseIndexBase_t idxBase)
{
	cusparseStatus_t retval = cusparseSsctr(handle, nnz, xVal, xInd, y, idxBase);
	return retval;
}