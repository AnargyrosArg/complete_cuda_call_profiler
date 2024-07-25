#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseCnnz_compress(cusparseHandle_t handle, int m, const cusparseMatDescr_t descr, const cuComplex *csrSortedValA, const int *csrSortedRowPtrA, int *nnzPerRow, int *nnzC, cuComplex tol)
{
	cusparseStatus_t retval = cusparseCnnz_compress(handle, m, descr, csrSortedValA, csrSortedRowPtrA, nnzPerRow, nnzC, tol);
	return retval;
}