#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDgthr(cusparseHandle_t handle, int nnz, const double *y, double *xVal, const int *xInd, cusparseIndexBase_t idxBase)
{
	cusparseStatus_t retval = cusparseDgthr(handle, nnz, y, xVal, xInd, idxBase);
	return retval;
}