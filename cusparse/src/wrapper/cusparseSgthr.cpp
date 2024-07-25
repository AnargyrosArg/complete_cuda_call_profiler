#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSgthr(cusparseHandle_t handle, int nnz, const float *y, float *xVal, const int *xInd, cusparseIndexBase_t idxBase)
{
	cusparseStatus_t retval = cusparseSgthr(handle, nnz, y, xVal, xInd, idxBase);
	return retval;
}