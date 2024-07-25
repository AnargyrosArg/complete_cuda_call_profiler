#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseZnnz_compress(cusparseHandle_t handle, int m, const cusparseMatDescr_t descr, const cuDoubleComplex *csrSortedValA, const int *csrSortedRowPtrA, int *nnzPerRow, int *nnzC, cuDoubleComplex tol)
{
	cusparseStatus_t retval = cusparseZnnz_compress(handle, m, descr, csrSortedValA, csrSortedRowPtrA, nnzPerRow, nnzC, tol);
	return retval;
}