#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseXcsr2coo(cusparseHandle_t handle, const int *csrSortedRowPtr, int nnz, int m, int *cooRowInd, cusparseIndexBase_t idxBase)
{
	cusparseStatus_t retval = cusparseXcsr2coo(handle, csrSortedRowPtr, nnz, m, cooRowInd, idxBase);
	return retval;
}