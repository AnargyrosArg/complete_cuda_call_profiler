#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSroti(cusparseHandle_t handle, int nnz, float *xVal, const int *xInd, float *y, const float *c, const float *s, cusparseIndexBase_t idxBase)
{
	cusparseStatus_t retval = cusparseSroti(handle, nnz, xVal, xInd, y, c, s, idxBase);
	return retval;
}