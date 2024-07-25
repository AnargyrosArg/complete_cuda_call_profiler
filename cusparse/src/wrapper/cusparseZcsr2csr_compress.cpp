#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseZcsr2csr_compress(cusparseHandle_t handle, int m, int n, const cusparseMatDescr_t descrA, const cuDoubleComplex *csrSortedValA, const int *csrSortedColIndA, const int *csrSortedRowPtrA, int nnzA, const int *nnzPerRow, cuDoubleComplex *csrSortedValC, int *csrSortedColIndC, int *csrSortedRowPtrC, cuDoubleComplex tol)
{
	cusparseStatus_t retval = cusparseZcsr2csr_compress(handle, m, n, descrA, csrSortedValA, csrSortedColIndA, csrSortedRowPtrA, nnzA, nnzPerRow, csrSortedValC, csrSortedColIndC, csrSortedRowPtrC, tol);
	return retval;
}