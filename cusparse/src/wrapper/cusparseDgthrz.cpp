#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDgthrz(cusparseHandle_t handle, int nnz, double *y, double *xVal, const int *xInd, cusparseIndexBase_t idxBase)
{
	cusparseStatus_t retval = cusparseDgthrz(handle, nnz, y, xVal, xInd, idxBase);
	return retval;
}