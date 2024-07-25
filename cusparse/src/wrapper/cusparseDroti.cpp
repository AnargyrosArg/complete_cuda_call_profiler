#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDroti(cusparseHandle_t handle, int nnz, double *xVal, const int *xInd, double *y, const double *c, const double *s, cusparseIndexBase_t idxBase)
{
	cusparseStatus_t retval = cusparseDroti(handle, nnz, xVal, xInd, y, c, s, idxBase);
	return retval;
}