#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseDnnz_compress(cusparseHandle_t handle, int m, const cusparseMatDescr_t descr, const double *csrSortedValA, const int *csrSortedRowPtrA, int *nnzPerRow, int *nnzC, double tol)
{
	cusparseStatus_t retval = cusparseDnnz_compress(handle, m, descr, csrSortedValA, csrSortedRowPtrA, nnzPerRow, nnzC, tol);
	return retval;
}