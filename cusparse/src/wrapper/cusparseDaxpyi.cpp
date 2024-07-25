#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDaxpyi(cusparseHandle_t handle, int nnz, const double *alpha, const double *xVal, const int *xInd, double *y, cusparseIndexBase_t idxBase)
{
	cusparseStatus_t retval = cusparseDaxpyi(handle, nnz, alpha, xVal, xInd, y, idxBase);
	return retval;
}