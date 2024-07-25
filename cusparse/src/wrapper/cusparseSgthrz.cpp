#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSgthrz(cusparseHandle_t handle, int nnz, float *y, float *xVal, const int *xInd, cusparseIndexBase_t idxBase)
{
	cusparseStatus_t retval = cusparseSgthrz(handle, nnz, y, xVal, xInd, idxBase);
	return retval;
}