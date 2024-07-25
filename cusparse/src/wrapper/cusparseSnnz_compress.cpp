#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSnnz_compress(cusparseHandle_t handle, int m, const cusparseMatDescr_t descr, const float *csrSortedValA, const int *csrSortedRowPtrA, int *nnzPerRow, int *nnzC, float tol)
{
	cusparseStatus_t retval = cusparseSnnz_compress(handle, m, descr, csrSortedValA, csrSortedRowPtrA, nnzPerRow, nnzC, tol);
	return retval;
}